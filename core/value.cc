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

void Value::copy(const Value* value)
{
	cleanUp();
	m_type = value->getType();
	m_data = value->getData();

	if (EXPECTED(m_type && m_data)) {
		m_data->addRef();
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
	cleanUp();
	m_type = CLEVER_INT_TYPE;
	setObj(m_type, new IntObject(n));
}

long Value::getInt() const
{
	return static_cast<IntObject*>(getObj())->value;
}

void Value::setDouble(double n)
{
	cleanUp();
	m_type = CLEVER_DOUBLE_TYPE;
	setObj(m_type, new DoubleObject(n));
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
	cleanUp();
	m_type = CLEVER_BOOL_TYPE;
	setObj(m_type, new BoolObject(n));
}

bool Value::getBool() const
{
	return static_cast<BoolObject*>(getObj())->value;
}

} // clever
