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
			pushValue(args[i]);
		}
	}

	void pushValue(Value* value) {
		if (value) {
			m_data.push_back(value->clone());
			m_data.back()->setConst(false);
		} else {
			m_data.push_back(NULL);
		}
	}

	std::list<GCObject*> getReferred() const {
		return std::list<GCObject*>(m_data.begin(), m_data.end());
	}

	std::vector<Value*>& getData() { return m_data; }
private:
	std::vector<Value*> m_data;

	DISALLOW_COPY_AND_ASSIGN(ArrayObject);
};

class ArrayIteratorObject : public TypeObject {
public:

	typedef std::vector<Value*>::iterator InternalIteratorType;

	ArrayIteratorObject(ArrayObject* array)
		: m_array(array), m_iterator(array->getData().begin()) {
		clever_addref(m_array);
	}

	ArrayIteratorObject(ArrayObject* array, const InternalIteratorType& iter)
		: m_array(array), m_iterator(iter) {
		clever_addref(m_array);
	}

	InternalIteratorType& getIterator() {
		return m_iterator;
	}

	InternalIteratorType getNext() {
		InternalIteratorType it = m_iterator;
		return ++it;
	}

	bool isValid() const {
		return m_iterator != m_array->getData().end();
	}

	ArrayObject* getArray() const {
		return m_array;
	}

	~ArrayIteratorObject() {
		clever_delref(m_array);
	}
private:
	ArrayObject* m_array;
	InternalIteratorType m_iterator;
	DISALLOW_COPY_AND_ASSIGN(ArrayIteratorObject);
};

class ArrayIterator : public Type {
public:
	ArrayIterator() : Type("ArrayIterator") {}
	~ArrayIterator() {}

	virtual void init();
	virtual std::string toString(TypeObject*) const;

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(next);
	CLEVER_METHOD(get);

	// Operators
	virtual void CLEVER_FASTCALL equal(CLEVER_TYPE_OPERATOR_ARGS)     const;
	virtual void CLEVER_FASTCALL not_equal(CLEVER_TYPE_OPERATOR_ARGS) const;

private:
	DISALLOW_COPY_AND_ASSIGN(ArrayIterator);
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
	CLEVER_METHOD(resize);
	CLEVER_METHOD(reserve);
	CLEVER_METHOD(reverse);
	CLEVER_METHOD(each);
	CLEVER_METHOD(shift);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(range);
	CLEVER_METHOD(erase);

	CLEVER_METHOD(begin);
	CLEVER_METHOD(end);

	// Operators
	Value* CLEVER_FASTCALL at_op(CLEVER_TYPE_AT_OPERATOR_ARGS) const;

	CLEVER_TYPE_OPERATOR(add);
private:

	DISALLOW_COPY_AND_ASSIGN(ArrayType);
};

} // clever

#endif // CLEVER_ARRAY_H
