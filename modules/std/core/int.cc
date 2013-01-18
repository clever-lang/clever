/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <sstream>
#include "modules/std/core/int.h"
#include "modules/std/core/function.h"

namespace clever {

CLEVER_TYPE_OPERATOR(IntType::add)
{
	if (EXPECTED(rhs->isInt())) {
		result->setInt(lhs->getInt() + rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::sub)
{
	if (EXPECTED(rhs->isInt())) {
		result->setInt(lhs->getInt() - rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::mul)
{
	if (EXPECTED(rhs->isInt())) {
		result->setInt(lhs->getInt() * rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::div)
{
	if (EXPECTED(rhs->isInt())) {
		result->setInt(lhs->getInt() / rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::mod)
{
	if (EXPECTED(rhs->isInt())) {
		result->setInt(lhs->getInt() % rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::greater)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() > rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::greater_equal)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() >= rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::less)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() < rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::less_equal)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() <= rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::equal)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() == rhs->getInt());
	}
}

CLEVER_TYPE_OPERATOR(IntType::not_equal)
{
	if (EXPECTED(rhs->isInt())) {
		result->setBool(lhs->getInt() != rhs->getInt());
	}
}

// Int::Int()
CLEVER_METHOD(IntType::ctor)
{
	result->setInt(0);
}

// Int::toString()
CLEVER_METHOD(IntType::toString)
{
	std::ostringstream str;

	str << CLEVER_THIS()->getInt();

	result->setStr(CSTRING(str.str()));
}

CLEVER_TYPE_INIT(IntType::init)
{
	Function* ctor = new Function("Int", (MethodPtr) &IntType::ctor);

	setConstructor(ctor);

	// Methods
	addMethod(ctor);
	addMethod(new Function("toString", (MethodPtr) &IntType::toString));

	// Properties
	addProperty(CSTRING("SIZE"), new Value((long)sizeof(long), true));
}

} // clever
