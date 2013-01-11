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
	const CString* of = NULL;
	int bounds[2];

	bounds[0] = -1;
	bounds[1] = -1;

	if (CLEVER_THIS()) {
		of = CLEVER_THIS()->getStr();
		switch(CLEVER_ARG_COUNT()) {
			case 2:
				bounds[0] = CLEVER_ARG_INT(0);
				bounds[1] = CLEVER_ARG_INT(1);
			break;

			case 1:
				bounds[0] = CLEVER_ARG_INT(0);
			break;

			default:
				Compiler::error("String.subString expected at least one argument");
		}
		if (of && bounds[0] > -1) {
			if (bounds[1] > -1) {
				result->setStr(CSTRING(of->substr(bounds[0], bounds[1])));
			} else {
				result->setStr(CSTRING(of->substr(bounds[0])));
			}
		} else {
			result->setNull();
		}
	} else {
		Compiler::error("String.subString cannot be called statically");
	}
}

// String.find(string needle, [int position, [int count]])
// Finds a string in a string returning the position
CLEVER_METHOD(StrType::find)
{
	const char* needle = NULL;
	const CString* haystack = NULL;
	int bounds[2];

	bounds[0] = -1;
	bounds[1] = -1;

	if (CLEVER_THIS()) {
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
				Compiler::error("String.find expected a maximum of 2 arguments");
		}

		if (needle && haystack) {
			if (bounds[0] > -1) {
				if (bounds[1] > -1) {
					CLEVER_RETURN_INT(haystack->find(needle, bounds[0], bounds[1]));
				} else {
					CLEVER_RETURN_INT(haystack->find(needle, bounds[0]));
				}
			} else {
				CLEVER_RETURN_INT(haystack->find(needle));
			}
		} else {
			result->setNull();
		}
	} else {
		Compiler::error("String.find cannot be called statically");
	}
}

// String.findFirst(string needle, [int position, [int count]])
// Finds the first occurence of a string in a string returning the position
CLEVER_METHOD(StrType::findFirst)
{
	const char* needle = NULL;
	const CString* haystack = NULL;
	int bounds[2];

	bounds[0] = -1;
	bounds[1] = -1;

	if (CLEVER_THIS()) {
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
				Compiler::error("String.findFirst expected a maximum of 2 arguments");
		}

		if (needle && haystack) {
			if (bounds[0] > -1) {
				if (bounds[1] > -1) {
					CLEVER_RETURN_INT(haystack->find_first_of(needle, bounds[0], bounds[1]));
				} else {
					CLEVER_RETURN_INT(haystack->find_first_of(needle, bounds[0]));
				}
			} else {
				CLEVER_RETURN_INT(haystack->find_first_of(needle));
			}
		} else {
			result->setNull();
		}
	} else {
		Compiler::error("String.findFirst cannot be called statically");
	}


}

// String.findLast(string needle, [int position, [int count]])
// Finds the last occurence of a string in a string returning the position
CLEVER_METHOD(StrType::findLast)
{
	const char* needle = NULL;
	const CString* haystack = NULL;
	int bounds[2];

	bounds[0] = -1;
	bounds[1] = -1;

	if (CLEVER_THIS()) {
		haystack = CLEVER_THIS()->getStr();
		switch (CLEVER_ARG_COUNT()) {
			case 1:
				needle = CLEVER_ARG_PSTR(0);
			break;

			case 2:
				needle = CLEVER_ARG_PSTR(0);
				if (CLEVER_ARG_TYPE(1) == CLEVER_INT_TYPE) {
					bounds[0] = CLEVER_ARG_INT(1);
				} else {
					Compiler::error("String.findLast expected an integral argument");
				}
			break;

			case 3:
				needle = CLEVER_ARG_PSTR(0);
				bounds[0] = CLEVER_ARG_INT(1);
				bounds[1] = CLEVER_ARG_INT(2);
			break;

			default:
				Compiler::error("String.findLast expected a maximum of 2 arguments");
		}

		if (needle && haystack) {
			if (bounds[0] > -1) {
				if (bounds[1] > -1) {
					CLEVER_RETURN_INT(haystack->find_last_of(needle, bounds[0], bounds[1]));
				} else {
					CLEVER_RETURN_INT(haystack->find_last_of(needle, bounds[0]));
				}
			} else {
				CLEVER_RETURN_INT(haystack->find_last_of(needle));
			}
		} else {
			result->setNull();
		}
	} else {
		Compiler::error("String.findLast cannot be called statically");
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
			Compiler::error("String.format expected at least one argument");
		}
	}

	if (format) {
		std::ostringstream stream;

		{
			const char* start = format->c_str();

			for(const char* point = start; point < (start + format->size());)
			{
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
		}

		result->setStr(CSTRING(stream.str()));
	} else {
		result->setNull();
	}
}

// String.startsWith(string match)
CLEVER_METHOD(StrType::startsWith)
{
	const char* with;
	const CString* match;

	if (CLEVER_THIS()) {
		if (CLEVER_ARG_COUNT() == 1) {
			match = CLEVER_THIS()->getStr();
			if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
				with = CLEVER_ARG_PSTR(0);
				if (match && with) {
					CLEVER_RETURN_INT(match->find(with) == 0);
				} else {
					result->setNull();
				}
			} else {
				Compiler::error("String.startsWith expected exactly one integral argument");
			}
		} else {
			Compiler::error("String.startsWith expected exactly one argument");
		}
	} else {
		Compiler::error("String.startsWith cannot be called statically");
	}


}

// String.endsWith(string match)
CLEVER_METHOD(StrType::endsWith)
{
	const CString* with;
	const CString* match;

	if (CLEVER_THIS()) {
		if (CLEVER_ARG_COUNT() == 1) {
			match = CLEVER_THIS()->getStr();
			if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
				with = CLEVER_ARG_CSTR(0);
				if (match && with) {
					CLEVER_RETURN_INT(match->rfind(with->c_str()) == (match->size() - with->size()));
				} else {
					result->setNull();
				}
			} else {
				Compiler::error("String.endsWith expected exactly one integral argument");
			}
		} else {
			Compiler::error("String.endsWith expected exactly one argument");
		}
	} else {
		Compiler::error("String.endsWith cannot be called statically");
	}
}

// String.charAt(int position)
CLEVER_METHOD(StrType::charAt)
{
	long position;
	const CString* data;
	char found[1];

	if (CLEVER_THIS()) {
		if (CLEVER_ARG_COUNT() == 1) {
			data = CLEVER_THIS()->getStr();
			position = CLEVER_ARG_INT(0);
			if (data) {
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
					Compiler::error("String.charAt expected a non-negative argument for position");
				}
			} else {
				result->setNull();
			}
		} else {
			Compiler::error("String.charAt expected exactly one argument");
		}
	} else {
		Compiler::error("String.charAt cannot be called statically");
	}
}

// String.getLength()
// Returns the length of the string
CLEVER_METHOD(StrType::getLength)
{
	if (CLEVER_THIS()) {
		CLEVER_RETURN_INT((CLEVER_THIS()->getStr())->length());
	} else {
		Compiler::error("String.getLength cannot be called statically");
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
}

CLEVER_TYPE_OPERATOR(StrType::greater)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() > rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::greater_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() >= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() < rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::less_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() <= rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() == rhs->getStr());
	}
}

CLEVER_TYPE_OPERATOR(StrType::not_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		CLEVER_RETURN_INT(lhs->getStr() != rhs->getStr());
	}
}

} // clever
