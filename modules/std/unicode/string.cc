/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "types/type.h"
#include "modules/std/unicode/string.h"
#include "unicode/unistr.h"
#include "core/value.h"

namespace clever { namespace packages { namespace std {

#define CLEVER_USTR_TYPE icu::UnicodeString*
#define CLEVER_USTR_CAST(what) (CLEVER_USTR_TYPE) what
#define CLEVER_USTR_THIS() CLEVER_USTR_CAST(CLEVER_THIS()->getObj())
#define CLEVER_USTR_OBJ(from) icu::UnicodeString(from->c_str(), from->size(), US_INV);

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

CLEVER_METHOD(UnicodeString::dbg) {
	if (CLEVER_THIS()) {
		CLEVER_USTR_TYPE intern = CLEVER_USTR_THIS();	
		if (intern) {
			printf("Fetched UnicodeString from Object: %d\n", intern->startsWith(
				icu::UnicodeString("H")
			));
		}
	} else {
		/** UnicodeString.dbg cannot be called statically **/
	}
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
	addMethod(CSTRING("dbg"),		(MethodPtr) &UnicodeString::dbg);
}

}}} // clever::packages::stdsame 
