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
CLEVER_METHOD(Char::constructor) {
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
CLEVER_METHOD(Char::toString) {
	retval->setString(CSTRING(value->toString()));
}

/**
 * Void Byte::__assign__(Byte)
 */
CLEVER_METHOD(Char::do_assign) {
	CLEVER_THIS()->setByte(CLEVER_ARG_BYTE(0));
}

CLEVER_METHOD(Char::plus) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) + CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::minus) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) - CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::div) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) / CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::mult) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) * CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::mod) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) % CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::bw_and) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) & CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::bw_or) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) | CLEVER_ARG_BYTE(1));
}

CLEVER_METHOD(Char::bw_xor) {
	CLEVER_RETURN_BYTE(CLEVER_ARG_BYTE(0) ^ CLEVER_ARG_BYTE(1));
}

/**
 * == operator (Byte, Byte)
 */
CLEVER_METHOD(Char::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) == CLEVER_ARG_BYTE(1));
}

/**
 * != operator (Byte, Byte)
 */
CLEVER_METHOD(Char::not_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) != CLEVER_ARG_BYTE(1));
}

/**
 * <= operator (Byte, Byte)
 */
CLEVER_METHOD(Char::less_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) <= CLEVER_ARG_BYTE(1));
}

/**
 * >= operator (Byte, Byte)
 */
CLEVER_METHOD(Char::greater_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) >= CLEVER_ARG_BYTE(1));
}

/**
 * > operator (Byte, Byte)
 */
CLEVER_METHOD(Char::greater) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) > CLEVER_ARG_BYTE(1));
}

/**
 * < operator (Byte, Byte)
 */
CLEVER_METHOD(Char::less) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_BYTE(0) < CLEVER_ARG_BYTE(1));
}

/**
 * ! operator
 */
CLEVER_METHOD(Char::logical_not) {
	CLEVER_RETURN_BOOL(!CLEVER_THIS()->getValueAsBool());
}

/**
 * ~ operator
 */
CLEVER_METHOD(Char::bw_not) {
	CLEVER_RETURN_BYTE(~CLEVER_THIS()->getByte());
}

/**
 * ++ operator
 */
CLEVER_METHOD(Char::pre_inc) {
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()+1);
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
}

/**
 * ++ operator
 */
CLEVER_METHOD(Char::pos_inc) {
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()+1);
}

/**
 * -- operator
 */
CLEVER_METHOD(Char::pre_dec) {
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()-1);
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
}

/**
 * -- operator
 */
CLEVER_METHOD(Char::pos_dec) {
	CLEVER_RETURN_BYTE(CLEVER_THIS()->getByte());
	CLEVER_THIS()->setByte(CLEVER_THIS()->getByte()-1);
}

void Char::init() {
	addMethod(
		new Method(CLEVER_OPERATOR_PRE_INC, &Char::pre_inc, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_INC, &Char::pos_inc, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_PRE_DEC, &Char::pre_dec, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_DEC, &Char::pos_dec, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_NOT, &Char::logical_not, CLEVER_BYTE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_BW_NOT, &Char::bw_not, CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, &Char::equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, &Char::not_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GREATER, &Char::greater, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LESS, &Char::less, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GE, &Char::greater_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LE, &Char::less_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, &Char::plus, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, &Char::minus, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, &Char::mult, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, &Char::div, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MOD, &Char::mod, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_AND, &Char::bw_and, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_XOR, &Char::bw_xor, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_OR, &Char::bw_or, CLEVER_BYTE))
			->addArg("arg1", CLEVER_BYTE)
			->addArg("arg2", CLEVER_BYTE)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, &Char::constructor, CLEVER_BYTE));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &Char::constructor, CLEVER_BYTE))
			->addArg("value", CLEVER_BYTE)
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &Char::constructor, CLEVER_BYTE))
			->addArg("value", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, &Char::do_assign, CLEVER_VOID))
			->addArg("rvalue", CLEVER_BYTE)
	);

	addMethod(new Method("toString", &Char::toString, CLEVER_STR));
}

DataValue* Char::allocateValue() const {
	return NULL;
}

} // clever
