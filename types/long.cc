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
#include "types/long.h"

namespace clever {


/**
 * Int::Int([Int value])
 * Construct an Int object with a default value (if no args) or a
 * custom value
 */
CLEVER_METHOD(Long::constructor) {
	if (args) {
		if(CLEVER_ARG_IS_INT(0)) {
			CLEVER_RETURN_LONG((int64_t)CLEVER_ARG_INT(0));
		} else if (CLEVER_ARG_IS_LONG(0)) {
			CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0));
		}
	} else {
		CLEVER_RETURN_LONG(0);
	}
}

/**
 * Int::toString()
 * Converts the number to string
 */
CLEVER_METHOD(Long::toString) {
	retval->setString(CSTRING(value->toString()));
}

/**
 * Void Int::__assign__(Int)
 */
CLEVER_METHOD(Long::do_assign) {
	if (CLEVER_ARG_IS_LONG(0)) {
		CLEVER_THIS()->setLong(CLEVER_ARG(0)->getLong());
	} else if(CLEVER_ARG_IS_INT(0)) {
		CLEVER_THIS()->setLong((int64_t)CLEVER_ARG(0)->getInteger());
	} else {
		CLEVER_THIS()->setLong((int64_t)CLEVER_ARG(0)->getDouble());
	}
}

CLEVER_METHOD(Long::plus) {
	if (CLEVER_ARG_IS_LONG(1)) {
		CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) + CLEVER_ARG_LONG(1));
	} else {
		if (CLEVER_ARG(0) != retval) {
			retval->setDouble(CLEVER_ARG_LONG(0) + CLEVER_ARG_DOUBLE(1));
		}
		else {
			CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) + CLEVER_ARG_DOUBLE(1));
		}
	}
}

CLEVER_METHOD(Long::minus) {
	if (CLEVER_ARG_IS_LONG(1)) {
		CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) - CLEVER_ARG_LONG(1));
	} else {
		if (CLEVER_ARG(0) != retval) {
			retval->setDouble(CLEVER_ARG_LONG(0) - CLEVER_ARG_DOUBLE(1));
		}
		else {
			CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) - CLEVER_ARG_DOUBLE(1));
		}
	}
}

CLEVER_METHOD(Long::div) {
	if (CLEVER_ARG_IS_LONG(1)) {
		CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) / CLEVER_ARG_LONG(1));
	} else {
		if (CLEVER_ARG(0) != retval) {
			retval->setDouble(CLEVER_ARG_LONG(0) / CLEVER_ARG_DOUBLE(1));
		}
		else {
			CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) / CLEVER_ARG_DOUBLE(1));
		}
	}
}

CLEVER_METHOD(Long::mult) {
	if (CLEVER_ARG_IS_LONG(1)) {
		CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) * CLEVER_ARG_LONG(1));
	} else {
		if (CLEVER_ARG(0) != retval) {
			retval->setDouble(CLEVER_ARG_LONG(0) * CLEVER_ARG_DOUBLE(1));
		}
		else {
			CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) * CLEVER_ARG_DOUBLE(1));
		}
	}
}

CLEVER_METHOD(Long::mod) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) % CLEVER_ARG_LONG(1));
}

CLEVER_METHOD(Long::bw_and) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) & CLEVER_ARG_LONG(1));
}

CLEVER_METHOD(Long::bw_or) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) | CLEVER_ARG_LONG(1));
}

CLEVER_METHOD(Long::bw_xor) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) ^ CLEVER_ARG_LONG(1));
}

/**
 * >> operator (Long, Long)
 */
CLEVER_METHOD(Long::rshift) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) >> CLEVER_ARG_LONG(1));
}

/**
 * << operator (Long, Long)
 */
CLEVER_METHOD(Long::lshift) {
	CLEVER_RETURN_LONG(CLEVER_ARG_LONG(0) << CLEVER_ARG_LONG(1));
}

/**
 * == operator (Long, Long)
 */
CLEVER_METHOD(Long::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) == CLEVER_ARG_LONG(1));
}

