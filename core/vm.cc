/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifdef CLEVER_DEBUG
#include <stdio.h>
#endif
#include "core/opcode.h"
#include "core/vm.h"
#include "core/value.h"
#include "modules/std/core/function.h"
#include "modules/std/core/array.h"
#include "core/user.h"
#include "types/thread.h"
#include "types/type.h"

#define OPCODE    m_inst[m_pc]

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
void VM::error(ErrorLevel level, const location& loc, const char* format, ...)
{
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	switch (level) {
		case VM_WARNING: out << "Warning: ";     break;
		case VM_ERROR:   out << "Fatal error: "; break;
	}
	vsprintf(out, format, args);

	std::cerr << out.str();

	if (loc.begin.filename) {
		std::cerr << " on " << *loc.begin.filename << " line " << loc.begin.line;
	} else {
		std::cerr << " on line " << loc.begin.line;
	}
	std::cerr << std::endl;

	if (level == VM_ERROR) {
		CLEVER_EXIT_FATAL();
	}
}

/// Fetchs a Value ptr according to the operand type
CLEVER_FORCE_INLINE Value* VM::getValue(const Operand& operand) const
{
	const Environment* source;

	switch (operand.op_type) {
		case FETCH_CONST: source = m_const_env;        break;
		case FETCH_VAR:   source = m_call_stack.top(); break;
		case FETCH_TMP:   source = m_temp_env;         break;
		default:
			return NULL;
	}
	clever_assert_not_null(source);

	return source->getValue(operand.voffset);
}

#ifdef CLEVER_DEBUG
void VM::dumpOperand(const Operand& op)
{
	const char *type[] = {
		"UNUSED", "FETCH_VAR", "FETCH_CONST", "FETCH_TMP", "JMP_ADDR"
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
		case UNUSED:
			::printf("        ");
			break;
	}
	::printf(" (%-11s) | ", type[op.op_type]);
}

void VM::dumpOpcodes() const
{
	for (size_t i = 0, j = m_inst.size(); i < j; ++i) {
		const IR& ir = m_inst[i];
		::printf("[%03zu] %-12s |", i, get_opcode_name(ir.opcode));
		dumpOperand(ir.op1);
		dumpOperand(ir.op2);
		dumpOperand(ir.result);
		::printf("\n");
	}
	std::cout << std::endl;
}
#endif

// Make a copy of VM instance
void VM::copy(const VM* vm, bool deep)
{
	f_mutex = const_cast<VM*>(vm)->getMutex();
	m_pc = vm->m_pc;
	m_try_stack = vm->m_try_stack;

	if (deep) {
		this->m_temp_env = new Environment();
		this->m_temp_env->copy(vm->m_temp_env);
	} else {
		this->m_temp_env = vm->m_temp_env;
	}

	m_global_env = vm->m_global_env;
	m_call_stack = vm->m_call_stack;
	m_const_env = vm->m_const_env;
}

void VM::wait()
{
	ThreadPool::const_iterator it(m_thread_pool.begin()), end(m_thread_pool.end());

	while (it != end) {
		for (size_t i = 0, j = it->size(); i < j; ++i) {
			it->at(i)->t_handler.wait();

			clever_delete_var(it->at(i)->vm_handler);
			clever_delete(it->at(i));
		}
		++it;
	}

	m_thread_pool.clear();
}

// Function parameter binding
static CLEVER_FORCE_INLINE void _param_binding(const Function* func, Environment* fenv,
	std::vector<Value*>* args)
{
	size_t nargs = 0;

	if (EXPECTED(func->hasArgs() && args != NULL)) {
		size_t num_args = args->size();
		ValueOffset argoff(0,0);

		if (UNEXPECTED(num_args > func->getNumArgs())) {
			num_args = func->getNumArgs();
		}

		for (size_t i = 0, len = num_args; i < len; ++i) {
			fenv->getValue(argoff)->copy(args->at(i));
			argoff.second++;
			++nargs;
		}
	}

	if (UNEXPECTED(func->isVariadic())) {
		ArrayObject* arr = new ArrayObject;

		if (EXPECTED(args && (args->size() - nargs) > 0)) {
			for (size_t i = nargs, j = args->size(); i < j; ++i) {
				arr->getData().push_back(args->at(i)->clone());
			}
		}

		Value* vararg = fenv->getValue(ValueOffset(0, func->getNumArgs()));
		vararg->setObj(CLEVER_ARRAY_TYPE, arr);
	}
}

