/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */


#include "types/int.h"

namespace clever {

CLEVER_TYPE_OPERATOR(IntType::add)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() + rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::sub)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() - rhs->getInt());
	}
}


CLEVER_TYPE_OPERATOR(IntType::mul)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() * rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::div)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() / rhs->getInt());
	}
}


CLEVER_TYPE_OPERATOR(IntType::mod)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() % rhs->getInt());
	}
}

} // clever