/**
 * != operator (Long, Long)
 */
CLEVER_METHOD(Long::not_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) != CLEVER_ARG_LONG(1));
}

/**
 * <= operator (Long, Long)
 */
CLEVER_METHOD(Long::less_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) <= CLEVER_ARG_LONG(1));
}

/**
 * >= operator (Long, Long)
 */
CLEVER_METHOD(Long::greater_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) >= CLEVER_ARG_LONG(1));
}

/**
 * > operator (Long, Long)
 */
CLEVER_METHOD(Long::greater) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) > CLEVER_ARG_LONG(1));
}

/**
 * < operator (Long, Long)
 */
CLEVER_METHOD(Long::less) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_LONG(0) < CLEVER_ARG_LONG(1));
}

/**
 * ! operator
 */
CLEVER_METHOD(Long::logical_not) {
	CLEVER_RETURN_BOOL(!CLEVER_THIS()->getValueAsBool());
}

/**
 * ~ operator
 */
CLEVER_METHOD(Long::bw_not) {
	CLEVER_RETURN_LONG(~CLEVER_THIS()->getLong());
}

/**
 * ++ operator
 */
CLEVER_METHOD(Long::pre_inc) {
	CLEVER_THIS()->setLong(CLEVER_THIS()->getLong()+1);
	CLEVER_RETURN_LONG(CLEVER_THIS()->getLong());
}

/**
 * ++ operator
 */
CLEVER_METHOD(Long::pos_inc) {
	CLEVER_RETURN_LONG(CLEVER_THIS()->getLong());
	CLEVER_THIS()->setLong(CLEVER_THIS()->getLong()+1);
}

/**
 * -- operator
 */
CLEVER_METHOD(Long::pre_dec) {
	CLEVER_THIS()->setLong(CLEVER_THIS()->getLong()-1);
	CLEVER_RETURN_LONG(CLEVER_THIS()->getLong());
}

/**
 * -- operator
 */
CLEVER_METHOD(Long::pos_dec) {
	CLEVER_RETURN_LONG(CLEVER_THIS()->getLong());
	CLEVER_THIS()->setLong(CLEVER_THIS()->getLong()-1);
}


void Long::init() {
	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, &Long::do_assign, CLEVER_VOID, false))
			->addArg("rvalue", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, &Long::do_assign, CLEVER_VOID, false))
			->addArg("rvalue", CLEVER_DOUBLE)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_PRE_INC, &Long::pre_inc, CLEVER_LONG, false)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_INC, &Long::pos_inc, CLEVER_LONG, false)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_PRE_DEC, &Long::pre_dec, CLEVER_LONG, false)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_POS_DEC, &Long::pos_dec, CLEVER_LONG, false)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_NOT, &Long::logical_not, CLEVER_LONG)
	);

	addMethod(
		new Method(CLEVER_OPERATOR_BW_NOT, &Long::bw_not, CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, &Long::equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, &Long::not_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GREATER, &Long::greater, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LESS, &Long::less, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GE, &Long::greater_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LE, &Long::less_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, &Long::plus, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, &Long::plus, CLEVER_DOUBLE))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, &Long::minus, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MINUS, &Long::minus, CLEVER_DOUBLE))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, &Long::mult, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, &Long::mult, CLEVER_DOUBLE))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, &Long::div, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_DIV, &Long::div, CLEVER_DOUBLE))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_DOUBLE)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MOD, &Long::mod, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_AND, &Long::bw_and, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_XOR, &Long::bw_xor, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_BW_OR, &Long::bw_or, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LSHIFT, &Long::lshift, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_RSHIFT, &Long::rshift, CLEVER_LONG))
			->addArg("arg1", CLEVER_LONG)
			->addArg("arg2", CLEVER_LONG)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, &Long::constructor, CLEVER_LONG));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &Long::constructor, CLEVER_LONG))
			->addArg("value", CLEVER_LONG)
	);

	addMethod(new Method("toString", &Long::toString, CLEVER_STR));
}

DataValue* Long::allocateValue() const {
	return NULL;
}

} // clever
