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

#include <iostream>
#include "compiler/cstring.h"
#include "types/type.h"
#include "types/bool.h"

namespace clever {


/**
 * Bool::Bool([Bool value])
 * Construct an Bool object with a default value (if no args) or a
 * custom value
 */
CLEVER_TYPE_METHOD(Bool::constructor) {
	if (args) {
		CLEVER_RETURN_BOOL(CLEVER_ARG_BOOL(0));
	}
	else {
		CLEVER_RETURN_BOOL(false);
	}
}

/**
 * Bool::toString()
 * Converts the number to string
 */
CLEVER_TYPE_METHOD(Bool::toString) {
	CLEVER_RETURN_STR(CSTRING(CLEVER_THIS()->toString()));
}

/**
 * Boolean operators
 */
CLEVER_TYPE_METHOD(Bool::bw_and) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_AS_BOOL(0) & CLEVER_ARG_AS_BOOL(1));
}

CLEVER_TYPE_METHOD(Bool::bw_or) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_AS_BOOL(0) | CLEVER_ARG_AS_BOOL(1));
}

CLEVER_TYPE_METHOD(Bool::bw_xor) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_AS_BOOL(0) ^ CLEVER_ARG_AS_BOOL(1));
}

/**
 * == operator (Bool, Bool)
 */
CLEVER_TYPE_METHOD(Bool::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BOOL(0) == CLEVER_ARG_BOOL(1));
}

/**
 * != operator (Bool, Bool)
 */
CLEVER_TYPE_METHOD(Bool::not_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BOOL(0) != CLEVER_ARG_BOOL(1));
}

void Bool::init() {
	addMethod(new Method("toString", (MethodPtr)&Bool::toString, CLEVER_STR));

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Bool::constructor, CLEVER_BOOL));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Bool::constructor, CLEVER_BOOL))
			->addArg("value", CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, (MethodPtr)&Bool::equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BOOL)
			->addArg("arg2", CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, (MethodPtr)&Bool::not_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BOOL)
			->addArg("arg2", CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_AND, (MethodPtr)&Bool::bw_and, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BOOL)
			->addArg("arg2", CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_XOR, (MethodPtr)&Bool::bw_xor, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BOOL)
			->addArg("arg2", CLEVER_BOOL)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_OR, (MethodPtr)&Bool::bw_or, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BOOL)
			->addArg("arg2", CLEVER_BOOL)
	);
}

DataValue* Bool::allocateValue() const {
	return NULL;
}

} // clever
