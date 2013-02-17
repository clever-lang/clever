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

struct BoolObject : public TypeObject {
	BoolObject()
		: value() {}

	BoolObject(bool n)
		: value(n) {}

	virtual TypeObject* clone() const { return new BoolObject(value); }

	bool value;
};

class BoolType : public Type {
public:
	BoolType()
		: Type("Bool") {}

	~BoolType() {}

	void init();

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new BoolObject; }

	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<BoolObject*>(data); }

	void dump(TypeObject* value, std::ostream& out) const {
		out << static_cast<BoolObject*>(value)->value;
	}

	CLEVER_METHOD(ctor);
	CLEVER_TYPE_OPERATOR(equal);
	CLEVER_TYPE_OPERATOR(not_equal);
	CLEVER_TYPE_UNARY_OPERATOR(not_op);
private:
	DISALLOW_COPY_AND_ASSIGN(BoolType);
};

} // clever

#endif // CLEVER_BOOL_H
