/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "modules/std/unicode/string.h"
#include "unicode/ustream.h"
#include "unicode/unistr.h"
#include "core/value.h"

namespace clever { namespace packages { namespace std {

using namespace icu;

void UString::dump(const void *data) const {
	dump(data, ::std::cout);
}

void UString::dump(const void* data, ::std::ostream& out) const {
	Value::DataValue* dvalue = (Value::DataValue*)data;
	if (dvalue) {
		UnicodeString* uvalue = (UnicodeString*) dvalue->obj->getObj();
		if (uvalue) {
			for(int32_t start=0; start < uvalue->length(); start++) {
				out << static_cast<char>(uvalue->char32At(start));
			}
		}
	}
}

void* UString::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	if (args->size()) {
		Value* from = args->at(0);
		if (from && from->getType() == CLEVER_STR_TYPE) {
			const CString* str = from->getStr();
			if (str) {
				return new CLEVER_USTR_OBJ(str);
			}
		} else {
			/** UString.new expected exactly one parameter of type String **/
		}
	} else {
		/** UString.new expected exactly one parameter of type String **/
	}
	return NULL;
}

void UString::deallocData(void *data) {
	delete CLEVER_USTR_CAST(data);
}

// UString.getLength()
// Determine the length of this
CLEVER_METHOD(UString::getLength)
{	
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			CLEVER_RETURN_INT(intern->length());
		}
	} else {
		/** UString.getLength cannot be called statically **/
	}
}

// UString.startsWith(string match, [int start, int length])
// Determine if this starts with match
CLEVER_METHOD(UString::startsWith) {
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("s") || CLEVER_VERIFY_ARGS("sii")) {
				switch (CLEVER_ARG_COUNT()) {
					case 1: CLEVER_RETURN_INT(intern->startsWith(UnicodeString(CLEVER_ARG_PSTR(0)))); break;
					case 3: CLEVER_RETURN_INT(intern->startsWith(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2))); break;
				}
			} else {
				/** UString.startsWith expected one, or three arguments exactly **/
			}
		}
	} else {
		/** UString.startsWith cannot be called statically **/
	}
}

// UString.endsWith(string match, [int start, int length])
// Determine if this ends with match
CLEVER_METHOD(UString::endsWith)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("s") || CLEVER_VERIFY_ARGS("sii")) {
				switch (CLEVER_ARG_COUNT()) {
					case 1: CLEVER_RETURN_INT(intern->endsWith(UnicodeString(CLEVER_ARG_PSTR(0)))); break;
					case 3: CLEVER_RETURN_INT(intern->endsWith(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2))); break;
				}
			} else {
				/** UString.endsWith expected one, or three arguments exactly **/
			}
		}
	} else {
		/** UString.endsWith cannot be called statically **/
	}
}

// UString.indexOf(string of, [int start, [int length]])
// Locates in this the first occurence of characters in text
CLEVER_METHOD(UString::indexOf)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("s") || CLEVER_VERIFY_ARGS("si") || CLEVER_VERIFY_ARGS("sii")) {
				switch(CLEVER_ARG_COUNT()) {
					case 1: CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0)))); break;
					case 2: CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1))); break;
					case 3: CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2))); break;
				}
			} else {
				/** UString.indexOf expected one, two, or three arguments exactly **/
			}
		}
	} else {
		/** UString.indexOf cannot be called statically **/
	}
}

// UString.lastIndexOf(string of, [int start, [int length]])
// Locates in this the last occurence of characters in text
CLEVER_METHOD(UString::lastIndexOf)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("s") || CLEVER_VERIFY_ARGS("si") || CLEVER_VERIFY_ARGS("sii")) {
				switch(CLEVER_ARG_COUNT()) {
					case 1: CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0)))); break;
					case 2: CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1))); break;
					case 3: CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2))); break;
				}
			} else {
				/** UString.lastIndexOf expected the first parameter to be a string **/
			}
		}
	} else {
		/** UString.lastIndexOf cannot be called statically **/
	}
}

