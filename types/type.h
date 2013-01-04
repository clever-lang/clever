/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
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

#define CLEVER_TYPE_INIT_ARGS
#define CLEVER_TYPE_INIT(name) void name(CLEVER_TYPE_INIT_ARGS)

#define CLEVER_METHOD_ARGS Value* result, const Value* obj
#define CLEVER_METHOD_D(name) void name(CLEVER_METHOD_ARGS) const
#define CLEVER_METHOD(name) void name(CLEVER_METHOD_ARGS) const

class Value;
class Type;

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS) const;

typedef std::tr1::unordered_map<const CString*, MethodPtr> MethodMap;
typedef std::pair<const CString*, MethodPtr> MethodPair;

class Type {
public:
	Type(const CString* name) : m_name(name) {}
	virtual ~Type() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS) {}

	void addMethod(const CString* name, MethodPtr ptr) {
		m_methods.insert(MethodPair(name, ptr));
	}

	MethodPtr getMethod(const CString* name) const {
		MethodMap::const_iterator it = m_methods.find(name);

		if (EXPECTED(it != m_methods.end())) {
			return it->second;
		}
		return NULL;
	}

	virtual bool isPrimitive() const { return false; }

	/// Method for retrieve the type name
	const CString* getName() const { return m_name; }

	/// Virtual method for debug purpose
	virtual void dump(const void*) const = 0;

	virtual void add(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void sub(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void mul(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void div(CLEVER_TYPE_OPERATOR_ARGS) const = 0;
	virtual void mod(CLEVER_TYPE_OPERATOR_ARGS) const = 0;

	virtual void* allocData() const { return NULL; }
	virtual void deallocData(void* data) {}

	virtual void increment(Value*) const = 0;
	virtual void decrement(Value*) const = 0;
private:
	const CString* m_name;
	MethodMap m_methods;
};

}

#endif // CLEVER_TYPE_H
