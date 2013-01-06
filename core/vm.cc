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
#include "core/vm.h"
#include "core/scope.h"
#include "core/value.h"
#include "types/type.h"
#include "types/function.h"

#define OPCODE m_inst[m_pc]
#define VM_EXIT() goto exit

#if CLEVER_GCC_VERSION > 0
# define OP(name)    name
# define OPCODES     const static void* labels[] = { OP_LABELS }; goto *labels[m_inst[m_pc].opcode]
# define DISPATCH    ++m_pc; goto *labels[m_inst[m_pc].opcode]
# define END_OPCODES
# define VM_GOTO(n)  m_pc = n; goto *labels[m_inst[m_pc].opcode]
#else
# define OP(name)    case name
# define OPCODES     for (;;) { switch (m_inst[m_pc].opcode) {
# define DISPATCH    ++m_pc; break
# define END_OPCODES EMPTY_SWITCH_DEFAULT_CASE(); } }
# define VM_GOTO(n)  m_pc = n; break
#endif

namespace clever {

/// Displays an error message
void VM::error(ErrorLevel level, const char* msg) const
{
	switch (level) {
		case WARNING:
			std::cerr << "Warning: " << msg << std::endl;
			break;
		case ERROR:
			std::cerr << "Error: " << msg << std::endl;
			CLEVER_EXIT_FATAL();
			break;
	}
}

/*/// Fetchs a Type ptr from the Symbol table
CLEVER_FORCE_INLINE const Type* VM::getType(Operand& operand) const
{
	return (*m_scope_pool)[operand.scope_id]->getType(operand.voffset);
}*/

/// Fetchs a Value ptr according to the operand type
CLEVER_FORCE_INLINE Value* VM::getValue(Operand& operand) const
{
	Environment* source;

	switch (operand.op_type) {
	case FETCH_CONST: source = m_const_env; break;
	case FETCH_VAR: source = m_call_stack.top(); break;
	case FETCH_TMP: source = m_temp_env; break;
	default:
		return NULL;
	}

	clever_assert_not_null(source);

	return source->getValue(operand.voffset);
}

#ifdef CLEVER_DEBUG
void VM::dumpOperand(Operand& op) const
{
	const char *type[] = {
		"UNUSED", "FETCH_VAR", "FETCH_CONST", "FETCH_TYPE", "FETCH_TMP", "JMP_ADDR"
	};

	switch (op.op_type) {
		case FETCH_VAR:
			::printf("%3zu:%3zu ", op.voffset.first, op.voffset.second);
			break;
		case JMP_ADDR:
			::printf("%7zu ", op.jmp_addr);
			break;
		case FETCH_CONST:
		case FETCH_TMP:
		case FETCH_TYPE:
			::printf("%7zu ", op.voffset.first);
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
		::printf("[%03zu] %-12s |", i, get_opcode_name(ir.opcode));
		dumpOperand(ir.op1);
		dumpOperand(ir.op2);
		dumpOperand(ir.result);
		::printf("\n");
	}
}
#endif

// Make a copy of VM instance
void VM::copy(const VM* vm)
{
	/*
	this->f_mutex = const_cast<VM*>(vm)->getMutex();
	this->m_pc = vm->m_pc;

	this->f_mutex->lock();
	this->m_scope_pool = new ScopePool;

	this->m_try_stack = vm->m_try_stack;
	this->m_scope_pool->push_back(const_cast<Scope*>(vm->m_scope_pool->at(0)));
	this->m_scope_pool->push_back(const_cast<Scope*>(vm->m_scope_pool->at(1)));

	for (size_t id = 2, n = vm->m_scope_pool->size(); id < n; ++id) {
		Scope* scope = new Scope;

		scope->copy(vm->m_scope_pool->at(id));

		this->m_scope_pool->push_back(scope);
	}
	this->f_mutex->unlock();

	this->m_temp_env = vm->m_temp_env;
	this->m_const_env = vm->m_const_env;
	*/
}

void VM::wait()
{
	ThreadPool::iterator it = m_thread_pool.begin(), ed = m_thread_pool.end();

	while (it != ed) {
		for (size_t i = 0, j = it->size(); i < j; ++i) {
			it->at(i)->t_handler.wait();

			delete it->at(i)->vm_handler;
			delete it->at(i);
		}

		++it;
	}
	m_thread_pool.clear();
}

//static size_t g_n_threads = 0;

/*static void* _thread_control(void* arg)
{
	VM* vm_handler = static_cast<Thread*>(arg)->vm_handler;

	vm_handler->nextPC();
	vm_handler->run();

	return NULL;
}*/

// Executes the VM opcodes
// When building on GCC the code will use direct threading code, otherwise
// the switch-based dispatching is used
void VM::run()
{
	if (m_call_stack.empty()) {
		m_call_stack.push(m_global_env);
	}

	OPCODES;
	OP(OP_RET):
		if (m_call_stack.size()) {
			/*const StackFrame& frame = m_call_stack.top();

			if (OPCODE.op1.op_type != UNUSED) {
				const Value* val = getValue(OPCODE.op1);

				if (val) {
					m_call_stack.top().ret_val->copy(getValue(OPCODE.op1));
				}
			}
			m_call_stack.pop();

			// Go back to the caller
			VM_GOTO(frame.ret_addr);*/
			clever_fatal("Not implemented.");
		} else {
			VM_EXIT();
		}
		DISPATCH;

	OP(OP_ASSIGN):
		{
			Value* var = getValue(OPCODE.op1);
			const Value* value = getValue(OPCODE.op2);

			var->copy(value);
		}
		DISPATCH;

	OP(OP_ADD):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->add(getValue(OPCODE.result), lhs, rhs);
			} else {
				error(ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_SUB):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->sub(getValue(OPCODE.result), lhs, rhs);
			} else {
				error(ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MUL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mul(getValue(OPCODE.result), lhs, rhs);
			} else {
				error(ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_DIV):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->div(getValue(OPCODE.result), lhs, rhs);
			} else {
				error(ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MOD):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mod(getValue(OPCODE.result), lhs, rhs);
			} else {
				error(ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_JMP):
		VM_GOTO(OPCODE.op1.jmp_addr);

	OP(OP_FCALL):
		{
			const Value* func = getValue(OPCODE.op1);
			Function* fdata = static_cast<Function*>(func->getObj());

			clever_assert_not_null(fdata);

			if (fdata->isUserDefined()) {
				/*
				m_call_stack.push(StackFrame());
				m_call_stack.top().ret_addr = m_pc + 1;
				m_call_stack.top().ret_val  = getValue(OPCODE.result);

				// Function argument value binding
				if (fdata->hasArgs()) {
					Scope* arg_scope = fdata->getArgVars();

					m_call_stack.top().arg_vars = arg_scope;

					if (g_n_threads) {
						getMutex()->lock();
					}

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

					if (g_n_threads) {
						getMutex()->unlock();
					}

				}
				m_call_args.clear();
				VM_GOTO(fdata->getAddr());
				*/
				clever_fatal("Not implemented.");
			} else {
				fdata->getPtr()(m_call_args, this);
				m_call_args.clear();
			}
		}
		DISPATCH;

	OP(OP_BTHREAD):
		{
		/*
			Thread* thread = new Thread;

			thread->vm_handler = new VM(this->m_inst);
			thread->vm_handler->copy(this);

			thread->vm_handler->setChild();
			getMutex()->lock();

			if (m_thread_pool.size() <= OPCODE.op2.value_id) {
				m_thread_pool.resize(OPCODE.op2.value_id + 1);
			}
			g_n_threads++;
			getMutex()->unlock();

			m_thread_pool[OPCODE.op2.value_id].push_back(thread);
			thread->t_handler.create(_thread_control,
									 static_cast<void*>(thread));

			VM_GOTO(OPCODE.op1.value_id);
			*/
			clever_fatal("Not implemented.");
		}

	OP(OP_WAIT):
		{
		/*
			std::vector<Thread*>& thread_list = m_thread_pool[OPCODE.op1.value_id];
			for (size_t i = 0, j = thread_list.size(); i < j; ++i) {
				Thread* t = thread_list.at(i);
				t->t_handler.wait();
				delete t->vm_handler;
				delete t;
			}
			thread_list.clear();
			*/
			clever_fatal("Not implemented.");
		}
		DISPATCH;

	OP(OP_ETHREAD):

		if (this->isChild()) {
		/*
			getMutex()->lock();

			for (size_t id = 2, n = m_scope_pool->size(); id < n; ++id) {
				delete m_scope_pool->at(id);
			}

			delete m_scope_pool;
			g_n_threads--;
			getMutex()->unlock();

			VM_EXIT();
			*/
			clever_fatal("Not implemented.");
		}
		DISPATCH;

	OP(OP_LEAVE):
		{
		/*
			const StackFrame& frame = m_call_stack.top();

			m_call_stack.pop();

			VM_GOTO(frame.ret_addr);*/
		}

	OP(OP_SEND_VAL):
		m_call_args.push_back(getValue(OPCODE.op1));
		DISPATCH;

	OP(OP_JMPZ):
		{
			const Value* value = getValue(OPCODE.op1);

			if (value->isNull() || !value->asBool()) {
				if (OPCODE.result.op_type != UNUSED) {
					getValue(OPCODE.result)->setNull(); // TODO: boolean
				}
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
			if (OPCODE.result.op_type != UNUSED) {
				getValue(OPCODE.result)->setInt(1); // TODO: boolean
			}
		}
		DISPATCH;

	OP(OP_PRE_INC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				value->getType()->increment(value);
				getValue(OPCODE.result)->copy(value);
			} else {
				error(VM::ERROR, "Cannot increment null value");
			}
		}
		DISPATCH;

	OP(OP_POS_INC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				getValue(OPCODE.result)->copy(value);
				value->getType()->increment(value);
			} else {
				error(VM::ERROR, "Cannot increment null value");
			}
		}
		DISPATCH;

	OP(OP_PRE_DEC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				value->getType()->decrement(value);
				getValue(OPCODE.result)->copy(value);
			} else {
				error(VM::ERROR, "Cannot decrement null value");
			}
		}
		DISPATCH;

