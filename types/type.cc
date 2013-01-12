/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "core/value.h"
#include "core/cexception.h"

namespace clever {

Type::~Type()
{
	PropertyMap::const_iterator it(m_properties.begin()),
		end(m_properties.end());

	while (it != end) {
		// TODO(Felipe): fix crash
		// CLEVER_SAFE_DELREF((*it).second);
		++it;
	}
}


CLEVER_TYPE_OPERATOR(Type::add)
{
	CLEVER_THROW("Cannot use + operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::sub)
{
	CLEVER_THROW("Cannot use - operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::mul)
{
	CLEVER_THROW("Cannot use * operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::div)
{
	CLEVER_THROW("Cannot use / operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::mod)
{
	CLEVER_THROW("Cannot use % operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::greater)
{
	CLEVER_THROW("Cannot use > operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::greater_equal)
{
	CLEVER_THROW("Cannot use >= operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::less)
{
	CLEVER_THROW("Cannot use < operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::less_equal)
{
	CLEVER_THROW("Cannot use <= operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::equal)
{
	CLEVER_THROW("Cannot use == operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::not_equal)
{
	CLEVER_THROW("Cannot use != operator with %S type", getName());
}

void Type::increment(Value* value, const VM* vm, CException* exception) const
{
	CLEVER_THROW("Cannot use ++ operator with %S type", getName());
}

void Type::decrement(Value* value, const VM* vm, CException* exception) const
{
	CLEVER_THROW("Cannot use -- operator with %S type", getName());
}

} // clever
