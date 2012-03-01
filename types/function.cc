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
 * Void Function<>::__assign__(Function<>)
 */
CLEVER_METHOD(FunctionType::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * String Function<>::toString()
 */
CLEVER_METHOD(FunctionType::toString) {
	FunctionValue* fv = CLEVER_GET_VALUE(FunctionValue*, value);
	
	std::string str = CLEVER_THIS_ARG(0)->getName()->str();
	str += ' ';
	str += fv->getFunction()->getName();
	str += "(";
	
	const TemplatedType* this_type = 
		static_cast<const TemplatedType*>(CLEVER_THIS()->getTypePtr());
		
	for (size_t i = 1, sz = this_type->getNumArgs(); i < sz; ++i) {
		str += CLEVER_THIS_ARG(i)->getName()->str();
		
		if (i < sz - 1) {
			str += ", ";
		}
	}
	
	str += ");";
	
	CLEVER_RETURN_STR(CSTRING(str));
}


/**
 * Function type initializator
 */
void FunctionType::init() {
	/**
	 * Check if we are in our "virtual" Function type
	 */
	if (CLEVER_TPL_ARG(0) == NULL) {
		return;
	}

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&FunctionType::do_assign, this, false))
			->addArg("rvalue", this)
	);
	
	addMethod(new Method("toString", (MethodPtr)&FunctionType::toString, CLEVER_STR, true));
}

DataValue* FunctionType::allocateValue() const {
	return new FunctionValue();
}

} // clever
