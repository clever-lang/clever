/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ARRAY_H
#define CLEVER_ARRAY_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "core/type.h"
#include "core/value.h"

namespace clever {

class Value;

class ArrayObject : public TypeObject {
public:
	ArrayObject() {}

	explicit ArrayObject(const std::vector<Value*>& args) {
		append(args);
	}

	~ArrayObject() {
		std::for_each(m_data.begin(), m_data.end(), clever_delref);
	}

	void append(const std::vector<Value*>& args) {
		for (size_t i = 0, n = args.size(); i < n; ++i) {
			m_data.push_back(args[i]->clone());
			m_data.back()->setConst(false);
		}
	}

	void push_value(Value* value) {
		m_data.push_back(value);
		clever_addref(value);
	}

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

	virtual void init();
	virtual std::string toString(TypeObject*) const;

	// Methods
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

	// Operators
	Value* CLEVER_FASTCALL at_op(CLEVER_TYPE_AT_OPERATOR_ARGS) const;

	CLEVER_TYPE_OPERATOR(add);
private:
	DISALLOW_COPY_AND_ASSIGN(ArrayType);
};

} // clever

#endif // CLEVER_ARRAY_H
