/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <algorithm>
#include "core/clever.h"
#include "core/type.h"
#include "core/value.h"
#include "core/cexception.h"
#include "core/native_types.h"

namespace clever {

TypeObject::~TypeObject()
{
	MemberMap::const_iterator it(m_members.begin()), end(m_members.end());

	for (; it != end; ++it) {
		clever_delref(it->second);
	}
}

void TypeObject::copyMembers(const Type* type)
{
	clever_assert(m_members.empty(), "m_members must be empty");

	const MemberMap& members = type->getMembers();

	if (!members.empty()) {
		MemberMap::const_iterator it(members.begin()), end(members.end());

		for (; it != end; ++it) {
			addMember(it->first, it->second->clone());
		}
	}
}

void Type::deallocMembers()
{
	MemberMap::iterator it(m_members.begin()), end(m_members.end());

	for (; it != end; ++it) {
		clever_delref(it->second);
	}
}

std::pair<size_t, TypeObject*> Type::serialize(const Value* value) const
{
	clever_assert_not_null(value);

	const Type* type = value->getType();
	size_t size;

	if (type == CLEVER_INT_TYPE) {
		size = sizeof(IntObject);
	} else if (type == CLEVER_DOUBLE_TYPE) {
		size = sizeof(DoubleObject);
	} else if (type == CLEVER_BOOL_TYPE) {
		size = sizeof(BoolObject);
	} else if (type == CLEVER_STR_TYPE) {
		size = sizeof(StrObject);
	} else if (type == CLEVER_ARRAY_TYPE) {
		size = sizeof(ArrayObject);
	} else if (type == CLEVER_MAP_TYPE) {
		size = sizeof(MapObject);
	} else {
		size = sizeof(TypeObject);
	}

	return std::pair<size_t, TypeObject*>(size, value->getObj());
}

Value* Type::unserialize(const Type* type, const std::pair<size_t, TypeObject*>& data) const
{
	Value* value = new Value;

	if (type == CLEVER_INT_TYPE) {
		value->setInt(static_cast<IntObject*>(data.second)->value);
	} else if (type == CLEVER_DOUBLE_TYPE) {
		value->setDouble(static_cast<DoubleObject*>(data.second)->value);
	} else if (type == CLEVER_BOOL_TYPE) {
		value->setBool(static_cast<BoolObject*>(data.second)->value);
	} else if (type == CLEVER_STR_TYPE) {
		value->setStr(static_cast<StrObject*>(data.second)->value);
	}

	return value;
}

Function* Type::addMethod(Function* func)
{
	Value* val = new Value;

	clever_assert_not_null(func);

	val->setObj(CLEVER_FUNC_TYPE, func);
	addMember(CSTRING(func->getName()), val);

	return func;
}

const Function* Type::getMethod(const CString* name) const
{
	Value* val = getMember(name);

	if (val && val->isFunction()) {
		return static_cast<Function*>(val->getObj());
	}

	return NULL;
}

Value* Type::getProperty(const CString* name) const
{
	Value* val = getMember(name);

	return (val && !val->isFunction()) ? val : NULL;
}

const MethodMap Type::getMethods() const
{
	MemberMap::const_iterator it(m_members.begin()), end(m_members.end());
	MethodMap mm;

	while (it != end) {
		if (it->second->isFunction()) {
			mm.insert(MethodMap::value_type(
				it->first, static_cast<Function*>(it->second->getObj())));
		}
		++it;
	}

	return mm;
}

const PropertyMap Type::getProperties() const
{
	MemberMap::const_iterator it(m_members.begin()), end(m_members.end());
	PropertyMap pm;

	while (it != end) {
		if (!it->second->isFunction()) {
			pm.insert(*it);
		}
		++it;
	}

	return pm;
}

CLEVER_TYPE_OPERATOR(Type::add)
{
	clever_throw("Cannot use + operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::sub)
{
	clever_throw("Cannot use - operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::mul)
{
	clever_throw("Cannot use * operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::div)
{
	clever_throw("Cannot use / operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::mod)
{
	clever_throw("Cannot use % operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::greater)
{
	clever_throw("Cannot use > operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::greater_equal)
{
	clever_throw("Cannot use >= operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::less)
{
	clever_throw("Cannot use < operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::less_equal)
{
	clever_throw("Cannot use <= operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::equal)
{
	clever_throw("Cannot use == operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::not_equal)
{
	clever_throw("Cannot use != operator with %s type", getName().c_str());
}

CLEVER_TYPE_AT_OPERATOR(Type::at_op)
{
	clever_throw("Cannot use [] operator with %s type", getName().c_str());
	return NULL;
}

CLEVER_TYPE_UNARY_OPERATOR(Type::not_op)
{
	clever_throw("Cannot use ! operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::bw_and)
{
	clever_throw("Cannot use & operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::bw_or)
{
	clever_throw("Cannot use | operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::bw_xor)
{
	clever_throw("Cannot use ^ operator with %s type", getName().c_str());
}

CLEVER_TYPE_UNARY_OPERATOR(Type::bw_not)
{
	clever_throw("Cannot use ~ operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::bw_ls)
{
	clever_throw("Cannot use << operator with %s type", getName().c_str());
}

CLEVER_TYPE_OPERATOR(Type::bw_rs)
{
	clever_throw("Cannot use >> operator with %s type", getName().c_str());
}

void Type::increment(Value* value, const VM* vm, CException* exception) const
{
	clever_throw("Cannot use ++ operator with %s type", getName().c_str());
}

void Type::decrement(Value* value, const VM* vm, CException* exception) const
{
	clever_throw("Cannot use -- operator with %s type", getName().c_str());
}

void Type::setConstructor(MethodPtr method)
{
	m_ctor = addMethod(new Function("Constructor#" + getName(), method));
}

void Type::setDestructor(MethodPtr method)
{
	m_dtor = addMethod(new Function("Destructor#" + getName(), method));
}

} // clever
