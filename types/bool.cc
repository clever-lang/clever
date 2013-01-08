/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/bool.h"

namespace clever {

CLEVER_TYPE_OPERATOR(BoolType::equal)
{
	if (CLEVER_GET_TYPE(rhs) == this) {
		CLEVER_RETURN_BOOL(CLEVER_GET_BOOL(lhs) == CLEVER_GET_BOOL(rhs));
	}
}

CLEVER_TYPE_OPERATOR(BoolType::not_equal)
{
	if (CLEVER_GET_TYPE(rhs) == this) {
		CLEVER_RETURN_BOOL(CLEVER_GET_BOOL(lhs) != CLEVER_GET_BOOL(rhs));
	}
}

} // clever
