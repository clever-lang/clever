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
	if (rhs->getType() == this) {
		CLEVER_RETURN_BOOL(lhs->getBool() == rhs->getBool());
	}
}

CLEVER_TYPE_OPERATOR(BoolType::not_equal)
{
	if (rhs->getType() == this) {
		CLEVER_RETURN_BOOL(lhs->getBool() != rhs->getBool());
	}
}

// Bool::Bool()
CLEVER_METHOD(BoolType::ctor)
{
	result->setType(this);
	result->setBool(true);
}

CLEVER_TYPE_INIT(BoolType::init)
{
	Function* ctor = new Function("Bool", (MethodPtr) &BoolType::ctor);

	setConstructor(ctor);

	addMethod(ctor);
}

} // clever
