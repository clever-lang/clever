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
#define VM_EXIT_UNHANDLED_EXCEPTION() goto exit_exception


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

#define THROW_EXCEPTION(val, internal)                     \
	if (EXPECTED(m_try_stack.size())) {                    \
		size_t catch_addr = m_try_stack.top().first;       \
		if (m_try_stack.top().second > 1) {                \
			m_try_stack.pop();                             \
			if (m_try_stack.size()) {                      \
				catch_addr = m_try_stack.top().first;      \
			} else {                                       \
				if (!internal) {                           \
					m_exception = new Value();             \
					m_exception->copy(val);                \
				}                                          \
				VM_EXIT_UNHANDLED_EXCEPTION();             \
			}                                              \
		}                                                  \
		getValue(m_inst[catch_addr].op1)->copy(val);       \
		if (internal) {                                    \
			m_exception->delRef();                         \
			m_exception = NULL;                            \
		}                                                  \
		VM_GOTO(catch_addr);                               \
	} else {                                               \
		if (!internal) {                                   \
			m_exception = new Value();                     \
			m_exception->copy(val);                        \
		}                                                  \
		VM_EXIT_UNHANDLED_EXCEPTION();                     \
	}

namespace clever {

/// Displays an error message
void VM::error(ErrorLevel level, const char* msg) const
{
	switch (level) {
		case VM_WARNING:
			std::cerr << "Warning: " << msg << std::endl;
			break;
		case VM_ERROR:
			std::cerr << "Error: " << msg << std::endl;
			CLEVER_EXIT_FATAL();
			break;
	}
}

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
		case FETCH_CONST:
		case FETCH_TMP:
		case FETCH_VAR:
			::printf("%3zu:%3zu ", op.voffset.first, op.voffset.second);
			break;
		case JMP_ADDR:
			::printf("%7zu ", op.jmp_addr);
			break;
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
	this->f_mutex = const_cast<VM*>(vm)->getMutex();
	this->m_pc = vm->m_pc;

	CallStack tmp_stack = vm->m_call_stack;
	CallQueue tmp_queue;

	while (!tmp_stack.empty()) {
		tmp_queue.push(tmp_stack.top()->activate(NULL));
		tmp_stack.pop();
	}

	while (!tmp_queue.empty()) {
		this->m_call_stack.push(tmp_queue.front());
		tmp_queue.pop();
	}


	this->m_try_stack = vm->m_try_stack;

	this->m_temp_env = vm->m_temp_env->activate(NULL);

	this->m_global_env = vm->m_global_env;
	this->m_const_env = vm->m_const_env;
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

static size_t g_n_threads = 0;


CLEVER_THREAD_FUNC(_thread_control)
{
	VM* vm_handler = static_cast<Thread*>(arg)->vm_handler;

	vm_handler->nextPC();
	vm_handler->run();

	return NULL;
}


void VM::setException(const char* msg)
{
	if (UNEXPECTED(m_exception == NULL)) {
		m_exception = new Value;
	}
	m_exception->setStr(CSTRING(msg));
}

void VM::setException(Value* exception)
{
	if (UNEXPECTED(m_exception == NULL)) {
		m_exception = new Value;
	}
	m_exception->copy(exception);
}

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

			Environment* env = m_call_stack.top();
			size_t ret_addr = env->getRetAddr();

			if (OPCODE.op1.op_type != UNUSED) {
				Value* val = getValue(OPCODE.op1);

				if (val) {
					m_call_stack.top()->getRetVal()->copy(val);
				}
			}

			env->clear();
			CLEVER_SAFE_DELREF(env);
			m_call_stack.pop();

			VM_GOTO(ret_addr);
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
				lhs->getType()->add(getValue(OPCODE.result), lhs, rhs, this);

