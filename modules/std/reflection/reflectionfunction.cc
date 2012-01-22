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

#include <compiler/pkgmanager.h>
#include <modules/std/reflection/reflectionfunction.h>
#include <modules/std/reflection/reflectionfunctionvalue.h>

namespace clever { namespace packages { namespace std { namespace reflection {

/**
 * ReflectionFunction constructor
 */
CLEVER_TYPE_METHOD(ReflectionFunction::constructor) {
	ReflectionFunctionValue* rfv = new ReflectionFunctionValue;

	/**
	 * Assignment on type creation will increase the ref
	 */
	rfv->setReference(0);

	retval->setDataValue(rfv);
}

/**
 * String ReflectionFunction::getName()
 */
CLEVER_TYPE_METHOD(ReflectionFunction::getName) {
	ReflectionFunctionValue* rfv = CLEVER_GET_VALUE(ReflectionFunctionValue*, value);

	CLEVER_RETURN_STR(rfv->getFunction()->getName());
}

/**
 * Void ReflectionFunction::__assign__(ReflectionFunction)
 */
CLEVER_TYPE_METHOD(ReflectionFunction::do_assign) {
	CLEVER_ARG(0)->getDataValue()->addRef();
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

void ReflectionFunction::init() {
	const Type* reffunc = CLEVER_TYPE("ReflectionFunction");
	
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&ReflectionFunction::constructor, reffunc))
			->addArg("package", CLEVER_STR)
	);

	addMethod(
		new Method("getName", (MethodPtr)&ReflectionFunction::getName, CLEVER_STR)
	);
	
	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&ReflectionFunction::do_assign, CLEVER_VOID))
			->addArg("rvalue", reffunc)
	);

}

DataValue* ReflectionFunction::allocateValue() const {
	return new ReflectionFunctionValue;
}

void ReflectionFunction::destructor(DataValue* value) const {
}

}}}} // clever::packages::std::reflection
