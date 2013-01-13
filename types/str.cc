/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <string>
#include <sstream>
#include <cstdio>
#include "types/str.h"
#include "core/compiler.h"
#include "core/vm.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(rhs->getType() == this)) {
		// TODO(Felipe): Do not require CString everywhere (because it stores the
		// data in an string table)
		result->setStr(CSTRING(*lhs->getStr() + *rhs->getStr()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::sub)
{
}

CLEVER_TYPE_OPERATOR(StrType::mul)
{
	if (rhs->getType() == CLEVER_INT_TYPE) {
		std::ostringstream os;

		for (long i = 0, j = rhs->getInt(); i < j; ++i) {
			os << *lhs->getStr();
		}

		result->setStr(CSTRING(os.str()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::div)
{
}

CLEVER_TYPE_OPERATOR(StrType::mod)
{
}

// String.subString(int start, [int count])
// Returns a substring of the argument or string object referenced using bounds provided
CLEVER_METHOD(StrType::subString)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.subString cannot be called statically");
		return;
	}

	const CString* of = CLEVER_THIS()->getStr();
	int bounds[2] = {-1, -1};

	switch(CLEVER_ARG_COUNT()) {
		case 2:
			bounds[0] = args[0]->getInt();
			bounds[1] = args[1]->getInt();
			break;

		case 1:
			bounds[0] = args[0]->getInt();
			break;

		default:
			CLEVER_THROW("String.subString expected at least one argument");
			return;
	}
	result->setNull();
	if (of && bounds[0] > -1) {
		if (bounds[1] > -1) {
			result->setStr(CSTRING(of->substr(bounds[0], bounds[1])));
		} else {
			result->setStr(CSTRING(of->substr(bounds[0])));
		}
	}
}

// String.find(string needle, [int position, [int count]])
// Finds a string in a string returning the position
CLEVER_METHOD(StrType::find)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.find cannot be called statically");
		return;
	}

	const char* needle = NULL;
	const CString* haystack = CLEVER_THIS()->getStr();
	int bounds[2] = {-1, -1};

	switch (CLEVER_ARG_COUNT()) {
		case 1:
			needle = CLEVER_ARG_PSTR(0);
		break;

		case 2:
			needle = CLEVER_ARG_PSTR(0);
			bounds[0] = CLEVER_ARG_INT(1);
		break;

		case 3:
			needle = CLEVER_ARG_PSTR(0);
			bounds[0] = CLEVER_ARG_INT(1);
			bounds[1] = CLEVER_ARG_INT(2);
		break;

		default:
			CLEVER_THROW("String.find expected a maximum of 2 arguments");
			return;
	}

	result->setNull();
	if (needle && haystack) {
		if (bounds[0] > -1) {
			if (bounds[1] > -1) {
				result->setInt(haystack->find(needle, bounds[0], bounds[1]));
			} else {
				result->setInt(haystack->find(needle, bounds[0]));
			}
		} else {
			result->setInt(haystack->find(needle));
		}
	}
}

// String.findFirst(string needle, [int position, [int count]])
// Finds the first occurence of a string in a string returning the position
CLEVER_METHOD(StrType::findFirst)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.findFirst cannot be called statically");
		return;
	}

	const char* needle = NULL;
	const CString* haystack = NULL;
	int bounds[2] = {-1, -1};

	haystack = CLEVER_THIS()->getStr();
	switch (CLEVER_ARG_COUNT()) {
		case 1:
			needle = CLEVER_ARG_PSTR(0);
			break;

		case 2:
			needle = CLEVER_ARG_PSTR(0);
			bounds[0] = CLEVER_ARG_INT(1);
			break;

		case 3:
			needle = CLEVER_ARG_PSTR(0);
			bounds[0] = CLEVER_ARG_INT(1);
			bounds[1] = CLEVER_ARG_INT(2);
			break;

		default:
			CLEVER_THROW("String.findFirst expected a maximum of 2 arguments");
			return;
	}
	result->setNull();

	if (needle && haystack) {
		if (bounds[0] > -1) {
			if (bounds[1] > -1) {
				result->setInt(haystack->find_first_of(needle, bounds[0], bounds[1]));
			} else {
				result->setInt(haystack->find_first_of(needle, bounds[0]));
			}
		} else {
			result->setInt(haystack->find_first_of(needle));
		}
	}
}

// String.findLast(string needle, [int position, [int count]])
// Finds the last occurence of a string in a string returning the position
CLEVER_METHOD(StrType::findLast)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.findLast cannot be called statically");
		return;
	}

	const char* needle = NULL;
	const CString* haystack = CLEVER_THIS()->getStr();
	int bounds[2] = {-1, -1};

	result->setNull();

	switch (CLEVER_ARG_COUNT()) {
		case 1:
			needle = CLEVER_ARG_PSTR(0);
			break;

		case 2:
			needle = CLEVER_ARG_PSTR(0);
			if (CLEVER_ARG_TYPE(1) == CLEVER_INT_TYPE) {
				bounds[0] = CLEVER_ARG_INT(1);
			} else {
				CLEVER_THROW("String.findLast expected an integral argument");
				return;
			}
			break;

		case 3:
			needle = CLEVER_ARG_PSTR(0);
			bounds[0] = CLEVER_ARG_INT(1);
			bounds[1] = CLEVER_ARG_INT(2);
			break;

		default:
			CLEVER_THROW("String.findLast expected a maximum of 2 arguments");
			return;
	}

	if (needle && haystack) {
		if (bounds[0] > -1) {
			if (bounds[1] > -1) {
				result->setInt(haystack->find_last_of(needle, bounds[0], bounds[1]));
			} else {
				result->setInt(haystack->find_last_of(needle, bounds[0]));
			}
		} else {
			result->setInt(haystack->find_last_of(needle));
		}
	}
}

