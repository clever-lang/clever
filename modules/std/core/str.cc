/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <string>
#include <sstream>
#include <cstdio>
#include "modules/std/core/str.h"
#include "core/compiler.h"
#include "core/vm.h"
#include "core/clever.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(rhs->isStr())) {
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
	if (rhs->isInt()) {
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

// String::String()
CLEVER_METHOD(StrType::ctor)
{
	result->setStr(CSTRING(""));
}

// String.subString(int start, [int count])
// Returns a substring of the argument or string object referenced using bounds provided
CLEVER_METHOD(StrType::subString)
{
	if (!clever_check_args("i|i")) {
		return;
	}

	const CString* of = CLEVER_THIS()->getStr();
	int bounds[2] = {-1, -1};

	switch (args.size()) {
		case 2:
			bounds[0] = args[0]->getInt();
			bounds[1] = args[1]->getInt();
			break;

		case 1:
			bounds[0] = args[0]->getInt();
			break;
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
	if (!clever_check_args("s|ii")) {
		return;
	}

	const CString* haystack = CLEVER_THIS()->getStr();
	const char* needle = args[0]->getStr()->c_str();
	CString::size_type pos, count;

	clever_assert_not_null(haystack);

	// XXX(heuripedes): should a warning/error/exception be thrown? perhaps a runtime error?
	if (!needle) {
		return;
	}

	if (args.size() > 1) {
		pos = args[1]->getInt();
	} else {
		pos = 0;
	}

	if (args.size() > 2) {
		count = args[2]->getInt();
	} else {
		count = strlen(needle);
	}

	result->setInt(haystack->find(needle, pos, count));
}

// String.findFirst(string needle, [int position, [int count]])
// Finds the first occurence of a string in a string returning the position
CLEVER_METHOD(StrType::findFirst)
{
	const char* needle = NULL;
	const CString* haystack = NULL;
	int bounds[2] = {-1, -1};

	if (!clever_check_args("s|ii")) {
		return;
	}

	haystack = CLEVER_THIS()->getStr();
	switch (args.size()) {
		case 1:
			needle = args[0]->getStr()->c_str();
			break;

		case 2:
			needle = args[0]->getStr()->c_str();
			bounds[0] = args[1]->getInt();
			break;

		case 3:
			needle = args[0]->getStr()->c_str();
			bounds[0] = args[1]->getInt();
			bounds[1] = args[2]->getInt();
			break;
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
	const char* needle = NULL;
	const CString* haystack = CLEVER_THIS()->getStr();
	int bounds[2] = {-1, -1};

	if (!clever_check_args("s|ii")) {
		return;
	}

	result->setNull();

	switch (args.size()) {
		case 1:
			needle = args[0]->getStr()->c_str();
			break;

		case 2:
			needle = args[0]->getStr()->c_str();
			bounds[0] = args[1]->getInt();
			break;

		case 3:
			needle = args[0]->getStr()->c_str();
			bounds[0] = args[1]->getInt();
			bounds[1] = args[2]->getInt();
			break;
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

	if (!clever_check_args("s*")) {
		return;
	}

	format = args[0]->getStr();
	std::ostringstream stream;
	const char* start = format->c_str();

	for(const char* point = start; point < (start + format->size());) {
		if (*point && (*point == (char)'\\')) {
			unsigned long arg;
			char* skip;

			if ((arg=::std::strtoul(++point, &skip, 10))) {
				if (args.size() > (arg+offset)) {
					args[arg+offset]->dump(stream);
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
}

// String.startsWith(string match)
CLEVER_METHOD(StrType::startsWith)
{
	if (!clever_check_args("s")) {
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
	if (!clever_check_args("s")) {
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
	if (!clever_check_args("s")) {
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

// String.size()
// Returns the length of the string
CLEVER_METHOD(StrType::size)
{
	if (!clever_check_no_args()) {
		return;
	}
	result->setInt((CLEVER_THIS()->getStr())->length());
}

// String.split(string delimiter, [int maximum])
// Returns string split by delimiter as array
CLEVER_METHOD(StrType::split)
{
	if (!clever_check_args("s|i")) {
		return;
	}

	unsigned long maximum = 0;
	if (args.size() > 1) {
		if (args[1]->getInt()) {
			maximum = args[1]->getInt();
		}
	}

	::std::vector<Value*> list;
	const ::std::string* self = CLEVER_THIS()->getStr();

	if (self && self->length()) {
		const ::std::string* delimit = args[0]->getStr();
		size_t offset = 0;

		if (delimit && (offset=delimit->length())) {
			::std::string buffer;
			size_t last = 0;

			for (size_t position = 0; position < self->length(); position++) {
				if ((!maximum || (list.size() < maximum))) {
					if ((last = self->find(delimit->c_str(), position)) == position) {
						list.push_back(new Value(CSTRING(buffer)));
						position = last + (offset-1);
						buffer.clear();
						continue;
					}
				}
				buffer += self->at(position);
			}
			list.push_back(new Value(CSTRING(buffer)));
		} else {
			list.push_back(new Value(self));
		}
	}
	result->setObj(CLEVER_ARRAY_TYPE, CLEVER_ARRAY_TYPE->allocData(&list));
}

CLEVER_TYPE_INIT(StrType::init)
{
	Function* ctor = new Function("String", (MethodPtr) &StrType::ctor);

	setConstructor(ctor);

	addMethod(ctor);
	addMethod(new Function("subString",  	(MethodPtr) &StrType::subString));
	addMethod(new Function("find", 			(MethodPtr) &StrType::find));
	addMethod(new Function("findFirst", 	(MethodPtr) &StrType::findFirst));
	addMethod(new Function("findLast", 		(MethodPtr) &StrType::findLast));
	addMethod(new Function("size",   		(MethodPtr) &StrType::size));
	addMethod(new Function("startsWith",	(MethodPtr) &StrType::startsWith));
	addMethod(new Function("endsWith",		(MethodPtr) &StrType::endsWith));
	addMethod(new Function("charAt",		(MethodPtr) &StrType::charAt));
	addMethod(new Function("split",			(MethodPtr) &StrType::split));
	addMethod(new Function("format",		(MethodPtr) &StrType::format))
		->setStatic();
}

CLEVER_TYPE_OPERATOR(StrType::greater)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() > rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::greater_equal)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() >= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() < rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less_equal)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() <= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::equal)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() == rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::not_equal)
{
	if (EXPECTED(rhs->isStr())) {
		result->setBool(lhs->getStr() != rhs->getStr());
	}
}

} // clever
