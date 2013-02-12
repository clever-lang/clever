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
	SAFETY_LOCK();
	cleanUp();
	m_type = value->getType();
	m_data = value->getData();

	if (EXPECTED(m_type && m_data)) {
		m_data->addRef();
	}
	SAFETY_ULOCK();
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
	SAFETY_LOCK();
	cleanUp();
	m_type = CLEVER_INT_TYPE;
	setObj(m_type, new IntObject(n));
	SAFETY_ULOCK();
}

long Value::getInt() const
{
	SAFETY_GET(long, IntObject, v);
}

void Value::setDouble(double n)
{
	SAFETY_LOCK();
	cleanUp();
	m_type = CLEVER_DOUBLE_TYPE;
	setObj(m_type, new DoubleObject(n));
	SAFETY_ULOCK();
}

double Value::getDouble() const
{
	SAFETY_GET(double, DoubleObject, v);
}

void Value::setStr(const CString* str)
{
	SAFETY_LOCK();
	cleanUp();
	m_type = CLEVER_STR_TYPE;
	setObj(m_type, new StrObject(str));
	SAFETY_ULOCK();
}

void Value::setStr(StrObject* str) {
	SAFETY_LOCK();
	cleanUp();
	m_type = CLEVER_STR_TYPE;
	setObj(m_type, str);
	SAFETY_ULOCK();
}

const CString* Value::getStr() const
{
	SAFETY_GET_STR(CString*, StrObject, v);
}

void Value::setBool(bool n)
{
	SAFETY_LOCK();
	cleanUp();
	m_type = CLEVER_BOOL_TYPE;
	setObj(m_type, new BoolObject(n));
	SAFETY_ULOCK();
}

bool Value::getBool() const
{
	SAFETY_GET(bool, BoolObject, v);
}

} // clever
