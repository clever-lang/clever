/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <sstream>
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

CLEVER_METHOD(IntType::toString)
{
	if (CLEVER_THIS()) {
		std::ostringstream str;

		str << CLEVER_THIS()->getInt();

		result->setStr(CSTRING(str.str()));
	} else {
		// TODO(Felipe): display an error/throw exception
		std::cout << "Error: Cannot be called as static method!" << '\n';
	}
}

CLEVER_TYPE_INIT(IntType::init)
{
	// Methods
	addMethod(CSTRING("toString"), (MethodPtr) &IntType::toString);

	// Properties
	// addProperty(CSTRING("size"), new Value((long)sizeof(long)));
}

} // clever
