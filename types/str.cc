/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <string>
#include <sstream>
#include "types/str.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(lhs->getType() == this && rhs->getType() == this)) {
		// TODO: Do not require CString everywhere (because it stores the
		// data in an string table)
		result->setStr(CSTRING(*lhs->getStr() + *rhs->getStr()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::sub)
{
}

CLEVER_TYPE_OPERATOR(StrType::mul)
{
	if (EXPECTED(lhs->getType() == this)) {
		if (rhs->getType() == CLEVER_INT_TYPE) {
			std::ostringstream os;

			for (long i = 0, j = rhs->getInt(); i < j; ++i) {
				os << *lhs->getStr();
			}

			result->setStr(CSTRING(os.str()));
		}
	}
}

CLEVER_TYPE_OPERATOR(StrType::div)
{
}

CLEVER_TYPE_OPERATOR(StrType::mod)
{
}

} // clever
