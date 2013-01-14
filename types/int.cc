/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <sstream>
#include "types/int.h"
#include "types/function.h"

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

CLEVER_TYPE_OPERATOR(IntType::greater)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() > rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::greater_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() >= rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::less)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() < rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::less_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() <= rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() == rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::not_equal)
{
	if (EXPECTED(rhs->getType() == this)) {
		result->setInt(lhs->getInt() != rhs->getInt());
	}
}

CLEVER_METHOD(IntType::toString)
{
	std::ostringstream str;

	str << CLEVER_THIS()->getInt();

	result->setStr(CSTRING(str.str()));
}

CLEVER_TYPE_INIT(IntType::init)
{
	// Methods
	addMethod(new Function("toString", (MethodPtr) &IntType::toString));

	// Properties
	// addProperty(CSTRING("size"), new Value((long)sizeof(long)));
}

} // clever
