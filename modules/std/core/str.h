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

	void init();

	bool isPrimitive() const { return true; }

	void dump(const void* value) const { dump(value, std::cout); }
	void dump(const void* value, std::ostream& out) const { out << (*(const CString**)value)->c_str();}

	CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS;

	void increment(Value* value, const VM* vm) const {}

	void decrement(Value* value, const VM* vm) const {}

	CLEVER_METHOD(subString);
	CLEVER_METHOD(find);
	CLEVER_METHOD(findFirst);
	CLEVER_METHOD(findLast);
	CLEVER_METHOD(size);
	CLEVER_METHOD(format);
	CLEVER_METHOD(startsWith);
	CLEVER_METHOD(endsWith);
	CLEVER_METHOD(charAt);
	CLEVER_METHOD(split);

};

} // clever

#endif // CLEVER_STR_H
