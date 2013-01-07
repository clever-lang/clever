/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/vm.h"
#include "types/function.h"

namespace clever {

CLEVER_TYPE_OPERATOR(FuncType::add)
{
	CLEVER_THROW("Cannot use + operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::sub)
{
	CLEVER_THROW("Cannot use - operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::mul)
{
	CLEVER_THROW("Cannot use * operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::div)
{
	CLEVER_THROW("Cannot use / operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::mod)
{
	CLEVER_THROW("Cannot use % operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::greater)
{
	CLEVER_THROW("Cannot use > operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::greater_equal)
{
	CLEVER_THROW("Cannot use >= operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::less)
{
	CLEVER_THROW("Cannot use < operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::less_equal)
{
	CLEVER_THROW("Cannot use <= operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::equal)
{
	CLEVER_THROW("Cannot use == operator with Function type");
}

CLEVER_TYPE_OPERATOR(FuncType::not_equal)
{
	CLEVER_THROW("Cannot use != operator with Function type");
}

} // clever
