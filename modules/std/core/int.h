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

struct IntObject : public TypeObject {
	IntObject()
		: value(0) {}

	IntObject(long n)
		: value(n) {}

	~IntObject() {}

	long value;
};

class IntType : public Type {
public:
	IntType()
		: Type(CSTRING("Int")) {}

	~IntType() {}

	void init();

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new IntObject; }

	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<IntObject*>(data); }

	void dump(TypeObject* value, std::ostream& out) const {
		out << static_cast<IntObject*>(value)->value;
	}

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

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
