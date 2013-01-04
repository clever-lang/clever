/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_INT_H
#define CLEVER_INT_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"

namespace clever {

class IntType : public Type {
public:
	IntType() : Type(CSTRING("Int")) {}
	~IntType() {}

	void init();

	bool isPrimitive() const { return true; }

	void dump(const void* value) const { std::cout << *(long*)value; }

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	void increment(Value* value) const {
		value->setInt(value->getInt()+1);
	}

	void decrement(Value* value) const {
		value->setInt(value->getInt()-1);
	}

	CLEVER_METHOD_D(toString);
};

} // clever

#endif // CLEVER_INT_H
