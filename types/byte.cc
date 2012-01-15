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

#include "compiler/cstring.h"
#include "types/type.h"
#include "types/byte.h"

namespace clever {


/**
 * Byte::Byte([Byte value])
 * Construct an Byte object with a default value (if no args) or a
 * custom value
 */
CLEVER_TYPE_METHOD(Char::constructor) {
	if (args) {
		uint8_t b;

		if (CLEVER_ARG(0)->isInteger()) {
			b = uint8_t(CLEVER_ARG_INT(0));
		}
		else {
			b = CLEVER_ARG_BYTE(0);
		}

		CLEVER_RETURN_BYTE(b);
	}
	else {
		CLEVER_RETURN_BYTE(0);
	}
}

/**
 * Byte::toString()
 * Converts the number to string
 */
CLEVER_TYPE_METHOD(Char::toString) {
	retval->setString(CSTRING(value->toString()));
}

CLEVER_TYPE_METHOD(Char::plus) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) + CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::minus) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) - CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::div) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) / CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::mult) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) * CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::mod) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) % CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::bw_and) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) & CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::bw_or) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) | CLEVER_ARG_BYTE(1));
}

CLEVER_TYPE_METHOD(Char::bw_xor) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) ^ CLEVER_ARG_BYTE(1));
}

/**
 * == operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) == CLEVER_ARG_BYTE(1));
}

/**
 * != operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::not_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) != CLEVER_ARG_BYTE(1));
}

/**
 * <= operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::less_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) <= CLEVER_ARG_BYTE(1));
}

/**
 * >= operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::greater_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) >= CLEVER_ARG_BYTE(1));
}

/**
 * > operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::greater) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) > CLEVER_ARG_BYTE(1));
}

/**
 * < operator (Byte, Byte)
 */
CLEVER_TYPE_METHOD(Char::less) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) < CLEVER_ARG_BYTE(1));
}

/**
 * ! operator
 */
CLEVER_TYPE_METHOD(Char::logical_not) {
	CLEVER_RETURN_BOOL(!CLEVER_THIS()->getValueAsBool());
}

/**
 * ~ operator
 */
CLEVER_TYPE_METHOD(Char::bw_not) {
	CLEVER_RETURN_BYTE(~CLEVER_THIS()->getByte());
}

/**
 * ++ operator
 */
CLEVER_TYPE_METHOD(Char::pre_inc) {
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()+1);
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
}

/**
 * ++ operator
 */
CLEVER_TYPE_METHOD(Char::pos_inc) {
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()+1);
}

/**
 * -- operator
 */
CLEVER_TYPE_METHOD(Char::pre_dec) {
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()-1);
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
}

/**
 * -- operator
 */
CLEVER_TYPE_METHOD(Char::pos_dec) {
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()-1);
}

void Char::init() {
	addMethod(
		new Method(CLEVER_OPERATOR_PRE_INC, (MethodPtr)&Char::pre_inc, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_INC, (MethodPtr)&Char::pos_inc, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_PRE_DEC, (MethodPtr)&Char::pre_dec, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_DEC, (MethodPtr)&Char::pos_dec, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_NOT, (MethodPtr)&Char::logical_not, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_BW_NOT, (MethodPtr)&Char::bw_not, CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, (MethodPtr)&Char::equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, (MethodPtr)&Char::not_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GREATER, (MethodPtr)&Char::greater, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LESS, (MethodPtr)&Char::less, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GE, (MethodPtr)&Char::greater_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LE, (MethodPtr)&Char::less_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, (MethodPtr)&Char::plus, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, (MethodPtr)&Char::minus, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, (MethodPtr)&Char::mult, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, (MethodPtr)&Char::div, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MOD, (MethodPtr)&Char::mod, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_AND, (MethodPtr)&Char::bw_and, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_XOR, (MethodPtr)&Char::bw_xor, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_OR, (MethodPtr)&Char::bw_or, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Char::constructor, CLEVER_BYTE));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Char::constructor, CLEVER_BYTE))
			->addArg("value", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Char::constructor, CLEVER_BYTE))
			->addArg("value", CLEVER_INT)
	);

	addMethod(new Method("toString", (MethodPtr)&Char::toString, CLEVER_STR));
}

DataValue* Char::allocateValue() const {
	return NULL;
}

} // clever