// Prepares an user function/method call
CLEVER_FORCE_INLINE void VM::prepareCall(const Function* func, Environment* env)
{
	getMutex()->lock();
	Environment* fenv;

	if (env) {
		fenv = func->getEnvironment()->activate(env);
	} else if (m_call_stack.top()->isActive()) {
		fenv = func->getEnvironment()->activate(m_call_stack.top()->getOuter());
	} else {
		fenv = func->getEnvironment()->activate(func->getEnvironment()->getOuter());
	}
	m_call_stack.push(fenv);

	fenv->setRetAddr(m_pc + 1);
	fenv->setRetVal(getValue(OPCODE.result));

	if (m_call_args.size() < func->getNumRequiredArgs()
		|| (m_call_args.size() > func->getNumArgs()
			&& !func->isVariadic())) {
		error(VM_ERROR, OPCODE.loc, "Wrong number of parameters");
	}

	_param_binding(func, fenv, &m_call_args);

	m_call_args.clear();
	getMutex()->unlock();
}

CLEVER_FORCE_INLINE void VM::createInstance(const Type* type, Value* instance) const
{
	if (type->isUserDefined()) {
		const UserType* utype = static_cast<const UserType*>(type);
		UserObject* obj = static_cast<UserObject*>(instance->getObj());

		obj->setEnvironment(utype->getEnvironment()->activate(m_call_stack.top()));
	}
}

