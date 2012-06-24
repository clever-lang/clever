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

#include "types/type.h"
#include "types/function.h"
#include "types/functionvalue.h"
#include "compiler/compiler.h"

namespace clever {

/**
 * Void Function<>::Function<>()
 */
CLEVER_METHOD(FunctionType::constructor) {
	CLEVER_RETURN_DATA_VALUE(new FunctionValue());
}

/**
 * Void Function<>::__assign__(Function<>)
 */
CLEVER_METHOD(FunctionType::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * ReturnType Function<>::toString()
 */
CLEVER_METHOD(FunctionType::toString) {
	FunctionValue* fv = CLEVER_GET_VALUE(FunctionValue*, value);

	std::string str = CLEVER_TYPE_NAME(CLEVER_THIS_ARG(0));
	str += ' ';
	str += fv->getFunction()->getName();
	str += "(";

	const TemplatedType* this_type =
		static_cast<const TemplatedType*>(CLEVER_THIS()->getTypePtr());

	for (size_t i = 1, sz = this_type->getNumArgs(); i < sz; ++i) {
		str += CLEVER_TYPE_NAME(CLEVER_THIS_ARG(i));

		if (i < sz - 1) {
			str += ", ";
		}
	}

	str += ");";

	CLEVER_RETURN_STR(CSTRING(str));
}

/**
 * String Function<>::call()
 */
CLEVER_METHOD(FunctionType::call) {
	FunctionValue* fv = CLEVER_GET_VALUE(FunctionValue*, value);
	const Function* func = fv->getFunction();

	if (func->isUserDefined()) {
		VM::run(func, args);

		// If ReturnType isn't Void
		if (CLEVER_THIS_ARG(0)) {
			retval->copy(VM::getLastReturnValue());
		}
		else {
			retval->setTypePtr(CLEVER_VOID);
		}
	}
	else if (func->isInternal()) {
		func->call(args, retval);
	}
	else {
		ValueVector new_args;

		if (args) {
			new_args = *args;
		}

		std::string rt = "p";

		if (func->getReturnType() == CLEVER_INT) rt = "i";
		else if (func->getReturnType() == CLEVER_DOUBLE) rt = "i";
		else if (func->getReturnType() == CLEVER_STR) rt = "s";
		else if (func->getReturnType() == CLEVER_BOOL) rt = "b";
		else if (func->getReturnType() == CLEVER_BYTE) rt = "c";
		else if (func->getReturnType() == CLEVER_VOID) rt = "v";

		Value lib_name(CSTRING(func->getLibName()));
		Value ret_type(CSTRING(rt));
		Value lf_name(CSTRING(func->getLFName()));

		new_args.push_back(&lib_name);
		new_args.push_back(&ret_type);
		new_args.push_back(&lf_name);

		func->call(&new_args, retval);
	}
}


/**
 * Function type initializator
 */
void FunctionType::init() {
	/**
	 * Check if we are in our "virtual" Function type
	 */
	if (getNumArgs() == 0) {
		return;
	}

	const Type* const return_t = CLEVER_TPL_ARG(0);
	const Type* const function_t =
		static_cast<const TemplatedType*>(CLEVER_TYPE("Function"))
		->getTemplatedType(return_t);

	addMethod(new Method(CLEVER_CTOR_NAME, 
		&FunctionType::constructor, function_t));

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, 
			&FunctionType::do_assign, this, false))->addArg("rvalue", this)
	);

	addMethod(new Method("toString", 
		&FunctionType::toString, CLEVER_STR, true));

	Method* method = new Method("call", &FunctionType::call, return_t, true);

	for (size_t i = 1, sz = getNumArgs(); i < sz; ++i) {
		method->addArg("arg", CLEVER_TPL_ARG(i));
	}

	addMethod(method);
}

DataValue* FunctionType::allocateValue() const {
	return new FunctionValue();
}

DataValue* FunctionType::copy(const Value* orig, bool deep) const {
	FunctionValue* fv = new FunctionValue;

	fv->setFunction(static_cast<FunctionValue*>
		(orig->getDataValue())->getFunction());

	return static_cast<DataValue*>(fv);
}

} // clever
