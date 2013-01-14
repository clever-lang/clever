/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ARRAY_H
#define CLEVER_ARRAY_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"

namespace clever {

class ArrayObject : public ValueObject {
public:
	ArrayObject()
		: ValueObject() {}

	ArrayObject(const std::vector<Value*>& vec)
		: ValueObject(), m_data(vec) {}

	~ArrayObject() {}

	std::vector<Value*>& getData() { return m_data; }
private:
	std::vector<Value*> m_data;
};

class ArrayType : public Type {
public:
	ArrayType() : Type(CSTRING("Array")) {}
	~ArrayType() {}

	void init();

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	void deallocData(void*);

	void dump(const void* value) const { dump(value, std::cout); }

	void dump(const void* value, std::ostream& out) const;

	CLEVER_METHOD(append);
	CLEVER_METHOD(size);
	CLEVER_METHOD(at);
	CLEVER_METHOD(reserve);
	CLEVER_METHOD(reverse);
	CLEVER_METHOD(each);
	CLEVER_METHOD(shift);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(range);
};

} // clever

#endif // CLEVER_ARRAY_H
