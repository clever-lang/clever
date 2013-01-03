/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <math.h>
#include "types/double.h"

namespace clever {

CLEVER_TYPE_OPERATOR(DoubleType::add)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setDouble(lhs->getDouble() + rhs->getDouble());
	}
}

CLEVER_TYPE_OPERATOR(DoubleType::sub)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setDouble(lhs->getDouble() - rhs->getDouble());
	}
}

CLEVER_TYPE_OPERATOR(DoubleType::mul)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setDouble(lhs->getDouble() * rhs->getDouble());
	}
}

CLEVER_TYPE_OPERATOR(DoubleType::div)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setDouble(lhs->getDouble() / rhs->getDouble());
	}
}
CLEVER_TYPE_OPERATOR(DoubleType::mod)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setDouble(fmod(lhs->getDouble(), rhs->getDouble()));
	}
}

} // clever
