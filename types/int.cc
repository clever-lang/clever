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
#include "types/int.h"

namespace clever {


/**
 * Int::Int([Int value])
 * Construct an Int object with a default value (if no args) or a
 * custom value
 */
CLEVER_TYPE_METHOD(Integer::constructor) {
	if (args) {
		retval->setInteger(args->at(0)->getInteger());
	}
	else {
		retval->setInteger(0);
	}
}

/**
 * Int::toString()
 * Converts the number to string
 */
CLEVER_TYPE_METHOD(Integer::toString) {
	retval->setString(CSTRING(value->toString()));
}

CLEVER_TYPE_METHOD(Integer::plus) {
	if (args->at(1)->isInteger()) {
		retval->setInteger(args->at(0)->getInteger() + args->at(1)->getInteger());
	} else {
		retval->setInteger(args->at(0)->getInteger() + args->at(1)->getDouble());
	}
}

CLEVER_TYPE_METHOD(Integer::minus) {
	if (args->at(1)->isInteger()) {
		retval->setInteger(args->at(0)->getInteger() - args->at(1)->getInteger());
	} else {
		retval->setInteger(args->at(0)->getInteger() - args->at(1)->getDouble());
	}
}

CLEVER_TYPE_METHOD(Integer::div) {
	if (args->at(1)->isInteger()) {
		retval->setInteger(args->at(0)->getInteger() / args->at(1)->getInteger());
	} else {
		retval->setInteger(args->at(0)->getInteger() / args->at(1)->getDouble());
	}
}

CLEVER_TYPE_METHOD(Integer::mult) {
	if (args->at(1)->isInteger()) {
		retval->setInteger(args->at(0)->getInteger() * args->at(1)->getInteger());
	} else {
		retval->setInteger(args->at(0)->getInteger() * args->at(1)->getDouble());
	}
}

CLEVER_TYPE_METHOD(Integer::mod) {
	retval->setInteger(args->at(0)->getInteger() % args->at(1)->getInteger());
}

CLEVER_TYPE_METHOD(Integer::bw_and) {
	retval->setInteger(args->at(0)->getInteger() & args->at(1)->getInteger());
}

CLEVER_TYPE_METHOD(Integer::bw_or) {
	retval->setInteger(args->at(0)->getInteger() | args->at(1)->getInteger());
}

CLEVER_TYPE_METHOD(Integer::bw_xor) {
	retval->setInteger(args->at(0)->getInteger() ^ args->at(1)->getInteger());
}

void Integer::init() {
	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, (MethodPtr)&Integer::plus, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, (MethodPtr)&Integer::plus, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, (MethodPtr)&Integer::minus, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, (MethodPtr)&Integer::minus, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, (MethodPtr)&Integer::mult, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, (MethodPtr)&Integer::mult, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, (MethodPtr)&Integer::div, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, (MethodPtr)&Integer::div, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MOD, (MethodPtr)&Integer::mod, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_AND, (MethodPtr)&Integer::bw_and, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_XOR, (MethodPtr)&Integer::bw_xor, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_OR, (MethodPtr)&Integer::bw_or, CLEVER_INT))
			->addArg("arg1", CLEVER_INT)
			->addArg("arg2", CLEVER_INT)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Integer::constructor, CLEVER_INT));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Integer::constructor, CLEVER_INT))
			->addArg("value", CLEVER_INT)
	);

	addMethod(new Method("toString", (MethodPtr)&Integer::toString, CLEVER_STR));
}

DataValue* Integer::allocateValue() const {
	return NULL;
}

} // clever
