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
#include "core/type.h"

namespace clever {

typedef SimpleTypeObject<double> DoubleObject;

class DoubleType : public Type {
public:
	DoubleType()
		: Type("Double") {}

	~DoubleType() {}

	virtual void init();

	virtual std::string toString(TypeObject* data) const {
		std::ostringstream str;
		str << static_cast<DoubleObject*>(data)->value;
		return str.str();
	}

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	virtual void increment(Value* value, Clever* clever) const {
		value->setInt(value->getDouble()+1);
	}

	virtual void decrement(Value* value, Clever* clever) const {
		value->setInt(value->getDouble()-1);
	}

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(to_String);
private:
	DISALLOW_COPY_AND_ASSIGN(DoubleType);
};

} // clever

#endif // CLEVER_DOUBLE_H
