/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include "core/clever.h"
#include "core/cstring.h"

namespace clever {

#define CLEVER_TYPE_OPERATOR_ARGS Value* result, const Value* lhs, const Value* rhs

#define CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS \
	void add(CLEVER_TYPE_OPERATOR_ARGS) const;  \
	void sub(CLEVER_TYPE_OPERATOR_ARGS) const;  \
	void mul(CLEVER_TYPE_OPERATOR_ARGS) const;  \
	void div(CLEVER_TYPE_OPERATOR_ARGS) const;  \
	void mod(CLEVER_TYPE_OPERATOR_ARGS) const

#define CLEVER_TYPE_OPERATOR(name) CLEVER_FASTCALL void name(CLEVER_TYPE_OPERATOR_ARGS) const

class Value;

class Type {
public:
	Type(const CString* name) : m_name(name) {}
	virtual ~Type() {}

	/// Method for retrieve the type name
	const CString* getName() const { return m_name; }

	/// Virtual method for debug purpose
	virtual void dump(const void*) const = 0;

	virtual void add(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void sub(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void mul(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void div(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void mod(CLEVER_TYPE_OPERATOR_ARGS) const = 0;

	virtual void* allocData() { return NULL; }
	virtual void deallocData(void* data) {}

	virtual void increment(Value*) const = 0;
	virtual void decrement(Value*) const = 0;
private:
	const CString* m_name;
};

}

#endif // CLEVER_TYPE_H