// Executes the supplied function
Value* VM::runFunction(const Function* func, std::vector<Value*>* args)
{
	Value* result = new Value;

	if (func->isInternal()) {
		func->getFuncPtr()(result, *args, this, &m_exception);
	} else {
		Environment* fenv = func->getEnvironment()->activate(m_call_stack.top());
		fenv->setRetVal(result);
		fenv->setRetAddr(m_inst.size()-1);

		m_call_stack.push(fenv);
		m_call_args.clear();

		_param_binding(func, fenv, args);

		size_t saved_pc = m_pc;
		m_pc = func->getAddr();
		run();
		m_pc = saved_pc;
	}

	return result;
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
		if (EXPECTED(m_call_stack.size() > 1)) {
			Environment* env = m_call_stack.top();
			size_t ret_addr = env->getRetAddr();

			if (EXPECTED(OPCODE.op1.op_type != UNUSED)) {
				Value* val = getValue(OPCODE.op1);
				clever_assert_not_null(val);
				m_call_stack.top()->getRetVal()->copy(val);
			}

			clever_delref(env);
			m_call_stack.pop();

			VM_GOTO(ret_addr);
		} else {
			goto exit;
		}
		DISPATCH;

	OP(OP_ASSIGN):
		{
			Value* var = getValue(OPCODE.op1);
			const Value* value = getValue(OPCODE.op2);

			// Checks if this assignment is allowed (non-const variable or
			// const variable declaration).
			if (EXPECTED(var->isAssignable())) {
				var->copy(value);
			} else {
				// TODO(muriloadriano): improve this message to show the symbol
				// name and the line to the user.
				error(VM_ERROR, OPCODE.loc, "Cannot assign to a const variable!");
			}
		}
		DISPATCH;

	OP(OP_ADD):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->add(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_SUB):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->sub(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MUL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mul(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_DIV):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->div(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_MOD):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->mod(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Operation cannot be executed on null value");
			}
		}
		DISPATCH;

	OP(OP_JMP):
		VM_GOTO(OPCODE.op1.jmp_addr);

	OP(OP_FCALL):
		{
			const Value* fval = getValue(OPCODE.op1);

			clever_assert_not_null(fval);

			if (UNEXPECTED(fval->isNull())) {
				error(VM_ERROR, OPCODE.loc, "Cannot make a call from null value");
			}

			if (UNEXPECTED(!fval->isFunction())) {
				error(VM_ERROR, OPCODE.loc, "Cannot make a call from %T type", fval->getType());
			}

			Function* func = static_cast<Function*>(fval->getObj());
			clever_assert_not_null(func);

			if (func->isUserDefined()) {
				prepareCall(func);

				VM_GOTO(func->getAddr());
			} else {
				func->getFuncPtr()(getValue(OPCODE.result), m_call_args, this, &m_exception);
				m_call_args.clear();

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			}
		}
		DISPATCH;

	OP(OP_BTHREAD):
		{
			getMutex()->lock();

			const Value* tval = getValue(OPCODE.op2);
			Thread* tdata = static_cast<Thread*>(tval->getObj());
			clever_assert_not_null(tdata);

			const Value* size = getValue(OPCODE.result);
			size_t n_threads = 1;

			if (size != NULL) {
				n_threads = size->getInt();
			}

			tdata->setNThreads(n_threads);

			getMutex()->unlock();

			VM_GOTO(OPCODE.op1.jmp_addr);
		}

	OP(OP_ETHREAD):
		if (EXPECTED(isChild())) {
			getMutex()->lock();

			if (EXPECTED(m_call_stack.size())) {
				Environment* env = m_call_stack.top();

				clever_delref(env);
				m_call_stack.pop();
			}

			Environment* env = m_temp_env;
			Environment* other = NULL;

			while (env != NULL) {
				other = env->getOuter();
				env = other;
			}
			clever_delete_var(m_temp_env);

			getMutex()->unlock();
			goto exit;
		}
		DISPATCH;

	OP(OP_LEAVE):
		{
			Environment* env = m_call_stack.top();
			size_t ret_addr = env->getRetAddr();

			clever_delref(env);
			m_call_stack.pop();

			VM_GOTO(ret_addr);
		}

	OP(OP_SEND_VAL):
		m_call_args.push_back(getValue(OPCODE.op1));
		DISPATCH;

	OP(OP_JMPZ):
		{
			const Value* value = getValue(OPCODE.op1);

			if (!value->asBool()) {
				if (OPCODE.result.op_type != UNUSED) {
					getValue(OPCODE.result)->setBool(false);
				}
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
			if (OPCODE.result.op_type != UNUSED) {
				getValue(OPCODE.result)->setBool(true);
			}
		}
		DISPATCH;

	OP(OP_PRE_INC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				value->getType()->increment(value, this, &m_exception);
				getValue(OPCODE.result)->copy(value);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Cannot increment null value");
			}
		}
		DISPATCH;

	OP(OP_POS_INC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				getValue(OPCODE.result)->copy(value);
				value->getType()->increment(value, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Cannot increment null value");
			}
		}
		DISPATCH;

	OP(OP_PRE_DEC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				value->getType()->decrement(value, this, &m_exception);
				getValue(OPCODE.result)->copy(value);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Cannot decrement null value");
			}
		}
		DISPATCH;

	OP(OP_POS_DEC):
		{
			Value* value = getValue(OPCODE.op1);

			if (EXPECTED(!value->isNull())) {
				getValue(OPCODE.result)->copy(value);
				value->getType()->decrement(value, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				error(VM_ERROR, OPCODE.loc, "Cannot decrement null value");
			}
		}
		DISPATCH;

	OP(OP_JMPNZ):
		{
			const Value* value = getValue(OPCODE.op1);

			if (value->asBool()) {
				if (OPCODE.result.op_type != UNUSED) {
					getValue(OPCODE.result)->setBool(true);
				}
				VM_GOTO(OPCODE.op2.jmp_addr);
			}
			if (OPCODE.result.op_type != UNUSED) {
				getValue(OPCODE.result)->setBool(false);
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
				lhs->getType()->greater(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
			}
		}
		DISPATCH;

	OP(OP_GEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->greater_equal(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
			}
		}
		DISPATCH;

	OP(OP_LESS):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->less(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
			}
		}
		DISPATCH;

	OP(OP_LEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->less_equal(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
			}
		}
		DISPATCH;

	OP(OP_EQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->equal(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
			}
		}
		DISPATCH;

	OP(OP_NEQUAL):
		{
			const Value* lhs = getValue(OPCODE.op1);
			const Value* rhs = getValue(OPCODE.op2);

			if (EXPECTED(!lhs->isNull() && !rhs->isNull())) {
				lhs->getType()->not_equal(getValue(OPCODE.result), lhs, rhs, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			} else {
				getValue(OPCODE.result)->setBool(false);
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
			const Function* ctor = type->getConstructor();

			if (EXPECTED(ctor != NULL)) {
				Value* instance = getValue(OPCODE.result);

				(type->*ctor->getMethodPtr())(instance,
					NULL, m_call_args, this, &m_exception);

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}

				if (UNEXPECTED(instance->isNull())) {
					error(VM_ERROR, OPCODE.loc,
						"Cannot create object of type %T", type);
				} else {
					createInstance(type, instance);
				}
			}
			m_call_args.clear();
		}
		DISPATCH;

	OP(OP_MCALL):
		{
			const Value* callee = getValue(OPCODE.op1);
			const Value* method = getValue(OPCODE.op2);

			if (UNEXPECTED(callee->isNull())) {
				error(VM_ERROR, OPCODE.loc,
					"Cannot call method `%S' from a null value", method->getStr());
			}

			const Type* type = callee->getType();
			const Function* func = type->getMethod(method->getStr());

			if (UNEXPECTED(func == NULL)) {
				error(VM_ERROR, OPCODE.loc, "Method `%T::%S' not found!",
					type, method->getStr());
			}

			if (func->isUserDefined()) {
				prepareCall(func,
					static_cast<UserObject*>(callee->getObj())->getEnvironment());

				VM_GOTO(func->getAddr());
			} else {
				if (UNEXPECTED(func->isStatic())) {
					error(VM_ERROR, OPCODE.loc,
						"Method `%T::%S' cannot be called non-statically",
						type, method->getStr());
				} else {
					(type->*func->getMethodPtr())(getValue(OPCODE.result),
						callee, m_call_args, this, &m_exception);

					m_call_args.clear();

					if (UNEXPECTED(m_exception.hasException())) {
						goto throw_exception;
					}
				}
			}
		}
		DISPATCH;

	OP(OP_SMCALL):
		{
			const Value* valtype = getValue(OPCODE.op1);
			const Type* type = valtype->getType();
			const Value* method = getValue(OPCODE.op2);
			const Function* func = type->getMethod(method->getStr());

			if (EXPECTED(func != NULL)) {
				if (UNEXPECTED(!func->isStatic())) {
					error(VM_ERROR, OPCODE.loc,
						"Method `%T::%S' cannot be called statically",
						type, method->getStr());
				} else {
					(type->*func->getMethodPtr())(getValue(OPCODE.result),
						NULL, m_call_args, this, &m_exception);

					m_call_args.clear();

					if (UNEXPECTED(m_exception.hasException())) {
						goto throw_exception;
					}
				}
			} else {
				error(VM_ERROR, OPCODE.loc,
					"Method `%T::%S' not found!", type, method->getStr());
			}
		}
		DISPATCH;

	OP(OP_PROP_ACC):
		{
			const Value* obj = getValue(OPCODE.op1);
			const Value* name = getValue(OPCODE.op2);

			if (UNEXPECTED(obj->isNull())) {
				error(VM_ERROR, OPCODE.loc,
					"Cannot perform property access from null value");
			}

			const Value* value = obj->getType()->getProperty(name->getStr());

			if (EXPECTED(value != NULL)) {
				getValue(OPCODE.result)->copy(value);
			} else {
				error(VM_ERROR, OPCODE.loc, "Property `%T::%S' not found!",
					obj->getType(), name->getStr());
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
		m_exception.setException(getValue(OPCODE.op1));
		goto throw_exception;

throw_exception:
		if (EXPECTED(m_try_stack.size())) {
			size_t catch_addr = m_try_stack.top().first;
			if (m_try_stack.top().second > 1) {
				m_try_stack.pop();
				if (!m_try_stack.size()) {
					goto exit_exception;
				}
				catch_addr = m_try_stack.top().first;
			}
			getValue(m_inst[catch_addr].op1)->copy(m_exception.getException());
			m_exception.getException()->delRef();
			m_exception.clear();
			VM_GOTO(catch_addr);
		}
		goto exit_exception;

	OP(OP_ETRY):
		m_try_stack.pop();
		DISPATCH;

	OP(OP_HALT):
		goto exit;

	END_OPCODES;

exit_exception:
	clever_fatal("Fatal error: Unhandled exception!\nMessage: %v",
		m_exception.getException());

exit:
	wait();
}

} // clever
