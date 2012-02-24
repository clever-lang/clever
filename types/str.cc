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

#include <cstdlib>
#include <algorithm>
#include "compiler/cstring.h"
#include "compiler/compiler.h"
#include "types/type.h"
#include "types/array.h"
#include "types/str.h"

namespace clever {

/**
 * String::toString()
 * Returns the itself string
 */
CLEVER_METHOD(String::toString) {
	CLEVER_RETURN_STR(CLEVER_THIS()->getStringP());
}

/**
 * String:ltrim()
 * Trim non letters from left
 */
CLEVER_METHOD(String::ltrim) {
    std::string newString = CLEVER_THIS()->toString();
    newString.erase(0, newString.find_first_not_of(" \n\r\t"));
    CLEVER_RETURN_STR(CSTRING(newString));
}

/**
 * String:rtrim()
 * Trim non letters from right
 */
CLEVER_METHOD(String::rtrim) {
    std::string newString = CLEVER_THIS()->toString();
    newString.erase(newString.find_last_not_of(" \n\r\t") + 1);
    CLEVER_RETURN_STR(CSTRING(newString));
}

/**
 * String:trim()
 * Trim non letters from both sides
 */
CLEVER_METHOD(String::trim) {
    std::string newString = CLEVER_THIS()->toString();
    // ltrim
    newString.erase(0, newString.find_first_not_of(" \n\r\t"));

    // rtrim
    newString.erase(newString.find_last_not_of(" \n\r\t") + 1);

    CLEVER_RETURN_STR(CSTRING(newString));
}

/**
 * String:replace()
 * Replace part of the string and returns the new one.
 */
CLEVER_METHOD(String::replace) {
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
CLEVER_METHOD(String::substring) {
	int64_t arg0 = CLEVER_ARG_INT(0);
	int64_t arg1 = CLEVER_ARG_INT(1);
	size_t max_size = CLEVER_THIS()->toString().max_size();
	size_t length   = CLEVER_THIS()->toString().length();
	int arg0_in_range = (uint64_t)arg0 < max_size && (uint64_t)arg0 < length;

	if (!arg0_in_range) {
		if ((uint64_t)arg0 >= max_size) {
			clever_fatal("Attempted to access %l, but this platform limits "
					"strings to %l characters.", arg0, max_size);
		} else {
			clever_fatal("Index %l is after the end of the string.", arg0);
		}
	}

	std::string substr = CLEVER_THIS()->toString().substr(arg0, arg1);
	CLEVER_RETURN_STR(CSTRING(substr));
}

/**
 * String:at(Int)
 * Return the char at position, if possible
 */
CLEVER_METHOD(String::at) {
	int64_t pos = CLEVER_ARG(0)->getInteger();

	if (static_cast<size_t>(pos) > CLEVER_THIS()->toString().length()) {
		Compiler::warningf("Out of range: %l is after the end of the string.", pos);
	}

	std::string newString;
	newString = CLEVER_THIS()->toString()[pos];

	CLEVER_RETURN_STR(CSTRING(newString));
}

/**
 * String:length
 * Return the length of the string
 */
CLEVER_METHOD(String::length) {
	CLEVER_RETURN_INT(CLEVER_THIS()->toString().length());
}

/**
 * String::toDouble()
 * Converts the string to a double, if possible.
 */
CLEVER_METHOD(String::toDouble) {
	double floatValue = 0.0;
	std::stringstream stream(CLEVER_THIS()->toString());

	stream >> floatValue;

	clever_assert(stream.fail() == false,
		"'%s' is not a valid floating point number.", CLEVER_THIS()->toString().c_str());

	retval->setDouble(floatValue);
}

/**
 * String::toInteger()
 * Converts the string to an integer, if possible.
 */
CLEVER_METHOD(String::toInteger) {
	int64_t integer = 0L;
	std::stringstream stream(CLEVER_THIS()->toString());

	stream >> integer;

	clever_assert(stream.fail() == false,
			"'%s' is not a valid integer.", CLEVER_THIS()->toString().c_str());


	CLEVER_RETURN_INT(integer);
}

/**
 * String::String([String value]), String::String([Array<Byte> data])
 * Construct the object.
 */
CLEVER_METHOD(String::constructor) {
	const Type* arr_byte = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_BYTE);

	if (args) {
		if (CLEVER_ARG(0)->getTypePtr() == CLEVER_STR) {
			// String::String([String value])
			CLEVER_RETURN_STR(CSTRING(CLEVER_ARG_STR(0)));
		} else if (CLEVER_ARG(0)->getTypePtr() == arr_byte) {
			// String::String([Array<Byte> data])
			ValueVector *vv = CLEVER_ARG_ARRAY(0);
			std::string buffer = "";

			for (size_t i = 0, j = vv->size(); i < j; ++i) {
				char c = static_cast<char>(vv->at(i)->getByte());

				// Support for zero-based strings.
				if (c) {
					buffer += static_cast<char>(c);
				} else {
					break;
				}
			}
			CLEVER_RETURN_STR(CSTRING(buffer));
		}
	}
	else {
		// String::String()
		CLEVER_RETURN_STR(CSTRING(""));
	}
}

/**
 * String String::toUpper()
 * Returns the current string in upper case
 */
CLEVER_METHOD(String::toUpper) {
	::std::string str = CLEVER_THIS()->toString();
	::std::transform(str.begin(), str.end(),str.begin(), ::toupper);
	CLEVER_RETURN_STR(CSTRING(str));
}

/**
 * String String::toLower()
 * Returns the current string in lower case
 */
CLEVER_METHOD(String::toLower) {
	::std::string str = CLEVER_THIS()->toString();
	::std::transform(str.begin(), str.end(),str.begin(), ::tolower);
	CLEVER_RETURN_STR(CSTRING(str));
}

/**
 * Bool String::startsWith(String)
 * Returns true iff this String starts with the String given as argument
 */
CLEVER_METHOD(String::startsWith) {
	const ::std::string& this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();

	size_t arg_sz = arg_str.size();

	if (arg_sz > this_str.size()) {
		CLEVER_RETURN_BOOL(false);
		return;
	}

	CLEVER_RETURN_BOOL(this_str.compare(0, arg_sz, arg_str) == 0);
}

/**
 * Bool String::endsWith(String)
 * Returns true iff this String ends with the String given as argument
 */
CLEVER_METHOD(String::endsWith) {
	const ::std::string& this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();

	size_t arg_sz = arg_str.size();
	size_t this_sz = this_str.size();

	if (arg_sz > this_sz) {
		CLEVER_RETURN_BOOL(false);
		return;
	}

	CLEVER_RETURN_BOOL(this_str.compare(this_sz - arg_sz, arg_sz, arg_str) == 0);
}

/**
 * Int String::find(String str) and Int String::find(String str, Int pos)
 * Searches in the current String for the first occurrence of 'str' and returns the
 * position or -1 if not found. In the second version, the search is done only using
 * the characters after 'pos'.
 */
CLEVER_METHOD(String::find) {
	const ::std::string& this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();
	size_t pos = (CLEVER_NUM_ARGS() == 1 ? 0 : CLEVER_ARG(1)->getInteger());

	if (pos >= this_str.size()) {
		CLEVER_RETURN_INT(-1LL);
		return;
	}

	size_t find_pos = this_str.find(arg_str, pos);
	CLEVER_RETURN_INT(find_pos != ::std::string::npos ? find_pos : -1LL);
}

/**
 * Array<Byte> String::toByteArray()
 * Returns the byte representation of the current String in an Array
 */
CLEVER_METHOD(String::toByteArray) {
	const ::std::string& this_str = CLEVER_THIS()->toString();
	ValueVector* vv = new ValueVector;

	Value* v;
	for (size_t i = 0, sz = this_str.size(); i < sz; ++i) {
		v = new Value();
		v->setByte(uint8_t(this_str[i]));
		vv->push_back(v);
	}

	retval->setTypePtr(CLEVER_TYPE("Array<Byte>"));
	CLEVER_RETURN_ARRAY(vv);
}

/**
 * String String::pad(S, K)
 */
CLEVER_METHOD(String::pad) {
	::std::string this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();
	int64_t arg_len = CLEVER_ARG(1)->getInteger();

	if ((int64_t)this_str.size() < arg_len) {
		::std::string pad;
		int64_t pad_len = (arg_len - this_str.size()) / 2;

		for (int64_t i = 0; i < pad_len; ++i) {
			pad += arg_str;
		}
		this_str = pad.substr(0, pad_len) + this_str;

		pad = "";
		pad_len = arg_len - this_str.size();
		for (int64_t i = 0; i < pad_len; ++i) {
			pad += arg_str;
		}
		this_str += pad.substr(0, pad_len);
	}

	CLEVER_RETURN_STR(CSTRING(this_str));
}

/**
 * String String::padLeft(S, K)
 */
CLEVER_METHOD(String::padLeft) {
	::std::string this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();
	int64_t arg_len = CLEVER_ARG(1)->getInteger();

	if ((int64_t)this_str.size() < arg_len) {
		::std::string pad;
		int64_t pad_len = arg_len - this_str.size();

		for (int64_t i = 0; i < pad_len; ++i) {
			pad += arg_str;
		}
		this_str = pad.substr(0, pad_len) + this_str;
	}

	CLEVER_RETURN_STR(CSTRING(this_str));
}

/**
 * String String::padRight(S, K)
 */
CLEVER_METHOD(String::padRight) {
	::std::string this_str = CLEVER_THIS()->toString();
	const ::std::string& arg_str = CLEVER_ARG(0)->toString();
	int64_t arg_len = CLEVER_ARG(1)->getInteger();

	if ((int64_t)this_str.size() < arg_len) {
		::std::string pad;
		int64_t pad_len = arg_len - this_str.size();

		for (int64_t i = 0; i < pad_len; ++i) {
			pad += arg_str;
		}
		this_str += pad.substr(0, pad_len);
	}

	CLEVER_RETURN_STR(CSTRING(this_str));
}

/**
 * String String::split(separator)
 */
CLEVER_METHOD(String::split) {
	::std::string this_str = CLEVER_THIS()->toString();
	const ::std::string& separator = CLEVER_ARG(0)->toString();
	ValueVector* vv = new ValueVector;

	// Skip delimiters at beginning.
	::std::string::size_type lastPos = this_str.find_first_not_of(separator, 0);

	// Find first "non-delimiter".
	::std::string::size_type pos = this_str.find_first_of(separator, lastPos);

	while ((::std::string::npos != pos) || (::std::string::npos != lastPos)) {
		Value *v = new Value();

		// Found it.
		v->setString(CSTRING(this_str.substr(lastPos, pos - lastPos)));
		vv->push_back(v);

		// Skip delimiters.
		lastPos = this_str.find_first_not_of(separator, pos);

		// Find next "non-delimiter"
		pos = this_str.find_first_of(separator, lastPos);
	}

	CLEVER_RETURN_ARRAY(vv);
}

/**
 * Void String::__assign__(String)
 */
CLEVER_METHOD(String::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * + operator (String, String)
 */
CLEVER_METHOD(String::plus) {
	CLEVER_RETURN_STR(CSTRING(CLEVER_ARG_STR(0) + CLEVER_ARG_STR(1)));
}

/**
 * == operator (String, String)
 */
CLEVER_METHOD(String::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) == CLEVER_ARG_STR(1));
}

