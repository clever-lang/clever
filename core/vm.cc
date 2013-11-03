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

void VM::collect(Environment* env)
{
	clever_assert_not_null(env);

	if (env->refCount() > 1) {
		clever_delref(env);
		return;
	}

	std::vector<Value*>& env_vars = env->getData();
	std::vector<Value*>::const_iterator it(env_vars.begin());
	std::vector<Value*>::const_iterator end(env_vars.end());

	while (it != end) {
		Value* val = *it;

		if (!val->isNull() && val->refCount() == 1) {
			const Type* type = val->getType();

			if (type->hasUserDestructor()) {
				clever_delref(runFunction(type->getUserDestructor(), m_call_args));
			} else if (type->hasDestructor()) {
				const Function* dtor = type->getDestructor();

				(type->*dtor->getMethodPtr())(NULL,	val, m_call_args, &m_clever);
			}
		}
		++it;
	}
	clever_delref(env);
}

void VM::collectObjects()
{
	EnvVector::const_iterator it(m_obj_store.top().begin()),
		end(m_obj_store.top().end());

	while (it != end) {
		collect(*it);
		++it;
	}
}

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
			if (entry.func) {
				out << "# " << entry.func->getName() << "()";
			} else {
				out << "# <main>";
			}

			if (entry.loc->begin.filename) {
				out << " at " << *entry.loc->begin.filename << ":";
			} else {
				out << " at <command line>:";
			}
			out << entry.loc->begin.line << std::endl;
		}

		m_call_stack.pop();
	} while (!m_call_stack.empty());
}

/// Fetchs the Environment according to the supplied operand type
CLEVER_FORCE_INLINE Environment* VM::getCurrentEnvironment(OperandType type) const
{
	switch (type) {
		case FETCH_CONST: return m_const_env;
		case FETCH_VAR:   return m_call_stack.top().env;
		case FETCH_TMP:   return m_call_stack.top().env->getTempEnv();
		default:  	      return NULL;
	}
}

/// Fetchs a Value ptr according to the operand type
CLEVER_FORCE_INLINE Value* VM::getValue(const Operand& operand) const
{
	const Environment* source = getCurrentEnvironment(operand.op_type);

	clever_assert_not_null(source);

	return source->getValue(operand.voffset);
}

CLEVER_FORCE_INLINE void VM::setValue(const Operand& operand, Value* value, bool change) const
{
	Environment* source = getCurrentEnvironment(operand.op_type);
	Value* current_value = source->getValue(operand.voffset);

	if (operand.op_type == FETCH_TMP) {
		if (change) {
			clever_delref(current_value);
			source->setData(operand.voffset.second, value);
		} else {
			current_value->copy(value);
		}
	} else {/*
		if (current_value->refCount() > 1) {
			clever_delref(current_value);
			source->setData(operand.voffset.second, value->clone());
		} else {*/
			current_value->deepCopy(value);
		//}
	}
}

#ifdef CLEVER_DEBUG
void VM::dumpOperand(const Operand& op)
{
	switch (op.op_type) {
		case FETCH_CONST:
			::printf(" %zu(~%zu)", op.voffset.first, op.voffset.second);
			break;
		case FETCH_TMP:
			::printf(" %zu(#%zu)", op.voffset.first, op.voffset.second);
			break;
		case FETCH_VAR:
			::printf(" %zu($%zu)", op.voffset.first, op.voffset.second);
			break;
		case JMP_ADDR:
			::printf(" %#zx", op.jmp_addr);
			break;
		case UNUSED:
			break;
	}
}

void VM::dumpOpcodes() const
{
	for (size_t i = 0, j = m_inst.size(); i < j; ++i) {
		const IR& ir = m_inst[i];
		::printf("0x%04zx: %s", i, get_opcode_name(ir.opcode));
		dumpOperand(ir.op1);
		if (ir.op2.op_type != UNUSED) {
			::printf(",");
		}
		dumpOperand(ir.op2);
		if (ir.result.op_type != UNUSED) {
			::printf(" ->");
		}
		dumpOperand(ir.result);
		::printf("\n");
	}
	std::cout << std::endl;
}
#endif

