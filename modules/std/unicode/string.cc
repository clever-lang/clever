/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "types/type.h"
#include "modules/std/unicode/string.h"

namespace clever { namespace packages { namespace std {

void* allocData(CLEVER_TYPE_CTOR_ARGS) {
	
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
}

}}} // clever::packages::std
