/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifdef CLEVER_DEBUG
#include <stdio.h>
#include "core/opcode.h"
#endif
#include "core/cstring.h"
#include "core/scope.h"
#include "core/value.h"
#include "types/type.h"
#include "core/vm.h"

namespace clever {

// VM initialization phase
inline void VM::init()
{
	// Opcode handler mapping
	m_handlers[OP_RET]        = &VM::ret;
	m_handlers[OP_ASSIGN]     = &VM::assignment;
	m_handlers[OP_ADD]        = &VM::add;
	m_handlers[OP_SUB]        = &VM::sub;
	m_handlers[OP_MUL]        = &VM::mul;
	m_handlers[OP_DIV]        = &VM::div;
	m_handlers[OP_MOD]        = &VM::sub;
	m_handlers[OP_JMP]        = &VM::jmp;
	m_handlers[OP_FCALL]      = &VM::fcall;
	m_handlers[OP_TCALL]      = &VM::threadcall;
	m_handlers[OP_END_THREAD] = &VM::endthread;
	m_handlers[OP_LEAVE]      = &VM::leave;
	m_handlers[OP_SEND_VAL]   = &VM::send_val;
	m_handlers[OP_JMPZ]       = &VM::jmpz;
	m_handlers[OP_JMPNZ]      = &VM::jmpnz;
	m_handlers[OP_PRE_INC]    = &VM::inc;
	m_handlers[OP_POS_INC]    = &VM::inc;
	m_handlers[OP_PRE_DEC]    = &VM::dec;
	m_handlers[OP_POS_DEC]    = &VM::dec;
}

inline Value* VM::getValue(size_t scope_id, size_t value_id) const
{
	return (*m_scope_pool)[scope_id]->getValue(value_id);
}

inline Value* VM::getValue(Operand& operand) const
{
	switch (operand.op_type) {
		case FETCH_CONST:
			return (*m_const_pool)[operand.value_id];
		case FETCH_VAL:
			return getValue(operand.scope_id, operand.value_id);
		default:
			return NULL;
	}
}

#ifdef CLEVER_DEBUG
void VM::dumpOperand(Operand& op) const
{
	const char *type[] = {"UNUSED", "FETCH_VAL", "FETCH_CONST", "JMP_ADDR"};

	switch (op.op_type) {
		case FETCH_VAL:
			::printf("%3ld:%3ld ", op.value_id, op.scope_id);
			break;
		case JMP_ADDR:
		case FETCH_CONST:
			::printf("%7ld ", op.value_id);
			break;
		case UNUSED:
			::printf("        ");
			break;
	}
	::printf(" (%-11s) | ", type[op.op_type]);
}

void VM::dumpOpcodes() const
{
	for (size_t i = 0, j = m_inst.size(); i < j; ++i) {
		IR& ir = m_inst[i];
		::printf("[%03ld] %-12s |", i, get_opcode_name(ir.opcode));
		dumpOperand(ir.op1),
		dumpOperand(ir.op2),
		::printf("%p\n", ir.result);
	}
}
#endif

// Return operation
VM_HANDLER(ret)
{
	if (m_call_stack.size()) {
		const StackFrame& frame = m_call_stack.top();
		const Value* val = getValue(op.op1);

		if (val) {
			m_call_stack.top().ret_val->copy(getValue(op.op1));
		}
		m_call_stack.pop();

		// Go back to the caller
		VM_GOTO(frame.ret_addr);
	} else {
		// Terminates the execution
		VM_GOTO(m_inst.size());
	}
}

// JMP operation
VM_HANDLER(jmp)
{
	VM_GOTO(op.op1.value_id);
}

// JMPZ operation
VM_HANDLER(jmpz)
{
	Value* value = getValue(op.op1);

	if (!value->getInt()) {
		VM_GOTO(op.op2.value_id);
	}

	VM_NEXT();
}

// JMPNZ operation
VM_HANDLER(jmpnz)
{
	Value* value = getValue(op.op1);

	if (value->getInt()) {
		VM_GOTO(op.op2.value_id);
	}

	VM_NEXT();
}

// Assignment operation
VM_HANDLER(assignment)
{
	Value* var = getValue(op.op1);
	Value* value = getValue(op.op2);

	var->copy(value);

	VM_NEXT();
}

// Math sum operation
VM_HANDLER(add)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() + rhs->getInt());
	}

	VM_NEXT();
}

// Math subtraction operation
VM_HANDLER(sub)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() - rhs->getInt());
	}

	VM_NEXT();
}

// Math multiplication operation
VM_HANDLER(mul)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() * rhs->getInt());
	}

	VM_NEXT();
}

// Math division operation
VM_HANDLER(div)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() / rhs->getInt());
	}

	VM_NEXT();
}

// Math modulus operation
VM_HANDLER(mod)
{
	Value* lhs = getValue(op.op1);
	Value* rhs = getValue(op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() % rhs->getInt());
	}

	VM_NEXT();
}

// Receives values to be used in the next function call
VM_HANDLER(send_val)
{
	m_call_args.push_back(getValue(op.op1));

	VM_NEXT();
}