/**
 * != operator (String, String)
 */
CLEVER_METHOD(String::not_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) != CLEVER_ARG_STR(1));
}

/**
 * <= operator (String, String)
 */
CLEVER_METHOD(String::less_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) <= CLEVER_ARG_STR(1));
}

/**
 * >= operator (String, String)
 */
CLEVER_METHOD(String::greater_equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) >= CLEVER_ARG_STR(1));
}

/**
 * > operator (String, String)
 */
CLEVER_METHOD(String::greater) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) > CLEVER_ARG_STR(1));
}

/**
 * < operator (String, String)
 */
CLEVER_METHOD(String::less) {
	CLEVER_RETURN_BOOL(CLEVER_ARG_STR(0) < CLEVER_ARG_STR(1));
}

/**
 * * operator (String, Int)
 */
CLEVER_METHOD(String::times) {
	const ::std::string& str = CLEVER_ARG_STR(0);
	int64_t num = CLEVER_ARG_INT(1);

	if (num <= 0) {
		CLEVER_RETURN_STR(CSTRING(""));
	}
	else {
		::std::string ret = str;
		for (int i = 1; i < num; ++i) {
			ret += str;
		}

		CLEVER_RETURN_STR(CSTRING(ret));
	}
}

void String::init() {
	const Type* arr_byte = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_BYTE);
	const Type* arr_string = CLEVER_GET_ARRAY_TEMPLATE->getTemplatedType(CLEVER_STR);

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&String::constructor, CLEVER_STR));

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&String::constructor, CLEVER_STR))
			->addArg("value", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&String::constructor, CLEVER_STR))
			->addArg("value", arr_byte)
	);

	addMethod(new Method("ltrim", (MethodPtr)&String::ltrim, CLEVER_STR));

	addMethod(new Method("rtrim", (MethodPtr)&String::rtrim, CLEVER_STR));

	addMethod(new Method("trim", (MethodPtr)&String::trim, CLEVER_STR));

	addMethod(
		(new Method(CLEVER_OPERATOR_EQUAL, (MethodPtr)&String::equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_NE, (MethodPtr)&String::not_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GREATER, (MethodPtr)&String::greater, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_GE, (MethodPtr)&String::greater_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LESS, (MethodPtr)&String::less, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_LE, (MethodPtr)&String::less_equal, CLEVER_BOOL))
			->addArg("arg1", CLEVER_STR)
			->addArg("arg2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_PLUS, (MethodPtr)&String::plus, CLEVER_STR))
			->addArg("str1", CLEVER_STR)
			->addArg("str2", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_MULT, (MethodPtr)&String::times, CLEVER_STR))
			->addArg("str", CLEVER_STR)
			->addArg("num", CLEVER_INT)
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

	addMethod(
		(new Method("at", (MethodPtr)&String::at, CLEVER_STR))
			->addArg("pos", CLEVER_INT)
	);

	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&String::do_assign, CLEVER_VOID))
			->addArg("rvalue", CLEVER_STR)
	);

	addMethod(
		(new Method("startsWith", (MethodPtr)&String::startsWith, CLEVER_BOOL))
			->addArg("str", CLEVER_STR)
	);

	addMethod(
		(new Method("endsWith", (MethodPtr)&String::endsWith, CLEVER_BOOL))
			->addArg("str", CLEVER_STR)
	);

	addMethod(
		(new Method("find", (MethodPtr)&String::find, CLEVER_INT))
			->addArg("str", CLEVER_STR)
			->addArg("pos", CLEVER_INT)
			->setMinNumArgs(1)
	);

	addMethod(
		(new Method("split", (MethodPtr)&String::split, arr_string))
			->addArg("separator", CLEVER_STR)
	);

	addMethod(new Method("toByteArray", (MethodPtr)&String::toByteArray, arr_byte));

	addMethod(new Method("length", (MethodPtr)&String::length, CLEVER_INT));

	addMethod(new Method("toDouble", (MethodPtr)&String::toDouble, CLEVER_DOUBLE));

	addMethod(new Method("toInteger", (MethodPtr)&String::toInteger, CLEVER_INT));

	addMethod(new Method("toUpper", (MethodPtr)&String::toUpper, CLEVER_STR));

	addMethod(new Method("toLower", (MethodPtr)&String::toLower, CLEVER_STR));

	addMethod(new Method("toString", (MethodPtr)&String::toString, CLEVER_STR));

	addMethod(
		(new Method("pad", (MethodPtr)&String::pad, CLEVER_STR))
			->addArg("str", CLEVER_STR)
			->addArg("length", CLEVER_INT)
	);

	addMethod(
		(new Method("padLeft", (MethodPtr)&String::padLeft, CLEVER_STR))
			->addArg("str", CLEVER_STR)
			->addArg("length", CLEVER_INT)
	);

	addMethod(
		(new Method("padRight", (MethodPtr)&String::padRight, CLEVER_STR))
			->addArg("str", CLEVER_STR)
			->addArg("length", CLEVER_INT)
	);
}

DataValue* String::allocateValue() const {
	return NULL;
}

} // clever