				if (UNEXPECTED(m_exception != NULL)) {
					THROW_EXCEPTION(m_exception, 1);
				}
			} else {
				error(VM_ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_SUB):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->sub(getValue(OPCODE.result), lhs, rhs, this);
			} else {
				error(VM_ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MUL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mul(getValue(OPCODE.result), lhs, rhs, this);
			} else {
				error(VM_ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_DIV):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->div(getValue(OPCODE.result), lhs, rhs, this);
			} else {
				error(VM_ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MOD):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mod(getValue(OPCODE.result), lhs, rhs, this);
			} else {
				error(VM_ERROR, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_JMP):
		VM_GOTO(OPCODE.op1.jmp_addr);

	OP(OP_FCALL):
		{
			const Value* func = getValue(OPCODE.op1);
			Function* fdata = static_cast<Function*>(func->getObj());
//std::cout << fdata->getName() << std::endl;
			clever_assert_not_null(fdata);

			if (fdata->isUserDefined()) {
				Environment* fenv;

				if (m_call_stack.top()->isActive()) {
					fenv = fdata->getEnvironment()->activate(m_call_stack.top()->getOuter());
				} else {
					fenv = fdata->getEnvironment()->activate(m_call_stack.top());
				}
				m_call_stack.push(fenv);

				fenv->setRetAddr(m_pc + 1);
				fenv->setRetVal(getValue(OPCODE.result));

				if (fdata->hasArgs()) {
					ValueOffset argoff(0,0);

					if (g_n_threads) {
						getMutex()->lock();
					}

					for (size_t i = 0, len = m_call_args.size(); i < len; i++) {
						fenv->getValue(argoff)->copy(m_call_args[i]);
						argoff.second++;
					}

					if (g_n_threads) {
						getMutex()->unlock();
					}
				}

				m_call_args.clear();
				VM_GOTO(fdata->getAddr());
			} else {
				fdata->getPtr()(m_call_args, this);
				m_call_args.clear();
			}
		}
		DISPATCH;

	OP(OP_BTHREAD):
		{

			getMutex()->lock();

			Thread* thread = new Thread;

			const Value* size = getValue(OPCODE.result);
			size_t n_threads = 1;

			if (size != NULL) {
				n_threads = size->getInt();
			}



			for (size_t i = 0; i < n_threads; ++i) {
				printf("<>\n");
				Thread* thread = new Thread;

				thread->vm_handler = new VM(this->m_inst);
				thread->vm_handler->copy(this);

				thread->vm_handler->setChild();

				if (m_thread_pool.size() <= getValue(OPCODE.op2)->getInt()) {
					m_thread_pool.resize(getValue(OPCODE.op2)->getInt() + 1);
				}
				g_n_threads++;
				m_thread_pool[getValue(OPCODE.op2)->getInt()].push_back(thread);

				thread->t_handler.create(_thread_control,
										 static_cast<void*>(thread));
			}
			getMutex()->unlock();

			VM_GOTO(OPCODE.op1.jmp_addr);

			//clever_fatal("Not implemented.");
		}

	OP(OP_WAIT):
		{

			std::vector<Thread*>& thread_list = m_thread_pool[getValue(OPCODE.op1)->getInt()];
			for (size_t i = 0, j = thread_list.size(); i < j; ++i) {
				Thread* t = thread_list.at(i);
				t->t_handler.wait();
				delete t->vm_handler;
				delete t;
			}
			thread_list.clear();

			clever_fatal("Not implemented.");
		}
		DISPATCH;

	OP(OP_ETHREAD):

		if (this->isChild()) {
			getMutex()->lock();

			//for (size_t id = 2, n = m_scope_pool->size(); id < n; ++id) {
				//delete m_scope_pool->at(id);
			//}

			//delete m_scope_pool;

			g_n_threads--;
			getMutex()->unlock();

			VM_EXIT();

			//clever_fatal("Not implemented.");
		}
		DISPATCH;

	OP(OP_LEAVE):
		{
			Environment* env = m_call_stack.top();
			size_t ret_addr = env->getRetAddr();

			env->clear();
			CLEVER_SAFE_DELREF(env);
			m_call_stack.pop();

			VM_GOTO(ret_addr);
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
				error(VM_ERROR, "Cannot increment null value");
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
				error(VM_ERROR, "Cannot increment null value");
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
				error(VM_ERROR, "Cannot decrement null value");
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
				error(VM_ERROR, "Cannot decrement null value");
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
				lhs->getType()->greater(getValue(OPCODE.result), lhs, rhs, this);
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
				lhs->getType()->greater_equal(getValue(OPCODE.result), lhs, rhs, this);
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
				lhs->getType()->less(getValue(OPCODE.result), lhs, rhs, this);
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
				lhs->getType()->less_equal(getValue(OPCODE.result), lhs, rhs, this);
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
				lhs->getType()->equal(getValue(OPCODE.result), lhs, rhs, this);
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
				lhs->getType()->not_equal(getValue(OPCODE.result), lhs, rhs, this);
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
			const Value* valtype = getValue(OPCODE.op1);
			const Type* type = valtype->getType();

			getValue(OPCODE.result)->setType(valtype->getType());

			if (EXPECTED(!type->isPrimitive())) {
				getValue(OPCODE.result)->setObj(type->allocData(&m_call_args));
				m_call_args.clear();
			}
		}
		DISPATCH;

	OP(OP_MCALL):
		{

			const Value* callee = getValue(OPCODE.op1);
			const Value* method = getValue(OPCODE.op2);
			const Type* type = callee->getType();
			MethodPtr ptr;

			if (UNEXPECTED(callee->isNull())) {
				error(VM_ERROR, "Cannot call method from a null value");
			}

			if (EXPECTED((ptr = type->getMethod(method->getStr())))) {
				(type->*ptr)(getValue(OPCODE.result), callee, m_call_args, this);

				m_call_args.clear();

				if (UNEXPECTED(m_exception != NULL)) {
					THROW_EXCEPTION(m_exception, 1);
				}
			} else {
				error(VM_ERROR, "Method not found!");
			}

		}
		DISPATCH;

	OP(OP_SMCALL):
		{
			const Value* valtype = getValue(OPCODE.op1);
			const Type* type = valtype->getType();
			const Value* method = getValue(OPCODE.op2);
			MethodPtr ptr;

			if (EXPECTED((ptr = type->getMethod(method->getStr())))) {
				(type->*ptr)(getValue(OPCODE.result), NULL, m_call_args, this);

				m_call_args.clear();

				if (UNEXPECTED(m_exception != NULL)) {
					THROW_EXCEPTION(m_exception, 1);
				}
			} else {
				error(VM_ERROR, "Method not found!");
			}
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
				error(VM_ERROR, "Property not found!");
			}
		}
		DISPATCH;

	OP(OP_TRY):
		m_try_stack.push(std::pair<size_t, size_t>(OPCODE.op1.jmp_addr, 1));
		DISPATCH;

	OP(OP_CATCH):
		m_try_stack.top().second = 2;
		DISPATCH;

	OP(OP_THROW):
		THROW_EXCEPTION(getValue(OPCODE.op1), 0);
		DISPATCH;

	OP(OP_ETRY):
		m_try_stack.pop();
		DISPATCH;

	OP(OP_HALT):
		VM_EXIT();

	END_OPCODES;

exit_exception:
	clever_fatal("Fatal error: Unhandled exception!\nMessage: %S",
		m_exception->getStr());
exit:
	wait();
}

} // clever