// Saves function argument and local variables
void VM::saveVars()
{/*
	Scope* arg_vars   = m_call_stack.top().arg_vars;
	Scope* local_vars = m_call_stack.top().local_vars;

	if (arg_vars) {
		// Save the function argument values
		for (size_t i = 0, j = arg_vars->size(); i < j; ++i) {
			Value* tmp = new Value();

			tmp->copy(getValue(arg_vars->at(i).value_id));
			m_call_stack.top().vars.push_back(
				std::pair<size_t, Value*>(
					arg_vars->at(i).value_id, tmp));
		}
	}
	if (EXPECTED(local_vars != NULL)) {
		// Save the local variables
		for (size_t i = 0, j = local_vars->size(); i < j; ++i) {
			Value* tmp = new Value();

			tmp->copy(getValue(local_vars->at(i).value_id));
			m_call_stack.top().vars.push_back(
				std::pair<size_t, Value*>(
					local_vars->at(i).value_id, tmp));
		}
	}*/
}

// Restore the argument and local variables values
void VM::restoreVars() const
{/*
	FuncVars::const_iterator it = m_call_stack.top().vars.begin(),
		end = m_call_stack.top().vars.end();

	while (EXPECTED(it != end)) {
		Value* var = getValue((*it).first);
		var->copy((*it).second);
		++it;
	}*/
}

// Make a copy of VM instance
void VM::copy(VM* vm)
{
	this->m_pc = vm->m_pc;
	this->m_scope_pool = vm->m_scope_pool;

	for (size_t i = 0; i < NUM_OPCODES; ++i) {
		this->m_handlers[i] = vm->m_handlers[i];
	}

	this->m_call_stack = vm->m_call_stack;
	this->m_call_args = vm->m_call_args;
}

void VM::wait()
{
	for (size_t i = 0; i < m_thread_pool.size(); ++i) {
		void* status;

		pthread_join(m_thread_pool[i]->t_handler, &status);

		delete m_thread_pool[i]->vm_handler;
		delete m_thread_pool[i];
	}
	m_thread_pool.clear();
}

static void* _thread_control(void* arg)
{
	Thread* thread = static_cast<Thread*>(arg);
	VM* vm_handler = thread->vm_handler;

	vm_handler->fcall(vm_handler->getInst()[vm_handler->getPC()]);
	vm_handler->run();

	return NULL;
}

VM_HANDLER(endthread)
{
	if (this->isChild()) {
		this->m_pc = this->m_inst.size();
	}
}

// Creates a thread and copy current VM instance
VM_HANDLER(threadcall)
{
	Thread* thread = new Thread;

	thread->vm_handler = new VM(this->m_inst);
	thread->vm_handler->copy(this);

	this->m_call_args.clear();

	thread->vm_handler->setChild();

	m_thread_pool.push_back(thread);

	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&(thread->t_handler), &attr,
		_thread_control, static_cast<void*>(thread));

	pthread_attr_destroy(&attr);

	VM_NEXT();
	VM_NEXT();
}

// Function call operation
VM_HANDLER(fcall)
{
	Value* func = getValue(op.op1);
	Function* fdata = static_cast<Function*>(func->getObj());

	if (fdata->isUserDefined()) {
		if (m_call_stack.size()) {
			saveVars();
		}
		m_call_stack.push(StackFrame());
		m_call_stack.top().ret_addr = m_pc + 1;
		m_call_stack.top().ret_val  = op.result;

		// Function argument value binding
		if (fdata->hasArgs()) {
			Scope* arg_scope = fdata->getArgVars();

			m_call_stack.top().arg_vars = arg_scope;

			for (size_t i = 0, j = arg_scope->size(); i < j; ++i) {
				Value* arg_val = getValue(
					arg_scope->at(i).scope->getId(),
					arg_scope->at(i).value_id);

				if (i < m_call_args.size()) {
					arg_val->copy(m_call_args[i]);
				} else {
					arg_val->setNull();
				}
			}
		}
		m_call_args.clear();
		VM_GOTO(fdata->getAddr());
	} else {
		fdata->getPtr()(m_call_args);
		m_call_args.clear();

		VM_NEXT();
	}
}

// Leave operation
VM_HANDLER(leave)
{
	const StackFrame& frame = m_call_stack.top();

	if (m_call_stack.size() > 1) {
		restoreVars();
	}

	m_call_stack.pop();

	VM_GOTO(frame.ret_addr);
}

// Increment operation
VM_HANDLER(inc)
{
	Value* value = getValue(op.op1);

	if (op.opcode == OP_PRE_INC) {
		value->getType()->increment(value);
		op.result->copy(value);
	} else {
		op.result->copy(value);
		value->getType()->increment(value);
	}

	VM_NEXT();
}

// Decrement operation
VM_HANDLER(dec)
{
	Value* value = getValue(op.op1);

	if (op.opcode == OP_PRE_DEC) {
		value->getType()->decrement(value);
		op.result->copy(value);
	} else {
		op.result->copy(value);
		value->getType()->decrement(value);
	}

	VM_NEXT();
}

// Executes the VM opcodes in a continuation-passing style
void VM::run()
{
	// Loads the opcode handlers
	init();

	for (size_t n = m_inst.size(); m_pc < n;) {
		(this->*m_handlers[m_inst[m_pc].opcode])(m_inst[m_pc]);
	}

	wait();
}

} // clever
