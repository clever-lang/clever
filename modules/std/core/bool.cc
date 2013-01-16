/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/core/bool.h"

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

} // clever