// Function parameter binding
CLEVER_FORCE_INLINE void VM::paramBinding(const Function* func,
	const Environment* fenv, const ValueVector& args)
{
	size_t nargs = 0;
	size_t args_count = args.size();

	if (func->hasArgs() && args_count) {
		ValueOffset argoff(0,0);
		size_t num_args = args_count;

		if (args_count > func->getNumArgs()) {
			num_args = func->getNumArgs();
		}
		nargs += num_args;

		for (size_t i = 0; i < num_args; ++i) {
			fenv->getValue(argoff)->copy(args[i]);
			argoff.second++;
		}
	}

	if (func->isVariadic()) {
		ArrayObject* arr = new ArrayObject;

		if ((args_count - nargs) > 0) {
			for (size_t i = nargs; i < args_count; ++i) {
				arr->pushValue(args[i]);
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

	m_call_stack.push(CallStackEntry(fenv, func, &OPCODE.loc));

	size_t args_count = m_call_args.size();

	if (args_count < func->getNumRequiredArgs()
		|| (args_count > func->getNumArgs()	&& !func->isVariadic())) {
		error(OPCODE.loc, "Wrong number of parameters");
	}

	paramBinding(func, fenv, m_call_args);

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

	m_obj_store.top().push_back(uobj->getEnvironment());
}

// Executes the supplied function
Value* VM::runFunction(const Function* func, const ValueVector& args)
{
	Value* result = new Value;

	if (UNEXPECTED(func->isInternal())) {
		func->getFuncPtr()(result, args, &m_clever);
	} else {
		Environment* fenv = func->getEnvironment()->activate();
		fenv->setRetVal(result);
		fenv->setRetAddr(m_inst.size()-1);

		m_call_stack.push(CallStackEntry(fenv, func, &OPCODE.loc));
		m_call_args.clear();

		paramBinding(func, fenv, args);

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
	const Value* rhs = op.op2.op_type != UNUSED ? getValue(op.op2) : NULL;
	const Type* type = lhs->getType();

	if (UNEXPECTED(lhs->isNull() || (op.op2.op_type != UNUSED && rhs->isNull()))) {
		error(op.loc, "Operation cannot be executed on null value");
	}

	switch (op.opcode) {
		// Arithmetic
		case OP_ADD: type->add(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_SUB: type->sub(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_MUL: type->mul(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_DIV: type->div(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_MOD: type->mod(getValue(op.result), lhs, rhs, &m_clever); break;
		// Bitwise
		case OP_BW_AND: type->bw_and(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_BW_OR: 	type->bw_or(getValue(op.result),  lhs, rhs, &m_clever); break;
		case OP_BW_XOR:	type->bw_xor(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_BW_RS:	type->bw_rs(getValue(op.result),  lhs, rhs, &m_clever); break;
		case OP_BW_LS:	type->bw_ls(getValue(op.result),  lhs, rhs, &m_clever); break;
		// Unary
		case OP_NOT:    type->not_op(getValue(op.result), lhs, &m_clever); break;
		case OP_BW_NOT:	type->bw_not(getValue(op.result), lhs, &m_clever); break;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}

/// Performs logical operation
CLEVER_FORCE_INLINE void VM::logicOp(const IR& op)
{
	const Value* lhs = getValue(op.op1);
	const Value* rhs = getValue(op.op2);

	if (UNEXPECTED(lhs->isNull() || rhs->isNull())) {
		if (op.opcode == OP_EQUAL) {
			getValue(op.result)->setBool(lhs->isNull() == rhs->isNull());
		} else if (op.opcode == OP_NEQUAL) {
			getValue(op.result)->setBool(lhs->isNull() != rhs->isNull());
		} else {
			getValue(op.result)->setBool(false);
		}
		return;
	}

	const Type* type = lhs->getType();

	switch (op.opcode) {
		case OP_GREATER: type->greater(getValue(op.result),       lhs, rhs, &m_clever); break;
		case OP_GEQUAL:  type->greater_equal(getValue(op.result), lhs, rhs, &m_clever); break;
		case OP_LESS:    type->less(getValue(op.result),          lhs, rhs, &m_clever); break;
		case OP_LEQUAL:  type->less_equal(getValue(op.result),    lhs, rhs, &m_clever); break;
		case OP_EQUAL:   type->equal(getValue(op.result),         lhs, rhs, &m_clever); break;
		case OP_NEQUAL:  type->not_equal(getValue(op.result),     lhs, rhs, &m_clever); break;
		EMPTY_SWITCH_DEFAULT_CASE();
	}
}

/// Throws uncaught exception
void VM::throwUncaughtException(const IR& op)
{
	std::ostringstream msg;

	msg << "Fatal error: Unhandled exception! on ";

	if (op.loc.begin.filename) {
		msg << *op.loc.begin.filename << " ";
	}

	msg << "line " << op.loc.begin.line << "\nMessage: %v";

	dumpStackTrace(msg);

	clever_fatal(msg.str().c_str(),	m_exception.getException());
}

/// Performs class member context checking
bool VM::checkContext(const MemberData& mdata) const
{
	if (mdata.flags == MemberData::PUBLIC) {
		return true;
	} else {
		const Function* curr_func =  m_call_stack.top().func;

		if (curr_func) {
			return curr_func->getContext() != mdata.value->getType();
		} else {
			return false;
		}
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
	if (EXPECTED(m_call_stack.top().env != m_global_env)) {
		Environment* env = m_call_stack.top().env;
		Environment* closure_env = NULL;
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

					//m_obj_store.top().push_back(closure->getEnvironment());
					closure_env = closure->getEnvironment();

					goto out;
				}
			}

			m_call_stack.top().env->getRetVal()->copy(val);
		}
out:
		collectObjects();
		collect(env);
		m_call_stack.pop();
		m_obj_store.pop();
		if (closure_env) {
			m_obj_store.top().push_back(closure_env);
		}

		VM_GOTO(ret_addr);
	} else {
		goto exit;
	}
	DISPATCH;

	OP(OP_ASSIGN):
	{
		Value* var = getValue(OPCODE.op1);
		Value* value = getValue(OPCODE.op2);

		// Checks if this assignment is allowed (non-const variable or
		// const variable declaration).
		if (EXPECTED(var->isAssignable())) {
			setValue(OPCODE.op1, value, false);

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

		if (UNEXPECTED(!fval->isFunction())) {
			error(OPCODE.loc, "Cannot make a call from %T %s",
				fval->getType(), fval->isNull() ? "value" : "type");
		}

		Function* func = static_cast<Function*>(fval->getObj());
		clever_assert_not_null(func);

		if (func->isUserDefined()) {
			prepareCall(func);

			VM_GOTO(func->getAddr());
		} else {
			func->getFuncPtr()(getValue(OPCODE.result), m_call_args, &m_clever);
			m_call_args.clear();

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		}
	}
	DISPATCH;


	OP(OP_LEAVE):
	{
		Environment* env = m_call_stack.top().env;
		size_t ret_addr = env->getRetAddr();

		collect(env);
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
			value->getType()->increment(value, &m_clever);
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
			value->getType()->increment(value, &m_clever);

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
			value->getType()->decrement(value, &m_clever);
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
			value->getType()->decrement(value, &m_clever);

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
				NULL, m_call_args, &m_clever);

			if (UNEXPECTED(m_exception.hasException())) {
				m_call_args.clear();
				goto throw_exception;
			}

			if (UNEXPECTED(instance->isNull())) {
				error(OPCODE.loc, "Cannot create object of type %T", type);
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
			error(OPCODE.loc, "Constructor for %T not found", type);
		}
	}
	DISPATCH;

	OP(OP_MCALL):
	{
		const Value* callee = getValue(OPCODE.op1);
		const Value* method = getValue(OPCODE.op2);

		clever_assert_not_null(callee);
		clever_assert_not_null(method);

		if (UNEXPECTED(callee->isNull())) {
			error(OPCODE.loc,
				"Cannot call method `%S' from a null value", method->getStr());
		}

		const Type* type = callee->getType();
		TypeObject* intern = callee->getObj();

		intern->initialize(type);

		MemberData mdata = intern->getMember(method->getStr());
		const Value* fval = mdata.value;

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot call `%T::%S' from context",
				type, method->getStr());
		}

		if (UNEXPECTED(!fval || !fval->isFunction())) {
			error(OPCODE.loc, "Member `%T::%S' not found or not callable!",
				type, method->getStr());
		}

		const Function* func = static_cast<Function*>(fval->getObj());

		clever_assert_not_null(func);

		if (func->isStatic()) {
			error(OPCODE.loc,
				"Method `%T::%S' cannot be called non-statically",
				type, method->getStr());
		}

		if (func->isUserDefined()) {
			// For real method call
			if (func->hasContext()) {
				prepareCall(func,
					static_cast<UserObject*>(intern)->getEnvironment());
			} else {
				// For function call through class member
				prepareCall(func);
			}

			VM_GOTO(func->getAddr());
		} else {
			if (func->hasContext()) {
				(type->*func->getMethodPtr())(getValue(OPCODE.result),
					callee, m_call_args, &m_clever);
			} else {
				func->getFuncPtr()(getValue(OPCODE.result), m_call_args, &m_clever);
			}

			m_call_args.clear();
			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		}
	}
	DISPATCH;

	OP(OP_SMCALL):
	{
		const Value* valtype = getValue(OPCODE.op1);
		const Type* type = valtype->getType();
		const Value* method = getValue(OPCODE.op2);
		MemberData mdata = type->getMethod(method->getStr());

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot access member `%T::%S' from context",
				type, method->getStr());
		}

		if (EXPECTED(mdata.value && mdata.value->isFunction())) {
			const Function* func = static_cast<Function*>(mdata.value->getObj());

			if (UNEXPECTED(!func->isStatic())) {
				error(OPCODE.loc, "Method `%T::%S' cannot be called statically",
					type, method->getStr());
			}

			if (func->isUserDefined()) {
				prepareCall(func);

				VM_GOTO(func->getAddr());
			} else {
				(type->*func->getMethodPtr())(getValue(OPCODE.result),
					NULL, m_call_args, &m_clever);

				m_call_args.clear();

				if (UNEXPECTED(m_exception.hasException())) {
					goto throw_exception;
				}
			}
		} else {
			error(OPCODE.loc, "Method `%T::%S' not found!", type, method->getStr());
		}
	}
	DISPATCH;

	OP(OP_PROP_R):
	{
		const Value* obj = getValue(OPCODE.op1);

		if (UNEXPECTED(obj->isNull())) {
			error(OPCODE.loc, "Cannot perform property access from null value");
		}

		TypeObject* intern = obj->getObj();

		intern->initialize(obj->getType());

		const Value* name = getValue(OPCODE.op2);
		MemberData mdata = intern->getMember(name->getStr());

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot access member `%T::%S' from context",
				obj->getType(), name->getStr());
		}

		const Value* value = mdata.value;

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
			error(OPCODE.loc, "Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		MemberData mdata = obj->getType()->getProperty(name->getStr());

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot access member `%T::%S' from context",
				obj->getType(), name->getStr());
		}

		const Value* value = mdata.value;

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
			error(OPCODE.loc, "Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		TypeObject* intern = obj->getObj();

		intern->initialize(obj->getType());

		MemberData mdata = intern->getMember(name->getStr());

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot access member `%T::%S' from context",
				obj->getType(), name->getStr());
		}

		Value* value = mdata.value;

		if (EXPECTED(value != NULL)) {
			setValue(OPCODE.result, value);
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
			error(OPCODE.loc, "Cannot perform property access from null value");
		}
		const Value* name = getValue(OPCODE.op2);
		MemberData mdata = obj->getType()->getProperty(name->getStr());

		if (!checkContext(mdata)) {
			error(OPCODE.loc, "Cannot access member `%T::%S' from context",
				obj->getType(), name->getStr());
		}

		Value* value = mdata.value;

		if (EXPECTED(value != NULL)) {
			setValue(OPCODE.result, value);
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

	OP(OP_SUBSCRIPT_W):
	{
		const Value* var = getValue(OPCODE.op1);
		const Value* index = getValue(OPCODE.op2);

		if (EXPECTED(!var->isNull() && !index->isNull())) {
			Value* result = var->getType()->at_op(var, index, true, &m_clever);

			setValue(OPCODE.result, result);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Operation cannot be executed on null value");
		}
	}
	DISPATCH;

	OP(OP_SUBSCRIPT_R):
	{
		const Value* var = getValue(OPCODE.op1);
		const Value* index = getValue(OPCODE.op2);

		if (EXPECTED(!var->isNull() && !index->isNull())) {
			Value* result = var->getType()->at_op(var, index, false, &m_clever);

			setValue(OPCODE.result, result);

			if (UNEXPECTED(m_exception.hasException())) {
				goto throw_exception;
			}
		} else {
			error(OPCODE.loc, "Operation cannot be executed on null value");
		}
	}
	DISPATCH;

	OP(OP_BIND):
	{
		const Value* fval = getValue(OPCODE.op1);
		Function* func = static_cast<Function*>(fval->getObj());
		Environment* fenv = func->getEnvironment();

		if (EXPECTED(fenv->getOuter())) {
			fenv->setOuter(m_call_stack.top().env);
		}
	}
	DISPATCH;

	OP(OP_BSCOPE):
	m_obj_store.push(EnvVector());
	DISPATCH;

	OP(OP_ESCOPE):
	collectObjects();
	m_obj_store.pop();
	DISPATCH;

	OP(OP_HALT): goto exit;
	END_OPCODES;

exit_exception:
	throwUncaughtException(OPCODE);
exit:
	return;
}

} // clever
