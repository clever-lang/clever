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

#define CLEVER_USTR_TYPE icu::UnicodeString*
#define CLEVER_USTR_CAST(what) (CLEVER_USTR_TYPE) what
#define CLEVER_USTR_THIS() CLEVER_USTR_CAST(CLEVER_THIS()->getObj())
#define CLEVER_USTR_OBJ(from) icu::UnicodeString(from->c_str(), from->size(), US_INV);

void UnicodeString::dump(const void *data) const {
	 dump(data, ::std::cout);
}

void UnicodeString::dump(const void* data, ::std::ostream& out) const {
	CLEVER_USTR_TYPE ustr = (*(CLEVER_USTR_TYPE*)data);
	if (ustr) {
		/** wtf, I am sure this is right ?? **/
		out << ustr;
	}
}

void* UnicodeString::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	if (args->size()) {
		Value* from = args->at(0);
		if (from && from->getType() == CLEVER_STR_TYPE) {
			const CString* str = from->getStr();
			if (str) {
				return new CLEVER_USTR_OBJ(str);
			}
		} else {
			/** UnicodeString.new expected exactly one argument of type String **/
		}
	} else {
		/** UnicodeString.new expected exactly one argument of type String **/
	}
	return NULL;
}

void UnicodeString::deallocData(void *data) {
	delete CLEVER_USTR_CAST(data);
}

CLEVER_METHOD(UnicodeString::getLength)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			CLEVER_RETURN_INT(intern->length());
		}
	} else {
		/** UnicodeString.getLength cannot be called statically **/
	}
}

CLEVER_METHOD(UnicodeString::startsWith) {
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch (CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0)==CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->startsWith(icu::UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UnicodeString.startsWith expects exactly one parameter of type String **/
					}
				} break;

				default:
					/** UnicodeString.startsWith expects exactly one parameter, got none **/
				break;
			}
		}
	} else {
		/** UnicodeString.startsWith cannot be called statically **/
	}
}

CLEVER_METHOD(UnicodeString::endsWith)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->endsWith(icu::UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UnicodeString.endsWith expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

CLEVER_METHOD(UnicodeString::indexOf) 
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->indexOf(icu::UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UnicodeString.indexOf expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

CLEVER_METHOD(UnicodeString::lastIndexOf)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->lastIndexOf(icu::UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UnicodeString.lastIndexOf expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

CLEVER_METHOD(UnicodeString::toLower)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->toLower();
		}
	} else {
		/** UnicodeString.toLower cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

CLEVER_METHOD(UnicodeString::toUpper)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->toUpper();
		}
	} else {
		/** UnicodeString.toUpper cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

CLEVER_METHOD(UnicodeString::reverse)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->reverse();
		}
	} else {
		/** UnicodeString.reverse cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

CLEVER_METHOD(UnicodeString::trim)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			intern->trim();
		}
	} else {
		/** UnicodeString.trim cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

CLEVER_METHOD(UnicodeString::truncate)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch (CLEVER_ARG_COUNT()) {
				case 1: {
					intern->truncate(CLEVER_ARG_INT(0));
				} break;
				
				default:
					/** UnicodeString.truncate cannot be called statically */
				break;
			}
		}
	} else {
		/** UnicodeString.trim cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
}

CLEVER_TYPE_OPERATOR(UnicodeString::add) {}
CLEVER_TYPE_OPERATOR(UnicodeString::sub) {}
CLEVER_TYPE_OPERATOR(UnicodeString::mul) {}
CLEVER_TYPE_OPERATOR(UnicodeString::div) {}
CLEVER_TYPE_OPERATOR(UnicodeString::mod) {}
CLEVER_TYPE_OPERATOR(UnicodeString::greater) {}
CLEVER_TYPE_OPERATOR(UnicodeString::greater_equal) {}
CLEVER_TYPE_OPERATOR(UnicodeString::less) {}
CLEVER_TYPE_OPERATOR(UnicodeString::less_equal) {}
CLEVER_TYPE_OPERATOR(UnicodeString::equal) {}
CLEVER_TYPE_OPERATOR(UnicodeString::not_equal) {}

CLEVER_TYPE_INIT(UnicodeString::init)
{	
	addMethod(CSTRING("getLength"),			(MethodPtr) &UnicodeString::getLength);
	addMethod(CSTRING("startsWith"),		(MethodPtr) &UnicodeString::startsWith);
	addMethod(CSTRING("endsWith"),			(MethodPtr) &UnicodeString::endsWith);
	addMethod(CSTRING("indexOf"),			(MethodPtr) &UnicodeString::indexOf);
	addMethod(CSTRING("lastIndexOf"),		(MethodPtr) &UnicodeString::lastIndexOf);
	addMethod(CSTRING("toUpper"),			(MethodPtr) &UnicodeString::toUpper);
	addMethod(CSTRING("toLower"),			(MethodPtr) &UnicodeString::toLower);
	addMethod(CSTRING("reverse"),			(MethodPtr) &UnicodeString::reverse);
	addMethod(CSTRING("trim"),				(MethodPtr) &UnicodeString::trim);
	addMethod(CSTRING("truncate"),			(MethodPtr) &UnicodeString::truncate);
}

}}} // clever::packages::std
