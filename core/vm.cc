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
#include "core/location.hh"
#include "core/user.h"
#include "types/thread.h"
#include "core/type.h"
#include "modules/std/core/function.h"
#include "modules/std/core/array.h"

#define OPCODE    m_inst[m_pc]

#if CLEVER_GCC_VERSION > 0 && !defined(CLEVER_NOGNU)
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
void VM::error(const location& loc, const char* format, ...)
{
	std::ostringstream out;
	va_list args;

	out << "Fatal error: ";

	va_start(args, format);
	vsprintf(out, format, args);

	std::cerr << out.str();

	if (loc.begin.filename) {
		std::cerr << " on " << *loc.begin.filename << " line " << loc.begin.line;
	} else {
		std::cerr << " on line " << loc.begin.line;
	}
	std::cerr << std::endl;

	CLEVER_EXIT_FATAL();
}

/// Dumps the current stack trace
void VM::dumpStackTrace(std::ostringstream& out)
{
	if (m_call_stack.empty()) {
		return;
	}

	out << std::endl << "Stack trace:" << std::endl;

	do {
		const CallStackEntry& entry = m_call_stack.top();

		if (entry.loc) {
			if (entry.loc->begin.filename) {
				out << "# " << *entry.loc->begin.filename << ":";
			} else {
				out << "# <command line>:";
			}
			out << entry.loc->begin.line << std::endl;
		}

		m_call_stack.pop();
	} while (!m_call_stack.empty());
}

/// Fetchs a Value ptr according to the operand type
CLEVER_FORCE_INLINE Value* VM::getValue(const Operand& operand) const
{
	const Environment* source;

	switch (operand.op_type) {
		case FETCH_CONST: source = m_const_env;                          break;
		case FETCH_VAR:   source = m_call_stack.top().env;               break;
		case FETCH_TMP:   source = m_call_stack.top().env->getTempEnv(); break;
		default:  	      return NULL;
	}
	clever_assert_not_null(source);

	return source->getValue(operand.voffset);
}

/// Fetchs and change a Value pointer in the current temporary environment
CLEVER_FORCE_INLINE Value* VM::setTempValue(const Operand& operand,
	Value* value) const
{
	Environment* source = m_call_stack.top().env->getTempEnv();
	Value* current = source->getValue(operand.voffset);

	clever_delref(current);
	source->setData(operand.voffset.second, value);

	return value;
}

