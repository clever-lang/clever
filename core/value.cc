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
#include "core/cthread.h"

namespace clever {

void Value::deepCopy(const Value* value)
{
	clever_assert_not_null(value);

	if (m_data && m_data->refCount() == 1) {
		if (isInt() && value->isInt()) {
			setInt(value->getInt());
			return;
		} else if (isDouble() && value->isDouble()) {
			setDouble(value->getDouble());
			return;
		}
	}
	TypeObject* val = value->isNull() ? NULL : value->getObj()->clone();

	if (val) {
		cleanUp();
		setObj(value->getType(),  val);
	} else {
		copy(value);
	}
}

bool Value::asBool() const
{
	if (isNull()) {
		return false;
	} else if (isBool()) {
		return getBool();
	}
	return true;
}

void Value::setInt(long n)
{
	if (m_data && m_data->refCount() == 1 && isInt()) {
		static_cast<IntObject*>(getObj())->value = n;
	} else {
		cleanUp();

		m_type = CLEVER_INT_TYPE;
		setObj(m_type, new IntObject(n));
	}
}

long Value::getInt() const
{
	return static_cast<IntObject*>(getObj())->value;
}

void Value::setDouble(double n)
{
	if (m_data && m_data->refCount() == 1 && isDouble()) {
		static_cast<DoubleObject*>(getObj())->value = n;
	} else {
		cleanUp();
		m_type = CLEVER_DOUBLE_TYPE;
		setObj(m_type, new DoubleObject(n));
	}
}

double Value::getDouble() const
{
	return static_cast<DoubleObject*>(getObj())->value;
}

void Value::setStr(const CString* str)
{
	cleanUp();
	m_type = CLEVER_STR_TYPE;
	setObj(m_type, new StrObject(str));
}

void Value::setStr(StrObject* str)
{
	cleanUp();
	m_type = CLEVER_STR_TYPE;
	setObj(m_type, str);
}

const CString* Value::getStr() const
{
	return static_cast<StrObject*>(getObj())->value;
}

void Value::setBool(bool n)
{
	if (m_data && m_data->refCount() == 1 && isBool()) {
		static_cast<BoolObject*>(getObj())->value = n;
	} else {
		cleanUp();
		m_type = CLEVER_BOOL_TYPE;
		setObj(m_type, new BoolObject(n));
	}
}

bool Value::getBool() const
{
	return static_cast<BoolObject*>(getObj())->value;
}

} // clever
