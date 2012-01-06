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
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include "compiler/cstring.h"
#include "types/type.h"
#include "types/str.h"

namespace clever {

/**
 * String:replace()
 * Replace part of the string and returns the new one.
 */
CLEVER_TYPE_METHOD(String::replace) {
	size_t needleLength, needlePos;
	std::string newString = CLEVER_THIS()->toString();

	// Initial replace
	needlePos = newString.find(CLEVER_ARG_STR(0), 0);
	needleLength = CLEVER_ARG_STR(0).length();

	do {
		// Do the replace
		newString = newString.replace(needlePos, needleLength, CLEVER_ARG_STR(1));

		// Find the next one
		needlePos = newString.find(CLEVER_ARG_STR(0), 0);
		needleLength = CLEVER_ARG_STR(0).length();
	} while (needlePos != std::string::npos);

	CLEVER_RETURN_STR(CSTRING(newString));
}

/**
 * String::substring(Int, Int)
 * Retrieves a substring from the original one.
 */
CLEVER_TYPE_METHOD(String::substring) {
	if (size_t(CLEVER_ARG(0)->getInteger()) >= CLEVER_THIS()->toString().length()) {
		std::cerr << "Out of range: " << CLEVER_ARG(0)->getInteger()
			<< " is after the end of the string." << std::endl;
		std::exit(1);
	}

	std::string substr = CLEVER_THIS()->toString().substr(CLEVER_ARG(0)->getInteger(), CLEVER_ARG(1)->getInteger());
	CLEVER_RETURN_STR(CSTRING(substr));
}

/**
 * String::toDouble()
 * Converts the string to a double, if possible.
 */
CLEVER_TYPE_METHOD(String::toDouble) {
	double floatValue;
	std::stringstream stream(CLEVER_THIS()->toString());

	if ((stream >> floatValue).fail()) {
		std::cerr << "\"" << CLEVER_THIS()->toString() << "\" is not a valid float." << std::endl;
		std::exit(1);
	}

	retval->setDouble(floatValue);
}

/**
 * String::toInteger()
 * Converts the string to an integer, if possible.
 */
CLEVER_TYPE_METHOD(String::toInteger) {
	int64_t integer;
	std::stringstream stream(CLEVER_THIS()->toString());

	if ((stream >> integer).fail()) {
		std::cerr << "\"" << CLEVER_THIS()->toString() << "\" is not a valid integer." << std::endl;
		std::exit(1);
	}

	CLEVER_RETURN_INT(integer);
}

/**
 * String::String([String value])
 * Construct the object.
 */
CLEVER_TYPE_METHOD(String::constructor) {
	if (args) {
		CLEVER_RETURN_STR(CSTRING(CLEVER_ARG_STR(0)));
	}
	else {
		CLEVER_RETURN_STR(CSTRING(""));
	}
}

/**
 * + operator (String, String)
 */
CLEVER_TYPE_METHOD(String::plus) {
	CLEVER_RETURN_STR(CSTRING(CLEVER_ARG_STR(0) + CLEVER_ARG_STR(1)));
}

void String::init() {
	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&String::constructor, CLEVER_STR));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&String::constructor, CLEVER_STR))
			->addArg("value", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, (MethodPtr)&String::plus, CLEVER_STR))
			->addArg("str1", CLEVER_STR)
			->addArg("str2", CLEVER_STR)
	);

	addMethod(
		(new Method("replace", (MethodPtr)&String::replace, CLEVER_STR))
			->addArg("before", CLEVER_STR)
			->addArg("after", CLEVER_STR)
	);

	addMethod(
		(new Method("substring", (MethodPtr)&String::substring, CLEVER_STR))
			->addArg("start", CLEVER_INT)
			->addArg("length", CLEVER_INT)
	);

	addMethod(new Method("toDouble", (MethodPtr)&String::toDouble, CLEVER_DOUBLE));

	addMethod(new Method("toInteger", (MethodPtr)&String::toInteger, CLEVER_INT));
}

DataValue* String::allocateValue() const {
	return NULL;
}

} // clever
