/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STR_H
#define CLEVER_STR_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"

namespace clever {

class StrType : public Type {
public:
	StrType() : Type(CSTRING("String")) {}
	~StrType() {}

	bool isPrimitive() const { return true; }

	void dump(const void* value) const {
		std::cout << (*(const CString**)value)->c_str();
	}

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	void increment(Value* value) const {}

	void decrement(Value* value) const {}
};

} // clever

#endif // CLEVER_STR_H
