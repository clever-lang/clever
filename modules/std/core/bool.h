/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_BOOL_H
#define CLEVER_BOOL_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"

namespace clever {

class BoolType : public Type {
public:
	BoolType()
		: Type(CSTRING("Bool")) {}

	~BoolType() {}

	void init();

	bool isPrimitive() const { return true; }

	void dump(const void* value, std::ostream& out) const { out << *(bool*)value; }

	CLEVER_METHOD(ctor);
	CLEVER_TYPE_OPERATOR(equal);
	CLEVER_TYPE_OPERATOR(not_equal);
private:
	DISALLOW_COPY_AND_ASSIGN(BoolType);
};

} // clever

#endif // CLEVER_BOOL_H
