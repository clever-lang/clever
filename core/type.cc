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
		clever_delref(it->second.value);
	}
}

/// Copy the type members to the object instance
void TypeObject::copyMembers(const Type* type)
{
	clever_assert(m_members.empty(), "m_members must be empty");

	const MemberMap& members = type->getMembers();

	MemberMap::const_iterator it(members.begin()), end(members.end());

	for (; it != end; ++it) {
		if (it->second.value->isConst()) {
			addMember(it->first, it->second);
			clever_addref(it->second.value);
		} else {
			addMember(it->first, MemberData(it->second.value->clone(), it->second.flags));
		}
	}

	m_initialized = 1;
}

/// Deallocs memory used by type members
void Type::deallocMembers()
{
	MemberMap::iterator it(m_members.begin()), end(m_members.end());

	for (; it != end; ++it) {
		clever_delref(it->second.value);
	}
}

/// Serialization interface
std::pair<size_t, TypeObject*> Type::serialize(const Value* value) const
{
	clever_assert_not_null(value);

	size_t size;

	if (value->isInt()) {
		size = sizeof(IntObject);
	} else if (value->isDouble()) {
		size = sizeof(DoubleObject);
	} else if (value->isBool()) {
		size = sizeof(BoolObject);
	} else if (value->isStr()) {
		size = sizeof(StrObject);
	} else if (value->isArray()) {
		size = sizeof(ArrayObject);
	} else if (value->isMap()) {
		size = sizeof(MapObject);
	} else {
		size = sizeof(TypeObject);
	}

	return std::pair<size_t, TypeObject*>(size, value->getObj());
}

/// Unserialization interface
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

/// Add a new method to the type
Function* Type::addMethod(Function* func, size_t flags)
{
	Value* val = new Value;

	clever_assert_not_null(func);

	val->setObj(CLEVER_FUNC_TYPE, func);
	val->setConst(true);
	func->setContext(this);
	addMember(CSTRING(func->getName()), MemberData(val, flags));

	return func;
}

/// Fetchs a method by name
MemberData Type::getMethod(const CString* name) const
{
	MemberData mdata = getMember(name);

	return mdata.value && mdata.value->isFunction() ? mdata : MemberData(NULL, 0);
}

/// Fetchs a property by name
MemberData Type::getProperty(const CString* name) const
{
	MemberData mdata = getMember(name);

	return mdata.value && !mdata.value->isFunction() ? mdata : MemberData(NULL, 0);
}

/// Returns all the type methods
const MethodMap Type::getMethods() const
{
	MemberMap::const_iterator it(m_members.begin()), end(m_members.end());
	MethodMap mm;

	while (it != end) {
		if (it->second.value->isFunction()) {
			mm.insert(MethodMap::value_type(
				it->first, static_cast<Function*>(it->second.value->getObj())));
		}
		++it;
	}

	return mm;
}

/// Returns all the type properties
const PropertyMap Type::getProperties() const
{
	MemberMap::const_iterator it(m_members.begin()), end(m_members.end());
	PropertyMap pm;

	for (; it != end; ++it) {
		if (!it->second.value->isFunction()) {
			pm.insert(PropertyMap::value_type(it->first, it->second));
		}
	}

	return pm;
}

/// Sets the type constructor
void Type::setConstructor(MethodPtr method)
{
	m_ctor = addMethod(new Function("Constructor#" + getName(), method));
}

/// Sets the type destructor
void Type::setDestructor(MethodPtr method)
{
	m_dtor = addMethod(new Function("Destructor#" + getName(), method));
}

/// Default + operator implementation
CLEVER_TYPE_OPERATOR(Type::add)
{
	clever_throw("Cannot use + operator with %T type", this);
}

/// Default - operator implementation
CLEVER_TYPE_OPERATOR(Type::sub)
{
	clever_throw("Cannot use - operator with %T type", this);
}

/// Default * operator implementation
CLEVER_TYPE_OPERATOR(Type::mul)
{
	clever_throw("Cannot use * operator with %T type", this);
}

/// Default / operator implementation
CLEVER_TYPE_OPERATOR(Type::div)
{
	clever_throw("Cannot use / operator with %T type", this);
}

/// Default % operator implementation
CLEVER_TYPE_OPERATOR(Type::mod)
{
	clever_throw("Cannot use % operator with %T type", this);
}

/// Default > operator implementation
CLEVER_TYPE_OPERATOR(Type::greater)
{
	clever_throw("Cannot use > operator with %T type", this);
}

/// Default >= operator implementation
CLEVER_TYPE_OPERATOR(Type::greater_equal)
{
	clever_throw("Cannot use >= operator with %T type", this);
}

/// Default < operator implementation
CLEVER_TYPE_OPERATOR(Type::less)
{
	clever_throw("Cannot use < operator with %T type", this);
}

/// Default <= operator implementation
CLEVER_TYPE_OPERATOR(Type::less_equal)
{
	clever_throw("Cannot use <= operator with %T type", this);
}

/// Default = operator implementation
CLEVER_TYPE_OPERATOR(Type::equal)
{
	//clever_throw("Cannot use == operator with %T type", this);
	result->setBool(lhs->getObj() == rhs->getObj());
}

/// Default != operator implementation
CLEVER_TYPE_OPERATOR(Type::not_equal)
{
	//clever_throw("Cannot use != operator with %T type",  this);
	result->setBool(lhs->getObj() != rhs->getObj());
}

/// Default [] operator implementation
CLEVER_TYPE_AT_OPERATOR(Type::at_op)
{
	clever_throw("Cannot use [] operator with %T type", this);
	return NULL;
}

/// Default ! operator implementation
CLEVER_TYPE_UNARY_OPERATOR(Type::not_op)
{
	clever_throw("Cannot use ! operator with %T type", this);
}

/// Default & operator implementation
CLEVER_TYPE_OPERATOR(Type::bw_and)
{
	clever_throw("Cannot use & operator with %T type", this);
}

/// Default | operator implementation
CLEVER_TYPE_OPERATOR(Type::bw_or)
{
	clever_throw("Cannot use | operator with %T type", this);
}

/// Default ^ operator implementation
CLEVER_TYPE_OPERATOR(Type::bw_xor)
{
	clever_throw("Cannot use ^ operator with %T type", this);
}

/// Default ~ operator implementation
CLEVER_TYPE_UNARY_OPERATOR(Type::bw_not)
{
	clever_throw("Cannot use ~ operator with %T type", this);
}

/// Default << operator implementation
CLEVER_TYPE_OPERATOR(Type::bw_ls)
{
	clever_throw("Cannot use << operator with %T type", this);
}

/// Default >> operator implementation
CLEVER_TYPE_OPERATOR(Type::bw_rs)
{
	clever_throw("Cannot use >> operator with %T type", this);
}

/// Default ++ operator implementation
void Type::increment(Value* value, const VM* vm, CException* exception) const
{
	clever_throw("Cannot use ++ operator with %T type", this);
}

/// Default -- operator implementation
void Type::decrement(Value* value, const VM* vm, CException* exception) const
{
	clever_throw("Cannot use -- operator with %T type", this);
}

} // clever
