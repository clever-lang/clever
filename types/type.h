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
class Value;
class Type;
class Function;

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

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS) const;

typedef std::tr1::unordered_map<const CString*, Value*> MemberMap;
typedef std::tr1::unordered_map<const CString*, Value*> PropertyMap;
typedef std::tr1::unordered_map<const CString*, Function*> MethodMap;

class Type {
public:
	Type() {}

	explicit Type(const CString* name)
		: m_name(name), m_ctor(NULL), m_dtor(NULL) {}

	virtual ~Type() {}

	void deallocMembers();

	void addMember(const CString* name, Value* value) {
		m_members.insert(MemberMap::value_type(name, value));
	}

	Value* getMember(const CString* name) const {
		MemberMap::const_iterator it = m_members.find(name);

		if (it != m_members.end()) {
			return it->second;
		}

		return NULL;
	}

	Function* addMethod(Function*);

	const Function* getMethod(const CString*) const;

	void addProperty(const CString* name, Value* value) {
		addMember(name, value);
	}

	Value* getProperty(const CString*) const;

	const MethodMap getMethods() const;

	const PropertyMap getProperties() const;

	/// Method for retrieve the type name
	const CString* getName() const { return m_name; }

	void setConstructor(Function* func) { m_ctor = func; }
	void setDestructor(Function* func) { m_dtor = func; }

	const Function* getConstructor() const { return m_ctor; }
	const Function* getDestructor() const { return m_dtor; }

	virtual void init(CLEVER_TYPE_INIT_ARGS) {}

	virtual bool isPrimitive() const { return false; }

	/// Virtual method for debug purpose
	virtual void dump(const void* data) const { dump(data, std::cout); }
	virtual void dump(const void*, std::ostream&) const = 0;

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
	const Function* m_ctor;
	const Function* m_dtor;

	MemberMap m_members;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

}

#endif // CLEVER_TYPE_H
