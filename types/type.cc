/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "core/value.h"
#include "core/cexception.h"
#include "modules/std/core/function.h"

#include <algorithm>

namespace clever {

TypeObject::~TypeObject()
{
	PropertyMap::const_iterator it(m_properties.begin()),
		end(m_properties.end());

	while (it != end) {
		clever_delref((*it).second);
		++it;
	}
}

void TypeObject::copyMembers(const Type* type)
{
	const PropertyMap& props(type->getProperties());

	if (props.size() > 0) {
		PropertyMap::const_iterator it(props.begin()), end(props.end());

		for (; it != end; ++it) {
			addProperty(it->first, it->second->clone());
		}
	}

	const MethodMap& methods(type->getMethods());

	if (methods.size() > 0) {
		MethodMap::const_iterator it(methods.begin()), end(methods.end());

		for (; it != end; ++it) {
			addMethod(it->first, it->second);
		}
	}
}

void Type::deallocMembers()
{
	MemberMap::const_iterator it(m_members.begin()),
		end(m_members.end());

	while (it != end) {
		clever_delref((*it).second);
		++it;
	}
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

	if (val && !val->isFunction()) {
		return val;
	}

	return NULL;
}

const MethodMap Type::getMethods() const
{
	MemberMap::const_iterator it(m_members.begin()),
		end(m_members.end());

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
	MemberMap::const_iterator it(m_members.begin()),
		end(m_members.end());

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
	CLEVER_THROW("Cannot use + operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::sub)
{
	CLEVER_THROW("Cannot use - operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::mul)
{
	CLEVER_THROW("Cannot use * operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::div)
{
	CLEVER_THROW("Cannot use / operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::mod)
{
	CLEVER_THROW("Cannot use % operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::greater)
{
	CLEVER_THROW("Cannot use > operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::greater_equal)
{
	CLEVER_THROW("Cannot use >= operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::less)
{
	CLEVER_THROW("Cannot use < operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::less_equal)
{
	CLEVER_THROW("Cannot use <= operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::equal)
{
	CLEVER_THROW("Cannot use == operator with %S type", getName());
}

CLEVER_TYPE_OPERATOR(Type::not_equal)
{
	CLEVER_THROW("Cannot use != operator with %S type", getName());
}

void Type::increment(Value* value, const VM* vm, CException* exception) const
{
	CLEVER_THROW("Cannot use ++ operator with %S type", getName());
}

void Type::decrement(Value* value, const VM* vm, CException* exception) const
{
	CLEVER_THROW("Cannot use -- operator with %S type", getName());
}

} // clever
