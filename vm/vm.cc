/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifdef CLEVER_DEBUG
#include <stdio.h>
#include "vm/opcode.h"
#endif
#include "compiler/cstring.h"
#include "compiler/scope.h"
#include "compiler/value.h"
#include "types/type.h"
#include "vm/vm.h"

namespace clever {

// VM initialization phase
inline void VM::init()
{
	// Opcode handler mapping
	m_handlers[OP_RET]      = &VM::ret;
	m_handlers[OP_ASSIGN]   = &VM::assignment;
	m_handlers[OP_ADD]      = &VM::add;
	m_handlers[OP_SUB]      = &VM::sub;
	m_handlers[OP_MUL]      = &VM::mul;
	m_handlers[OP_DIV]      = &VM::div;
	m_handlers[OP_MOD]      = &VM::sub;
	m_handlers[OP_JMP]      = &VM::jmp;
	m_handlers[OP_FCALL]    = &VM::fcall;
	m_handlers[OP_LEAVE]    = &VM::leave;
	m_handlers[OP_SEND_VAL] = &VM::send_val;
	m_handlers[OP_JMPZ]     = &VM::jmpz;
	m_handlers[OP_PRE_INC]  = &VM::inc;
	m_handlers[OP_POS_INC]  = &VM::inc;
	m_handlers[OP_PRE_DEC]  = &VM::dec;
	m_handlers[OP_POS_DEC]  = &VM::dec;
}

inline Value* VM::getValue(size_t scope_id, size_t value_id) const
{
	return (*m_scope_pool)[scope_id]->getValue(value_id);
}

#ifdef CLEVER_DEBUG
void VM::dumpOpcodes() const
{
	const char *op_type[] = {
		"UNUSED", "FETCH_VAL", "JMP_ADDR"
	};

	for (size_t i = 0, j = m_inst.size(); i < j; ++i) {
		IR& ir = m_inst[i];
		::printf("[%03ld] %-12s | %3ld:%3ld (%-9s) | %3ld:%3ld (%-9s) | %p\n",
			i,
			get_opcode_name(ir.opcode),
			ir.op1, ir.op1_scope, op_type[ir.op1_type],
			ir.op2, ir.op2_scope, op_type[ir.op2_type],
			ir.result);
	}
}
#endif

// Return operation
VM_HANDLER(ret)
{
	if (m_call_stack.size()) {
		const StackFrame& frame = m_call_stack.top();
		const Value* val = getValue(op.op1_scope, op.op1);

		if (val) {
			m_call_stack.top().ret_val->copy(getValue(op.op1_scope, op.op1));
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
	VM_GOTO(op.op1);
}

// JMPZ operation
VM_HANDLER(jmpz)
{
	Value* value = getValue(op.op1_scope, op.op1);

	if (!value->getInt()) {
		VM_GOTO(op.op2);
	}

	VM_NEXT();
}

// Assignment operation
VM_HANDLER(assignment)
{
	Value* var = getValue(op.op1_scope, op.op1);
	Value* value = getValue(op.op2_scope, op.op2);

	var->copy(value);

	VM_NEXT();
}

// Math sum operation
VM_HANDLER(add)
{
	Value* lhs = getValue(op.op1_scope, op.op1);
	Value* rhs = getValue(op.op2_scope, op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() + rhs->getInt());
	}

	VM_NEXT();
}

// Math subtraction operation
VM_HANDLER(sub)
{
	Value* lhs = getValue(op.op1_scope, op.op1);
	Value* rhs = getValue(op.op2_scope, op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() - rhs->getInt());
	}

	VM_NEXT();
}

// Math multiplication operation
VM_HANDLER(mul)
{
	Value* lhs = getValue(op.op1_scope, op.op1);
	Value* rhs = getValue(op.op2_scope, op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() * rhs->getInt());
	}

	VM_NEXT();
}

// Math division operation
VM_HANDLER(div)
{
	Value* lhs = getValue(op.op1_scope, op.op1);
	Value* rhs = getValue(op.op2_scope, op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() / rhs->getInt());
	}

	VM_NEXT();
}

// Math modulus operation
VM_HANDLER(mod)
{
	Value* lhs = getValue(op.op1_scope, op.op1);
	Value* rhs = getValue(op.op2_scope, op.op2);

	if (lhs->getType() == CLEVER_INT_TYPE
		&& rhs->getType() == CLEVER_INT_TYPE) {
		op.result->setInt(lhs->getInt() % rhs->getInt());
	}

	VM_NEXT();
}

// Receives values to be used in the next function call
VM_HANDLER(send_val)
{
	m_call_args.push_back(getValue(op.op1_scope, op.op1));

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

// Function call operation
VM_HANDLER(fcall)
{
	Value* func = getValue(op.op1_scope, op.op1);
	Function* fdata = static_cast<Function*>(func->getObj());

	if (fdata->isUserDefined()) {
		// Save arguments and local vars on possible recursion
		if (m_call_stack.size()) {
			saveVars();
		}

		// Pushs a new stack frame for the user function call on the call stack
		m_call_stack.push(StackFrame());

		// Sets the return address to the next instruction
		m_call_stack.top().ret_addr = m_pc + 1;

		// Save the function return value address
		m_call_stack.top().ret_val = op.result;

		// Function argument value binding
		if (fdata->hasArgs()) {
			Scope* arg_scope = fdata->getArgVars();

			m_call_stack.top().arg_vars = arg_scope;

			for (size_t i = 0, j = arg_scope->size(); i < j; ++i) {
				Value* arg_val = getValue(
					arg_scope->at(i).scope->getId(), arg_scope->at(i).value_id);
				arg_val->copy(m_call_args[i]);
			}

			m_call_args.clear();
		}

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

	// Go back to the next instruction after the caller
	VM_GOTO(frame.ret_addr);
}

// Increment operation
VM_HANDLER(inc)
{
	Value* value = getValue(op.op1_scope, op.op1);

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
	Value* value = getValue(op.op1_scope, op.op1);

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
}

} // clever
