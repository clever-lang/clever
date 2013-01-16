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
#include <vector>
#include "core/clever.h"
#include "core/cstring.h"

namespace clever {

class CException;
class VM;

#define CLEVER_TYPE_OPERATOR_ARGS Value* result, const Value* lhs, const Value* rhs, const VM* vm, CException* exception

#define CLEVER_TYPE_VIRTUAL_METHOD_DECLARATIONS                          \
	void CLEVER_FASTCALL add(CLEVER_TYPE_OPERATOR_ARGS)           const; \
	void CLEVER_FASTCALL sub(CLEVER_TYPE_OPERATOR_ARGS)           const; \
	void CLEVER_FASTCALL mul(CLEVER_TYPE_OPERATOR_ARGS)           const; \
	void CLEVER_FASTCALL div(CLEVER_TYPE_OPERATOR_ARGS)           const; \
	void CLEVER_FASTCALL mod(CLEVER_TYPE_OPERATOR_ARGS)           const; \
	void CLEVER_FASTCALL equal(CLEVER_TYPE_OPERATOR_ARGS)         const; \
	void CLEVER_FASTCALL not_equal(CLEVER_TYPE_OPERATOR_ARGS)     const; \
	void CLEVER_FASTCALL greater(CLEVER_TYPE_OPERATOR_ARGS)       const; \
	void CLEVER_FASTCALL greater_equal(CLEVER_TYPE_OPERATOR_ARGS) const; \
	void CLEVER_FASTCALL less(CLEVER_TYPE_OPERATOR_ARGS)          const; \
	void CLEVER_FASTCALL less_equal(CLEVER_TYPE_OPERATOR_ARGS)    const;

#define CLEVER_TYPE_OPERATOR(name) void CLEVER_FASTCALL name(CLEVER_TYPE_OPERATOR_ARGS) const

#define CLEVER_THIS() obj

#define CLEVER_TYPE_INIT_ARGS
#define CLEVER_TYPE_INIT(name) void name(CLEVER_TYPE_INIT_ARGS)

#define CLEVER_METHOD_ARGS Value* result, const Value* obj, const ::std::vector<Value*>& args, const VM* vm, CException* exception
#define CLEVER_METHOD(name) void name(CLEVER_METHOD_ARGS) const

#define CLEVER_TYPE_CTOR_ARGS const ::std::vector<Value*>* args
#define CLEVER_TYPE_DTOR_ARGS void* data

class Value;
class Type;
class Function;

/**
 * POD property class
 */
struct Property {
	enum Modifier {
		PUBLIC =  1 << 1,
		PRIVATE = 1 << 2,
		PROTECTED = 1 << 3,
		STATIC = 1 << 4
	};

	Value* value;
	unsigned char modifiers;
};

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS) const;

typedef std::tr1::unordered_map<const CString*, Property> PropertyMap;
typedef std::pair<const CString*, Property> PropertyPair;

typedef std::tr1::unordered_map<const CString*, Function*> MethodMap;
typedef std::pair<const CString*, Function*> MethodPair;

class Type {
public:
	Type(const CString* name)
		: m_name(name), m_methods(), m_properties() {}

	virtual ~Type();

	Function* addMethod(Function* func);

	void addProperty(const CString* name, Value* value,
		unsigned char modifiers = Property::PUBLIC) {

		Property prop = {value, modifiers};
		m_properties.insert(PropertyPair(name, prop));
	}

	const Function* getMethod(const CString* name) const {
		MethodMap::const_iterator it = m_methods.find(name);

		if (EXPECTED(it != m_methods.end())) {
			return it->second;
		}
		return NULL;
	}

	Value* getProperty(const CString* name) const {
		PropertyMap::const_iterator it = m_properties.find(name);

		if (EXPECTED(it != m_properties.end())) {
			return it->second.value;
		}
		return NULL;
	}

	/// Method for retrieve the type name
	const CString* getName() const { return m_name; }

	virtual void init(CLEVER_TYPE_INIT_ARGS) {}

	virtual bool isPrimitive() const { return false; }

	/// Virtual method for debug purpose
	virtual void dump(const void*) const = 0;
	virtual void dump(const void*, std::ostream& out) const = 0;

	/// Operator methods
	virtual void CLEVER_FASTCALL add(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL sub(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL mul(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL div(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL mod(CLEVER_TYPE_OPERATOR_ARGS)           const;
	virtual void CLEVER_FASTCALL equal(CLEVER_TYPE_OPERATOR_ARGS)         const;
	virtual void CLEVER_FASTCALL not_equal(CLEVER_TYPE_OPERATOR_ARGS)     const;
	virtual void CLEVER_FASTCALL greater(CLEVER_TYPE_OPERATOR_ARGS)       const;
	virtual void CLEVER_FASTCALL greater_equal(CLEVER_TYPE_OPERATOR_ARGS) const;
	virtual void CLEVER_FASTCALL less(CLEVER_TYPE_OPERATOR_ARGS)          const;
	virtual void CLEVER_FASTCALL less_equal(CLEVER_TYPE_OPERATOR_ARGS)    const;
	virtual void increment(Value*, const VM*, CException*)                const;
	virtual void decrement(Value*, const VM*, CException*)                const;

	/// Type internal data constructor
	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }

	/// Type internal data destructor
	virtual void deallocData(CLEVER_TYPE_DTOR_ARGS) {}
private:
	const CString* m_name;
	MethodMap m_methods;
	PropertyMap m_properties;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

}

#endif // CLEVER_TYPE_H
