/*
 * Clever language
 * Copyright (c) 2011 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * $Id$
 */

#ifndef CLEVER_VALUES_H
#define CLEVER_VALUES_H

#include <stdint.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "refcounted.h"
#include "cstring.h"
#include "global.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

namespace clever {
class Type;
class Value;

typedef std::vector<Value*> ValueVector;

/**
 * Base class for value representation
 */
class NO_INIT_VTABLE Value : public RefCounted {
public:
	enum { SET, UNSET, MODIFIED };
	enum { NONE, INTEGER, DOUBLE, STRING, BOOLEAN, VECTOR, USER };
	enum { UNKNOWN, NAMED, CONST, TEMP };

	Value() : RefCounted(1), m_status(UNSET), m_type(UNKNOWN), m_kind(UNKNOWN) {}
	explicit Value(int kind) : RefCounted(1), m_status(UNSET), m_type(UNKNOWN), m_kind(kind) {}

	virtual ~Value() {
		if (isVector()) {
			ValueVector::iterator it = m_data.v_value->begin();

			while (it != m_data.v_value->end()) {
				(*it)->delRef();
				++it;
			}
			delete m_data.v_value;
		}
	}

	inline void set_type(int type) { m_type = type; }
	inline int get_type() const { return m_type; }
	inline int hasSameType(Value* value) const { return m_type == value->get_type(); }

	inline int get_kind() const { return m_kind; }
	inline void set_kind(int kind) { m_kind = kind; }

	inline int get_status() { return m_status; }
	inline void set_status(int status) { m_status = status; }

	inline bool hasSameKind(Value* value) { return get_kind() == value->get_kind(); }

	inline bool isConst() const { return m_kind == CONST; }
	inline bool isNamedValue(void) const { return m_kind == NAMED; }
	inline bool isTempValue(void) const { return m_kind == TEMP; }

	inline bool isSet(void) const { return m_status != UNSET; }
	inline bool isModified(void) const { return m_status == MODIFIED; }

	inline bool isInteger(void) const { return m_type == INTEGER; }
	inline bool isString(void) const { return m_type == STRING; }
	inline bool isDouble(void) const { return m_type == DOUBLE; }
	inline bool isBoolean(void) const { return m_type == BOOLEAN; }
	inline bool isVector(void) const { return m_type == VECTOR; }
	inline bool isUserValue(void) const { return m_type == USER; }

	inline void setInteger(int64_t i) { m_data.l_value = i; }
	inline void setString(CString* s) { m_data.s_value = s;	}
	inline void setDouble(double d) { m_data.d_value = d; }
	inline void setBoolean(bool b) { m_data.b_value = b; }
	inline void setVector(ValueVector* v) { m_data.v_value = v; }

	inline int64_t getInteger(void) const { return m_data.l_value; }
	inline CString* getStringP(void) const { return m_data.s_value; }
	inline CString getString(void) const { return *m_data.s_value; }
	inline double getDouble(void) const { return m_data.d_value; }
	inline bool getBoolean(void) const { return m_data.b_value; }
	inline ValueVector* getVector(void) const { return m_data.v_value; }

	virtual void set_value(Value* value) { }

	virtual Value* get_value(void) {
		return this;
	}

	virtual std::string toString(void) {
		std::stringstream str;

		switch (get_type()) {
			case INTEGER:
				str << getInteger();

				return str.str();
			case DOUBLE:
				str << getDouble();

				return str.str();
			case BOOLEAN:
				return std::string(getBoolean() ? "true" : "false");
			case STRING:
				return getString();
			default:
				return std::string();
		}
	}

	virtual Type* getType() { return m_type_ptr; }
private:
	int m_status;
	int m_type;
	int m_kind;
	Type* m_type_ptr;

	union {
		int64_t l_value;
		double d_value;
		bool b_value;
		CString* s_value;
		void* u_value;
		ValueVector* v_value;
	} m_data;
};

/**
 * Symbol names used for opcodes.
 *
 * e.g. Functions and Variables.
 */
class NamedValue : public Value {
public:
	NamedValue()
		: Value(NAMED), m_value(NULL) { }

	explicit NamedValue(CString* name)
		: Value(NAMED), m_value(NULL) {
		set_type(STRING);
		setString(name);
	}

	inline void set_value(Value* value) {
		m_value = value;
	}

	Value* get_value(void) {
		return m_value;
	}
private:
	Value* m_value;
};

/**
 * Constant values used for opcodes
 */
class ConstantValue : public Value {
public:
	explicit ConstantValue(double value)
		: Value(CONST) {
		set_type(DOUBLE);
		setDouble(value);
	}

	explicit ConstantValue(int64_t value)
		: Value(CONST) {
		set_type(INTEGER);
		setInteger(value);
	}

	explicit ConstantValue(CString* value)
		: Value(CONST) {
		set_type(STRING);
		setString(value);
	}

	explicit ConstantValue(bool value)
		: Value(CONST) {
		set_type(BOOLEAN);
		setBoolean(value);
	}

	~ConstantValue() { }
};

/**
 * Temporary storage used for opcodes to storage results
 */
class TempValue : public Value {
public:
	TempValue() : Value(TEMP), m_value(NULL) { }

	~TempValue() {
		if (m_value) {
			m_value->delRef();
		}
	}

	Value* get_value(void) {
		return m_value;
	}

	void set_value(Value* value) {
		if (m_value) {
			m_value->delRef();
		}

		m_value = value;
	}

	std::string toString() {
		if (m_value) {
			return m_value->toString();
		} else {
			return std::string();
		}
	}
private:
	Value* m_value;
};

} /* clever */
#endif /* CLEVER_VALUES_H */