// UString.toLower()
// Convert this into lowercase characters
CLEVER_METHOD(UString::toLower)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->toLower();
		}
	} else {
		/** UString.toLower cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

// UString.toUpper()
// Convert this into uppercase characters
CLEVER_METHOD(UString::toUpper)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->toUpper();
		}
	} else {
		/** UString.toUpper cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

// UString.reverse()
// Convert this into the reverse of itself
CLEVER_METHOD(UString::reverse)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->reverse();
		}
	} else {
		/** UString.reverse cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

// UString.trim()
// Trim this
CLEVER_METHOD(UString::trim)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->trim();
		}
	} else {
		/** UString.trim cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

// UString.truncate(int length)
// Truncates this to length, returning the new truncated length
CLEVER_METHOD(UString::truncate)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("i")) {
				intern->truncate(CLEVER_ARG_INT(0));
				CLEVER_RETURN_INT(intern->length());
			} else {
				/** UString.truncate expected exactly on integral parameter **/
			}
		}
	} else {
		/** UString.truncate cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

// UString.append(string next, [int start, int length])
// Appends next to this, using optional start and length of next, returning the length of this
CLEVER_METHOD(UString::append) {
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("s")||CLEVER_VERIFY_ARGS("sii")) {
				switch(CLEVER_ARG_COUNT()) {
					case 1: intern->append(UnicodeString(CLEVER_ARG_PSTR(0))); break;
					case 3: intern->append(UnicodeString(CLEVER_ARG_PSTR(0)), CLEVER_ARG_INT(1), CLEVER_ARG_INT(2)); break;
				}
				CLEVER_RETURN_INT(intern->length());
			} else {
				/** UString.append expected the first argument to be a string **/
			}			
		}
	} else {
		/** UString.append cannot be called statically **/
	}
}

// UString.replace(string match, string replacement)
// Replaces all occurences of match with replacement in this
CLEVER_METHOD(UString::replace)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			if (CLEVER_VERIFY_ARGS("ss")) {
				intern->findAndReplace(UnicodeString(CLEVER_ARG_PSTR(0)), UnicodeString(CLEVER_ARG_PSTR(1)));
			} else {
				/** UString.replace expected exactly two parameters of type string **/
			}
		}
	} else {
		/** UString.replace cannot be called statically **/
	}
}

CLEVER_TYPE_OPERATOR(UString::add) {}
CLEVER_TYPE_OPERATOR(UString::sub) {}
CLEVER_TYPE_OPERATOR(UString::mul) {}
CLEVER_TYPE_OPERATOR(UString::div) {}
CLEVER_TYPE_OPERATOR(UString::mod) {}
CLEVER_TYPE_OPERATOR(UString::greater) {}
CLEVER_TYPE_OPERATOR(UString::greater_equal) {}
CLEVER_TYPE_OPERATOR(UString::less) {}
CLEVER_TYPE_OPERATOR(UString::less_equal) {}
CLEVER_TYPE_OPERATOR(UString::equal) {}
CLEVER_TYPE_OPERATOR(UString::not_equal) {}

CLEVER_TYPE_INIT(UString::init)
{
	addMethod(CSTRING("getLength"),			(MethodPtr) &UString::getLength);
	addMethod(CSTRING("startsWith"),		(MethodPtr) &UString::startsWith);
	addMethod(CSTRING("endsWith"),			(MethodPtr) &UString::endsWith);
	addMethod(CSTRING("indexOf"),			(MethodPtr) &UString::indexOf);
	addMethod(CSTRING("lastIndexOf"),		(MethodPtr) &UString::lastIndexOf);
	addMethod(CSTRING("toUpper"),			(MethodPtr) &UString::toUpper);
	addMethod(CSTRING("toLower"),			(MethodPtr) &UString::toLower);
	addMethod(CSTRING("reverse"),			(MethodPtr) &UString::reverse);
	addMethod(CSTRING("trim"),				(MethodPtr) &UString::trim);
	addMethod(CSTRING("truncate"),			(MethodPtr) &UString::truncate);
	addMethod(CSTRING("append"),			(MethodPtr) &UString::append);
	addMethod(CSTRING("replace"),			(MethodPtr) &UString::replace);
}

}}} // clever::packages::std
