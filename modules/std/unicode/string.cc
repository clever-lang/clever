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

#define CLEVER_USTR_TYPE UnicodeString*
#define CLEVER_USTR_CAST(what) (CLEVER_USTR_TYPE) what
#define CLEVER_USTR_THIS() CLEVER_USTR_CAST(CLEVER_THIS()->getObj())
#define CLEVER_USTR_OBJ(from) UnicodeString(from->c_str(), from->size(), NULL);

void UString::dump(const void *data) const {
	 dump(data, ::std::cout);
}

void UString::dump(const void* data, ::std::ostream& out) const {
	
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
			/** UString.new expected exactly one argument of type String **/
		}
	} else {
		/** UString.new expected exactly one argument of type String **/
	}
	return NULL;
}

void UString::deallocData(void *data) {
	delete CLEVER_USTR_CAST(data);
}

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

CLEVER_METHOD(UString::startsWith) {
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch (CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0)==CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->startsWith(UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UString.startsWith expects exactly one parameter of type String **/
					}
				} break;

				default:
					/** UString.startsWith expects exactly one parameter, got none **/
				break;
			}
		}
	} else {
		/** UString.startsWith cannot be called statically **/
	}
}

CLEVER_METHOD(UString::endsWith)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->endsWith(UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UString.endsWith expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

CLEVER_METHOD(UString::indexOf) 
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->indexOf(UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UString.indexOf expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

CLEVER_METHOD(UString::lastIndexOf)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch(CLEVER_ARG_COUNT()) {
				case 1: {
					if (CLEVER_ARG_TYPE(0) == CLEVER_STR_TYPE) {
						CLEVER_RETURN_INT(intern->lastIndexOf(UnicodeString(CLEVER_ARG_PSTR(0))));
					} else {
						/** UString.lastIndexOf expects exactly one parameter of type String **/					
					}
				} break;
			}
		}
	}
}

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

CLEVER_METHOD(UString::truncate)
{
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();
		if (intern) {
			switch (CLEVER_ARG_COUNT()) {
				case 1: {
					intern->truncate(CLEVER_ARG_INT(0));
				} break;
				
				default:
					/** UString.truncate cannot be called statically */
				break;
			}
		}
	} else {
		/** UString.trim cannot be called statically **/
	}
	CLEVER_RETURN_NULL();
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
}

}}} // clever::packages::std