#ifdef CLEVER_DEBUG
void VM::dumpOperand(const Operand& op)
{
	const char* type[] = {
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
	f_mutex      = const_cast<VM*>(vm)->getMutex();
	m_pc         = vm->m_pc;
	m_inst       = vm->m_inst;
	m_try_stack  = vm->m_try_stack;
	m_global_env = vm->m_global_env;
	m_call_stack = vm->m_call_stack;
	m_const_env  = vm->m_const_env;
}

// Function parameter binding
static CLEVER_FORCE_INLINE void _param_binding(const Function* func,
	Environment* fenv, std::vector<Value*>* args)
{
	size_t nargs = 0;

	if (EXPECTED(func->hasArgs() && args != NULL)) {
		size_t num_args = args->size();
		ValueOffset argoff(0,0);

		if (UNEXPECTED(num_args > func->getNumArgs())) {
			num_args = func->getNumArgs();
		}

		for (size_t i = 0, len = num_args; i < len; ++i) {
			fenv->getValue(argoff)->copy((*args)[i]);
			argoff.second++;
			++nargs;
		}
	}

	if (UNEXPECTED(func->isVariadic())) {
		ArrayObject* arr = new ArrayObject;

		if (EXPECTED(args && (args->size() - nargs) > 0)) {
			for (size_t i = nargs, j = args->size(); i < j; ++i) {
				arr->getData().push_back((*args)[i]->clone());
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
	Environment* fenv = func->getEnvironment()->activate(env);

	fenv->setRetAddr(m_pc + 1);
	fenv->setRetVal(getValue(OPCODE.result));

	m_call_stack.push(CallStackEntry(fenv, &OPCODE.loc));

	if (m_call_args.size() < func->getNumRequiredArgs()
		|| (m_call_args.size() > func->getNumArgs()
			&& !func->isVariadic())) {
		error(OPCODE.loc, "Wrong number of parameters");
	}

	_param_binding(func, fenv, &m_call_args);

	m_call_args.clear();
	getMutex()->unlock();
}

// Creates a new instance for user objects
CLEVER_FORCE_INLINE void VM::createInstance(const Type* type, Value* instance)
{
	if (!type->isUserDefined()) {
		return;
	}

	const UserType* utype = static_cast<const UserType*>(type);
	UserObject* uobj = static_cast<UserObject*>(instance->getObj());

	uobj->setEnvironment(utype->getEnvironment()->activate());
	uobj->getEnvironment()->getValue(ValueOffset(0,0))->copy(instance);

	if (m_obj_store.empty()) {
		m_obj_store.push(std::vector<Environment*>());
	}
	m_obj_store.top().push_back(uobj->getEnvironment());
}

// Executes the supplied function
Value* VM::runFunction(const Function* func, std::vector<Value*>* args)
{
	Value* result = new Value;

	if (func->isInternal()) {
		func->getFuncPtr()(result, *args, this, &m_exception);
	} else {
		Environment* fenv = func->getEnvironment()->activate();
		fenv->setRetVal(result);
		fenv->setRetAddr(m_inst.size()-1);

		m_call_stack.push(CallStackEntry(fenv, &OPCODE.loc));
		m_call_args.clear();

		_param_binding(func, fenv, args);

		m_obj_store.push(std::vector<Environment*>());

		size_t saved_pc = m_pc;
		m_pc = func->getAddr();
		run();
		m_pc = saved_pc;
	}

	return result;
}

// Performs binary operation
CLEVER_FORCE_INLINE void VM::binOp(const IR& op)
{
	const Value* lhs = getValue(op.op1);
	const Value* rhs = getValue(op.op2);
	const Type* type = lhs->getType();

	if (UNEXPECTED(lhs->isNull() || (op.op2.op_type != UNUSED && rhs->isNull()))) {
		error(op.loc, "Operation cannot be executed on null value");
	}

	switch (op.opcode) {
		// Arithmetic
		case OP_ADD: type->add(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_SUB: type->sub(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_MUL: type->mul(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_DIV: type->div(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_MOD: type->mod(getValue(op.result), lhs, rhs, this, &m_exception); break;
		// Bitwise
		case OP_BW_AND: type->bw_and(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_BW_OR: 	type->bw_or(getValue(op.result),  lhs, rhs, this, &m_exception); break;
		case OP_BW_XOR:	type->bw_xor(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_BW_RS:	type->bw_rs(getValue(op.result),  lhs, rhs, this, &m_exception); break;
		case OP_BW_LS:	type->bw_ls(getValue(op.result),  lhs, rhs, this, &m_exception); break;
		// Unary
		case OP_NOT:    type->not_op(getValue(op.result), lhs, this, &m_exception); break;
		case OP_BW_NOT:	type->bw_not(getValue(op.result), lhs, this, &m_exception);	break;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}

/// Performs logical operation
CLEVER_FORCE_INLINE void VM::logicOp(const IR& op)
{
	const Value* lhs = getValue(op.op1);
	const Value* rhs = getValue(op.op2);

	if (UNEXPECTED(lhs->isNull() || rhs->isNull())) {
		getValue(op.result)->setBool(false);
		return;
	}

	const Type* type = lhs->getType();

	switch (op.opcode) {
		case OP_GREATER: type->greater(getValue(op.result), lhs, rhs, this, &m_exception);       break;
		case OP_GEQUAL:  type->greater_equal(getValue(op.result), lhs, rhs, this, &m_exception); break;
		case OP_LESS:    type->less(getValue(op.result), lhs, rhs, this, &m_exception);          break;
		case OP_LEQUAL:  type->less_equal(getValue(op.result), lhs, rhs, this, &m_exception);    break;
		case OP_EQUAL:   type->equal(getValue(op.result), lhs, rhs, this, &m_exception);         break;
		case OP_NEQUAL:  type->not_equal(getValue(op.result), lhs, rhs, this, &m_exception);     break;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}

// Executes the VM opcodes
// When building on GCC the code will use direct threading code, otherwise
// the switch-based dispatching is used
void VM::run()
{
	getMutex()->lock();
	if (m_call_stack.empty()) {
		m_call_stack.push(CallStackEntry(m_global_env));
	}
	getMutex()->unlock();

	OPCODES;
	OP(OP_RET):
	if (EXPECTED(!m_call_stack.empty())) {
		Environment* env = m_call_stack.top().env;
		size_t ret_addr = env->getRetAddr();

		if (EXPECTED(OPCODE.op1.op_type != UNUSED)) {
			Value* val = getValue(OPCODE.op1);
			clever_assert_not_null(val);

			if (UNEXPECTED(val->isFunction())) {
				const Function* func = static_cast<Function*>(val->getObj());

				if (func->isUserDefined()) {
					Function* closure = func->getClosure();

					m_call_stack.top().env->getRetVal()->setObj(CLEVER_FUNC_TYPE, closure);

					closure->setEnvironment(
						func->getEnvironment()->activate(m_call_stack.top().env));

					goto out;
				}
			}

			m_call_stack.top().env->getRetVal()->copy(val);
		}
out:
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
			var->deepCopy(value);
			if (UNEXPECTED(OPCODE.result.op_type != UNUSED)) {
				getValue(OPCODE.result)->copy(value);
			}
		} else {
			// TODO(muriloadriano): improve this message to show the symbol
			// name and the line to the user.
			error(OPCODE.loc, "Cannot assign to a const variable!");
		}
	}
	DISPATCH;

	OP(OP_ADD):
	OP(OP_SUB):
	OP(OP_MUL):
	OP(OP_DIV):
	OP(OP_MOD):
	OP(OP_NOT):
	OP(OP_BW_AND):
	OP(OP_BW_OR):
	OP(OP_BW_XOR):
	OP(OP_BW_NOT):
	OP(OP_BW_LS):
	OP(OP_BW_RS):
	binOp(OPCODE);

	if (UNEXPECTED(m_exception.hasException())) {
		goto throw_exception;
	}
	DISPATCH;

	OP(OP_JMP): VM_GOTO(OPCODE.op1.jmp_addr);

	OP(OP_FCALL):
	{
		const Value* fval = getValue(OPCODE.op1);

		clever_assert_not_null(fval);

		if (UNEXPECTED(fval->isNull())) {
			error(OPCODE.loc, "Cannot make a call from null value");
		}

		if (UNEXPECTED(!fval->isFunction())) {
			error(OPCODE.loc,
				"Cannot make a call from %T type", fval->getType());
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

		if (EXPECTED(!m_call_stack.empty())) {
			clever_delref(m_call_stack.top().env);
			m_call_stack.pop();
		}

		getMutex()->unlock();
		goto exit;
	}
	DISPATCH;

	OP(OP_LEAVE):
	{
		Environment* env = m_call_stack.top().env;
		size_t ret_addr = env->getRetAddr();

		clever_delref(env);
		m_call_stack.pop();

		VM_GOTO(ret_addr);
	}

	OP(OP_SEND_VAL): m_call_args.push_back(getValue(OPCODE.op1)); DISPATCH;

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
			getValue(OPCODE.result)->deepCopy(value);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Cannot increment null value");
		}
	}
	DISPATCH;

	OP(OP_POS_INC):
	{
		Value* value = getValue(OPCODE.op1);

		if (EXPECTED(!value->isNull())) {
			getValue(OPCODE.result)->deepCopy(value);
			value->getType()->increment(value, this, &m_exception);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Cannot increment null value");
		}
	}
	DISPATCH;

	OP(OP_PRE_DEC):
	{
		Value* value = getValue(OPCODE.op1);

		if (EXPECTED(!value->isNull())) {
			value->getType()->decrement(value, this, &m_exception);
			getValue(OPCODE.result)->deepCopy(value);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Cannot decrement null value");
		}
	}
	DISPATCH;

	OP(OP_POS_DEC):
	{
		Value* value = getValue(OPCODE.op1);

		if (EXPECTED(!value->isNull())) {
			getValue(OPCODE.result)->deepCopy(value);
			value->getType()->decrement(value, this, &m_exception);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Cannot decrement null value");
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
	OP(OP_GEQUAL):
	OP(OP_LEQUAL):
	OP(OP_LESS):
	OP(OP_EQUAL):
	OP(OP_NEQUAL):
	logicOp(OPCODE);
	if (UNEXPECTED(m_exception.hasException())) {
		goto throw_exception;
	}
	DISPATCH;

	OP(OP_LOCK):   getMutex()->lock();   DISPATCH;
	OP(OP_UNLOCK): getMutex()->unlock(); DISPATCH;

	OP(OP_NEW):
	{
		const Type* type = getValue(OPCODE.op1)->getType();
		const Function* ctor = type->getConstructor();

		if (EXPECTED(ctor != NULL)) {
			Value* instance = getValue(OPCODE.result);

			(type->*ctor->getMethodPtr())(instance,
				NULL, m_call_args, this, &m_exception);

			if (UNEXPECTED(m_exception.hasException())) {
				m_call_args.clear();
				goto throw_exception;
			}

			if (UNEXPECTED(instance->isNull())) {
				error(OPCODE.loc,
					"Cannot create object of type %T", type);
			} else {
				createInstance(type, instance);

				if (type->hasUserConstructor()) {
					prepareCall(type->getUserConstructor(),
						static_cast<UserObject*>(instance->getObj())->getEnvironment());

					VM_GOTO(type->getUserConstructor()->getAddr());
				}
				m_call_args.clear();
			}
		} else {
			error(OPCODE.loc,
				"Constructor for %T not found", type);
		}
	}
	DISPATCH;

	OP(OP_MCALL):
	{
		const Value* callee = getValue(OPCODE.op1);
		const Value* method = getValue(OPCODE.op2);

		if (UNEXPECTED(callee->isNull())) {
			error(OPCODE.loc,
				"Cannot call method `%S' from a null value", method->getStr());
		}

		const Type* type = callee->getType();
		const Value* fval = callee->getObj()->getMember(method->getStr());

		if (UNEXPECTED(fval == NULL || !fval->isFunction())) {
			error(OPCODE.loc, "Member `%T::%S' not found or not callable!",
				type, method->getStr());
		}

		const Function* func = static_cast<Function*>(fval->getObj());

		if (UNEXPECTED(func == NULL)) {
			error(OPCODE.loc, "Method `%T::%S' not found!",
				type, method->getStr());
		}

		if (func->isUserDefined()) {
			prepareCall(func,
				static_cast<UserObject*>(callee->getObj())->getEnvironment());

			VM_GOTO(func->getAddr());
		} else {
			if (UNEXPECTED(func->isStatic())) {
				error(OPCODE.loc,
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
				error(OPCODE.loc,
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
			error(OPCODE.loc,
				"Method `%T::%S' not found!", type, method->getStr());
		}
	}
	DISPATCH;

	OP(OP_PROP_R):
	{
		const Value* obj = getValue(OPCODE.op1);

		if (UNEXPECTED(obj->isNull())) {
			error(OPCODE.loc,
				"Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		const Value* value = obj->getObj()->getMember(name->getStr());

		if (EXPECTED(value != NULL)) {
			getValue(OPCODE.result)->copy(value);
		} else {
			error(OPCODE.loc, "Property `%T::%S' not found!",
				obj->getType(), name->getStr());
		}
	}
	DISPATCH;

	OP(OP_SPROP_R):
	{
		const Value* obj = getValue(OPCODE.op1);

		if (UNEXPECTED(obj->isNull())) {
			error(OPCODE.loc,
				"Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		const Value* value = obj->getType()->getProperty(name->getStr());

		if (EXPECTED(value != NULL)) {
			getValue(OPCODE.result)->copy(value);
		} else {
			error(OPCODE.loc, "Property `%T::%S' not found!",
				obj->getType(), name->getStr());
		}
	}
	DISPATCH;

	OP(OP_PROP_W):
	{
		const Value* obj = getValue(OPCODE.op1);

		if (UNEXPECTED(obj->isNull())) {
			error(OPCODE.loc,
				"Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		Value* value = obj->getObj()->getMember(name->getStr());

		if (EXPECTED(value != NULL)) {
			setTempValue(OPCODE.result, value);
			clever_addref(value);
		} else {
			error(OPCODE.loc, "Member `%T::%S' not found!",
				obj->getType(), name->getStr());
		}
	}
	DISPATCH;

	OP(OP_SPROP_W):
	{
		const Value* obj = getValue(OPCODE.op1);

		if (UNEXPECTED(obj->isNull())) {
			error(OPCODE.loc,
				"Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		Value* value = obj->getType()->getProperty(name->getStr());

		if (EXPECTED(value != NULL)) {
			setTempValue(OPCODE.result, value);
			clever_addref(value);
		} else {
			error(OPCODE.loc, "Property `%T::%S' not found!",
				obj->getType(), name->getStr());
		}
	}
	DISPATCH;

	OP(OP_TRY):   m_try_stack.push(std::pair<size_t, size_t>(OPCODE.op1.jmp_addr, 1)); DISPATCH;
	OP(OP_CATCH): m_try_stack.top().second = 2; DISPATCH;
	OP(OP_THROW): m_exception.setException(getValue(OPCODE.op1)); goto throw_exception;

throw_exception:
	if (EXPECTED(!m_try_stack.empty())) {
		size_t catch_addr = m_try_stack.top().first;
		if (m_try_stack.top().second > 1) {
			m_try_stack.pop();
			if (m_try_stack.empty()) {
				goto exit_exception;
			}
			catch_addr = m_try_stack.top().first;
		}
		getValue(m_inst[catch_addr].op1)->copy(m_exception.getException());
		clever_delref(m_exception.getException());
		m_exception.clear();
		VM_GOTO(catch_addr);
	}
	goto exit_exception;

	OP(OP_ETRY): m_try_stack.pop(); DISPATCH;

	OP(OP_SUBSCRIPT):
	{
		const Value* var = getValue(OPCODE.op1);
		const Value* index = getValue(OPCODE.op2);

		if (EXPECTED(!var->isNull() && !index->isNull())) {
			Value* result = var->getType()->at_op(var, index, this, &m_exception);

			setTempValue(OPCODE.result, result);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Operation cannot be executed on null value");
		}
	}
	DISPATCH;

	OP(OP_HALT): goto exit;
	END_OPCODES;

exit_exception:
	{
		std::ostringstream dump;

		dumpStackTrace(dump);

		clever_fatal("Fatal error: Unhandled exception!\nMessage: %v%s",
			m_exception.getException(), dump.str().c_str());
	}
exit:
	if (!m_obj_store.empty()) {
		std::for_each(m_obj_store.top().begin(), m_obj_store.top().end(), clever_delref);
		m_obj_store.pop();
	}
}

} // clever
