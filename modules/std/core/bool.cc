/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/core/bool.h"
#include "modules/std/core/function.h"

namespace clever {

CLEVER_TYPE_OPERATOR(BoolType::equal)
{
	if (rhs->isBool()) {
		result->setBool(lhs->getBool() == rhs->getBool());
	}
}

CLEVER_TYPE_OPERATOR(BoolType::not_equal)
{
	if (rhs->isBool()) {
		result->setBool(lhs->getBool() != rhs->getBool());
	}
}

// Bool::Bool()
CLEVER_METHOD(BoolType::ctor)
{
	result->setBool(true);
}

CLEVER_TYPE_INIT(BoolType::init)
{
	setConstructor((MethodPtr) &BoolType::ctor);
}

} // clever
