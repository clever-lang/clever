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

class ArrayObject : public TypeObject {
public:
	ArrayObject() {}

	ArrayObject(const std::vector<Value*>& vec)
		: m_data(vec) {}

	~ArrayObject() {}

	std::vector<Value*>& getData() { return m_data; }
private:
	std::vector<Value*> m_data;

	DISALLOW_COPY_AND_ASSIGN(ArrayObject);
};

class ArrayType : public Type {
public:
	ArrayType()
		: Type("Array") {}

	~ArrayType() {}

	void init();

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	void deallocData(void*);

	void dump(TypeObject*, std::ostream&) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(append);
	CLEVER_METHOD(size);
	CLEVER_METHOD(at);
	CLEVER_METHOD(reserve);
	CLEVER_METHOD(reverse);
	CLEVER_METHOD(each);
	CLEVER_METHOD(shift);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(range);
	CLEVER_METHOD(erase);
private:
	DISALLOW_COPY_AND_ASSIGN(ArrayType);
};

} // clever

#endif // CLEVER_ARRAY_H
