/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "modules/std/core/int.h"
#include "modules/std/core/double.h"
#include "modules/std/core/bool.h"

namespace clever {

void Value::deepCopy(const Value* value)
{
	clever_assert_not_null(value);

	if (m_data && m_data->refCount() == 1) {
		if (isInt() && value->isInt()) {
			static_cast<IntObject*>(m_data)->value = value->getInt();
			return;
		} else if (isDouble() && value->isDouble()) {
			static_cast<DoubleObject*>(m_data)->value = value->getDouble();
			return;
		} else if (isBool() && value->isBool()) {
			static_cast<BoolObject*>(m_data)->value = value->getBool();
			return;
		}
	}

	TypeObject* val = value->isNull() ? NULL : value->getObj()->clone();

	if (val) {
		setObj(value->getType(),  val);
	} else {
		copy(value);
	}
}

void Value::setInt(long n)
{
	if (m_data && isInt() && m_data->refCount() == 1) {
		static_cast<IntObject*>(m_data)->value = n;
	} else {
		setObj(CLEVER_INT_TYPE, new IntObject(n));
	}
}

long Value::getInt() const
{
	return static_cast<IntObject*>(getObj())->value;
}

void Value::setDouble(double n)
{
	if (m_data && isDouble() && m_data->refCount() == 1) {
		static_cast<DoubleObject*>(m_data)->value = n;
	} else {
		setObj(CLEVER_DOUBLE_TYPE, new DoubleObject(n));
	}
}

double Value::getDouble() const
{
	return static_cast<DoubleObject*>(m_data)->value;
}

void Value::setStr(const CString* str)
{
	setObj(CLEVER_STR_TYPE, new StrObject(str));
}

void Value::setStr(StrObject* str)
{
	setObj(CLEVER_STR_TYPE, str);
}

void Value::setStr(const std::string& str)
{
	if (m_data && isStr() && m_data->refCount() == 1
		&& static_cast<StrObject*>(m_data)->interned == false) {
		*const_cast<CString*>(static_cast<StrObject*>(m_data)->value) = str;
	} else {
		setObj(CLEVER_STR_TYPE, new StrObject(str));
	}
}

const CString* Value::getStr() const
{
	return static_cast<StrObject*>(m_data)->value;
}

void Value::setBool(bool n)
{
	if (m_data && isBool() && m_data->refCount() == 1) {
		static_cast<BoolObject*>(m_data)->value = n;
	} else {
		setObj(CLEVER_BOOL_TYPE, new BoolObject(n));
	}
}

bool Value::getBool() const
{
	return static_cast<BoolObject*>(m_data)->value;
}

} // clever
