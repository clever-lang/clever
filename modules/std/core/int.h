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
#include "core/type.h"

namespace clever {

typedef SimpleTypeObject<long> IntObject;

class IntType : public Type {
public:
	IntType()
		: Type("Int") {}

	~IntType() {}

	virtual void init();

	virtual std::string toString(TypeObject* data) const {
		std::ostringstream str;
		str << static_cast<IntObject*>(data)->value;
		return str.str();
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
