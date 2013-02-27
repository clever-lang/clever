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

typedef SimpleTypeObject<long> IntObject;

class IntType : public Type {
public:
	IntType()
		: Type("Int") {}

	~IntType() {}

	void init(CLEVER_TYPE_INIT_ARGS);

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new IntObject; }

	void dump(TypeObject* value, std::ostream& out) const {
		out << static_cast<IntObject*>(value)->value;
	}

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;
	CLEVER_TYPE_VIRTUAL_BITWISE_OPERATORS;

	void increment(Value* value, const VM* vm, CException* exception) const {
		value->setInt(value->getInt()+1);
	}

	void decrement(Value* value, const VM* vm, CException* exception) const {
		value->setInt(value->getInt()-1);
	}

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(toString);
private:
	DISALLOW_COPY_AND_ASSIGN(IntType);
};

} // clever

#endif // CLEVER_INT_H
