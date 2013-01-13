/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DOUBLE_H
#define CLEVER_DOUBLE_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"

namespace clever {

class DoubleType : public Type {
public:
	DoubleType() : Type(CSTRING("Double")) {}
	~DoubleType() {}

	bool isPrimitive() const { return true; }

	void dump(const void* value) const { dump(value, std::cout); }
	void dump(const void* value, std::ostream& out) const { out << *(double*)value; }

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	void increment(Value* value, const VM* vm, CException& exception) const {
		value->setInt(value->getDouble()+1);
	}

	void decrement(Value* value, const VM* vm, CException& exception) const {
		value->setInt(value->getDouble()-1);
	}
};

} // clever

#endif // CLEVER_DOUBLE_H