// String.format(string str, ...)
// String.format(...)
// Format a string with the variable list of arguments
CLEVER_METHOD(StrType::format)
{
	const CString* format = NULL;
	long offset = 0L;

	if (CLEVER_THIS()) {
		format = CLEVER_THIS()->getStr();
		offset = -1L;
	} else {
		if (CLEVER_ARG_COUNT()) {
			format = CLEVER_ARG_CSTR(0);
		} else {
			CLEVER_THROW("String.format expected at least one argument");
			return;
		}
	}

	if (format) {
		std::ostringstream stream;
		const char* start = format->c_str();

		for(const char* point = start; point < (start + format->size());) {
			if (*point && (*point == (char)'\\')) {
				unsigned long arg;
				char* skip;

				if ((arg=::std::strtoul(++point, &skip, 10))) {
					if (CLEVER_ARG_COUNT() > (arg+offset)) {
						CLEVER_ARG_DUMPTO((arg+offset), stream);
					}
					point = skip;
				} else {
					stream << *(--point);
					point++;
				}
			} else {
				stream << *point;
				point++;
			}
		}
		result->setStr(CSTRING(stream.str()));
	} else {
		result->setNull();
	}
}

// String.startsWith(string match)
CLEVER_METHOD(StrType::startsWith)
{
	if (!clever_check_args("s")) {
		CLEVER_THROW("String.startsWith expected exactly one string argument");
		return;
	}

	const CString* match = CLEVER_THIS()->getStr();
	const char* with = args[0]->getStr()->c_str();

	if (match && with) {
		result->setInt(match->find(with) == 0);
	} else {
		result->setNull();
	}
}

// String.endsWith(string match)
CLEVER_METHOD(StrType::endsWith)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.endsWith cannot be called statically");
		return;
	}

	if (!clever_check_args("s")) {
		CLEVER_THROW("String.endsWith expected exactly one integral argument");
		return;
	}

	const CString* match = CLEVER_THIS()->getStr();
	const CString* with = args[0]->getStr();

	if (match && with) {
		result->setInt(match->rfind(with->c_str()) == (match->size() - with->size()));
	} else {
		result->setNull();
	}
}

// String.charAt(int position)
CLEVER_METHOD(StrType::charAt)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.charAt cannot be called statically");
		return;
	}
	if (!clever_check_args("s")) {
		CLEVER_THROW("String.charAt expected exactly one argument");
		return;
	}

	const CString* data = CLEVER_THIS()->getStr();
	long position = args[0]->getInt();
	char found[1];

	if (!data) {
		result->setNull();
		return;
	}

	if (position > -1L) {
		if (data->size() > (unsigned long) position) {
			found[0] = data->at(position);
			if (found[0]) {
				result->setStr(CSTRING(found));
			} else {
				result->setNull();
			}
		} else {
			result->setNull();
		}
	} else {
		CLEVER_THROW("String.charAt expected a non-negative argument for position");
	}
}

// String.getLength()
// Returns the length of the string
CLEVER_METHOD(StrType::getLength)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.getLength cannot be called statically");
		return;
	}

	result->setInt((CLEVER_THIS()->getStr())->length());
}

// String.split(string delimiter, [int maximum])
// Returns string split by delimiter as array
CLEVER_METHOD(StrType::split)
{
	if (!CLEVER_THIS()) {
		CLEVER_THROW("String.split cannot be called statically");
		return;
	}

	//const CString* astring = CLEVER_THIS()->getStr();
	if (clever_check_args("s") || clever_check_args("si")) {
		//const CString* delimit = CLEVER_ARG_CSTR(0);
		{
			::std::vector<Value*> list;
			{
				// @TODO(krakjoe) finish the implementation of split
			}
			CLEVER_RETURN_ARRAY(CLEVER_ARRAY_TYPE->allocData(&list));
		}
	} else {
		CLEVER_THROW("String.split expected a string for delimiter");
	}
}

CLEVER_TYPE_INIT(StrType::init)
{
	addMethod(CSTRING("subString"),  	(MethodPtr) &StrType::subString);
	addMethod(CSTRING("find"), 			(MethodPtr) &StrType::find);
	addMethod(CSTRING("findFirst"), 	(MethodPtr) &StrType::findFirst);
	addMethod(CSTRING("findLast"), 		(MethodPtr) &StrType::findLast);
	addMethod(CSTRING("getLength"),		(MethodPtr) &StrType::getLength);
	addMethod(CSTRING("format"),		(MethodPtr) &StrType::format);
	addMethod(CSTRING("startsWith"),	(MethodPtr) &StrType::startsWith);
	addMethod(CSTRING("endsWith"),		(MethodPtr) &StrType::endsWith);
	addMethod(CSTRING("charAt"),		(MethodPtr) &StrType::charAt);
	addMethod(CSTRING("split"),			(MethodPtr) &StrType::split);
}

CLEVER_TYPE_OPERATOR(StrType::greater)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() > rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::greater_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() >= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() < rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() <= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() == rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::not_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getStr() != rhs->getStr());
	}
}

} // clever
