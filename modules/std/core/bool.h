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
#include "core/type.h"

namespace clever {

typedef SimpleTypeObject<bool> BoolObject;

class BoolType : public Type {
public:
	BoolType()
		: Type("Bool") {}

	~BoolType() {}

	void init(CLEVER_TYPE_INIT_ARGS);

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new BoolObject; }

	void dump(TypeObject* value, std::ostream& out) const {
		if (static_cast<BoolObject*>(value)->value) {
			out << "true";
		} else {
			out << "false";
		}
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