	OP(OP_POS_DEC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				getValue(OPCODE.result)->copy(value);
				value->getType()->decrement(value);
			} else {
				error(VM::ERROR, "Cannot decrement null value");
			}
		}
		DISPATCH;

	OP(OP_JMPNZ):
		{
			const Value* value = getValue(OPCODE.op1);

			if (!value->isNull() || value->asBool()) {
				if (OPCODE.result.op_type != UNUSED) {
					getValue(OPCODE.result)->setInt(1); // TODO: boolean
				}
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
			if (OPCODE.result.op_type != UNUSED) {
				getValue(OPCODE.result)->setNull(); // TODO: boolean
			}
		}
		DISPATCH;

	OP(OP_AND):
		{
			const Value* lhs = getValue(OPCODE.op1);

			if (!lhs->asBool()) {
				getValue(OPCODE.result)->setNull();
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
			getValue(OPCODE.result)->copy(lhs);
		}
		DISPATCH;

	OP(OP_OR):
		{
			const Value* lhs = getValue(OPCODE.op1);

			if (lhs->asBool()) {
				getValue(OPCODE.result)->copy(lhs);
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
		}
		DISPATCH;

	OP(OP_GREATER):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->greater(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_GEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->greater_equal(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_LESS):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->less(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_LEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->not_equal(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_EQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->equal(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_NEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->not_equal(getValue(OPCODE.result), lhs, rhs);
			} else {
				// TODO(Felipe): boolean false
				getValue(OPCODE.result)->setInt(0);
			}
		}
		DISPATCH;

	OP(OP_LOCK):
		getMutex()->lock();
		DISPATCH;

	OP(OP_UNLOCK):
		getMutex()->unlock();
		DISPATCH;

	OP(OP_NEW):
		{
		/*
			const Type* type = getType(OPCODE.op1);

			getValue(OPCODE.result)->setType(type);

			if (EXPECTED(!type->isPrimitive())) {
				getValue(OPCODE.result)->setObj(type->allocData(&m_call_args));
				m_call_args.clear();
			}
			*/
		}
		DISPATCH;

	OP(OP_MCALL):
		{
		/*
			const Value* callee = getValue(OPCODE.op1);
			const Value* method = getValue(OPCODE.op2);
			const Type* type = callee->getType();
			MethodPtr ptr;

			if (UNEXPECTED(callee->isNull())) {
				error(ERROR, "Cannot call method from a null value");
			}

			if (EXPECTED((ptr = type->getMethod(method->getStr())))) {
				(type->*ptr)(getValue(OPCODE.result), callee, m_call_args);
				m_call_args.clear();
			} else {
				error(ERROR, "Method not found!");
			}
			*/
		}
		DISPATCH;

	OP(OP_SMCALL):
		{
		/*
			const Type* type = getType(OPCODE.op1);
			const Value* method = getValue(OPCODE.op2);
			MethodPtr ptr;

			if (EXPECTED((ptr = type->getMethod(method->getStr())))) {
				(type->*ptr)(getValue(OPCODE.result), NULL, m_call_args);
				m_call_args.clear();
			} else {
				error(ERROR, "Method not found!");
			}
			*/
		}
		DISPATCH;

	OP(OP_PROP_ACC):
		{
			const Value* obj = getValue(OPCODE.op1);
			const Value* prop_name = getValue(OPCODE.op2);
			const Value* prop_value;

			if (EXPECTED((prop_value = obj->getType()->getProperty(prop_name->getStr())))) {
				getValue(OPCODE.result)->copy(prop_value);
				m_call_args.clear();
			} else {
				error(ERROR, "Property not found!");
			}
		}
		DISPATCH;

	OP(OP_TRY):
		m_try_stack.push(OPCODE.op1.jmp_addr);
		DISPATCH;

	OP(OP_CATCH):
		DISPATCH;

	OP(OP_THROW):
		if (EXPECTED(m_try_stack.size())) {
			size_t catch_addr = m_try_stack.top();

			getValue(m_inst[catch_addr].op1)->copy(getValue(OPCODE.op1));

			VM_GOTO(catch_addr);
		}
		DISPATCH;

	OP(OP_ETRY):
		m_try_stack.pop();
		DISPATCH;

	OP(OP_HALT):
		VM_EXIT();

	END_OPCODES;
exit:
	wait();
}

} // clever
