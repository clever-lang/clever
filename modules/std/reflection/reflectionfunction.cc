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

#include "compiler/scope.h"
#include "compiler/pkgmanager.h"
#include "modules/std/reflection/reflectionfunction.h"
#include "modules/std/reflection/reflectionfunctionvalue.h"
#include "types/array.h"
#include "vm/vm.h"

namespace clever { namespace packages { namespace std { namespace reflection {

/**
 * Finds for a CallableValue representing a function
 */
static const Function* _reflection_get_function_ptr(const CString* name) {
	const ScopeVector& scopes = g_scope.getChildren();
	ScopeVector::const_iterator scope_it(scopes.begin()),
		scope_end(scopes.end());

	while (scope_it != scope_end) {
		Value* val = (*scope_it)->getValue(name);

		if (val != NULL) {
			if (val->isCallable()) {
				return static_cast<CallableValue*>(val)->getFunction();
			}
			break;
		}
		++scope_it;
	}
	return NULL;
}

/**
 * ReflectionFunction constructor
 */
CLEVER_METHOD(ReflectionFunction::constructor) {
	ReflectionFunctionValue* rfv = new ReflectionFunctionValue;

	rfv->setFunction(_reflection_get_function_ptr(&CLEVER_ARG_STR(0)));

	if (rfv->getFunction() == NULL) {
		delete rfv;
		clever_fatal("Function `%S' not found!", &CLEVER_ARG_STR(0));
	}

	retval->setDataValue(rfv);
}

/**
 * String ReflectionFunction::getName()
 */
CLEVER_METHOD(ReflectionFunction::getName) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	CLEVER_RETURN_STR(CSTRINGT(rfv->getFunction()->getName()));
}

/**
 * Bool ReflectionFunction::isInternal()
 */
CLEVER_METHOD(ReflectionFunction::isInternal) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	CLEVER_RETURN_BOOL(rfv->getFunction()->isInternal());
}

/**
 * Bool ReflectionFunction::isUserDefined()
 */
CLEVER_METHOD(ReflectionFunction::isUserDefined) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	CLEVER_RETURN_BOOL(rfv->getFunction()->isUserDefined());
}

/**
 * Bool ReflectionFunction::isVariadic()
 */
CLEVER_METHOD(ReflectionFunction::isVariadic) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	CLEVER_RETURN_BOOL(rfv->getFunction()->isVariadic());
}

/**
 * String ReflectionFunction::getReturnType()
 */
CLEVER_METHOD(ReflectionFunction::getReturnType) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	const Type* rtype = rfv->getFunction()->getReturnType();

	CLEVER_RETURN_STR(rtype ? rtype->getName() : CSTRING("Void"));
}

/**
 * Int ReflectionFunction::getNumRequiredArgs()
 */
CLEVER_METHOD(ReflectionFunction::getNumRequiredArgs) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);

	CLEVER_RETURN_INT(int64_t(rfv->getFunction()->getNumArgs()));
}

/**
 * Array<String> ReflectionFunction::getArgs()
 */
CLEVER_METHOD(ReflectionFunction::getArgs) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);
	const FunctionArgs& fargs = rfv->getFunction()->getArgs();
	FunctionArgs::const_iterator it(fargs.begin()), end(fargs.end());

	ValueVector* vec = new ValueVector;

	while (it != end) {
		Value* tmp = new Value;

		tmp->setString(it->type->getName());
		vec->push_back(tmp);

		++it;
	}

	CLEVER_RETURN_ARRAY(vec);
}

/**
 * Void ReflectionFunction::__assign__(ReflectionFunction)
 */
CLEVER_METHOD(ReflectionFunction::do_assign) {
	CLEVER_ARG(0)->getDataValue()->addRef();
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * String ReflectionFunction::call([...])
 */
CLEVER_METHOD(ReflectionFunction::call) {
	CLEVER_OBJECT_INIT(rfv, ReflectionFunctionValue*);
	const Function* func = rfv->getFunction();

	if (func->isInternal()) {
		Value result;

		func->call(args, &result);

		if (func->getReturnType()) {
			CLEVER_RETURN_STR(CSTRINGT(result.toString()));
		} else {
			CLEVER_RETURN_EMPTY_STR();
		}
	} else {
		VM::run(func, args);

		const Value* val = VM::getLastReturnValue();

		if (val) {
			CLEVER_RETURN_STR(CSTRINGT(const_cast<Value*>(val)->toString()));
		} else {
			CLEVER_RETURN_EMPTY_STR();
		}
	}
}

void ReflectionFunction::init() {
	const Type* reffunc = CLEVER_TYPE("ReflectionFunction");
	const Type* arr_str = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_STR);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&ReflectionFunction::constructor,
			reffunc))
			->addArg("name", CLEVER_STR)
	);

	addMethod(
		new Method("getName", (MethodPtr)&ReflectionFunction::getName, CLEVER_STR)
	);

	addMethod(
		new Method("getArgs", (MethodPtr)&ReflectionFunction::getArgs, arr_str)
	);

	addMethod(
		new Method("isVariadic", (MethodPtr)&ReflectionFunction::isVariadic,
			CLEVER_BOOL)
	);

	addMethod(
		new Method("getNumRequiredArgs",
			(MethodPtr)&ReflectionFunction::getNumRequiredArgs,	CLEVER_INT)
	);

	addMethod(
		new Method("getReturnType",
			(MethodPtr)&ReflectionFunction::getReturnType, CLEVER_STR)
	);

	addMethod(
		new Method("isInternal",
			(MethodPtr)&ReflectionFunction::isInternal, CLEVER_BOOL)
	);

	addMethod(
		new Method("isUserDefined",
			(MethodPtr)&ReflectionFunction::isUserDefined, CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN,
			(MethodPtr)&ReflectionFunction::do_assign, CLEVER_VOID))
			->addArg("rvalue", reffunc)
	);

	addMethod(
		(new Method("call",
			(MethodPtr)&ReflectionFunction::call, CLEVER_STR))
			->setVariadic()
			->setMinNumArgs(0)
	);
}

DataValue* ReflectionFunction::allocateValue() const {
	return new ReflectionFunctionValue;
}

void ReflectionFunction::destructor(Value* value) const {
}

}}}} // clever::packages::std::reflection
