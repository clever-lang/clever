/*
 * Clever programming language
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

#ifndef CLEVER_VALUE_H
#define CLEVER_VALUE_H

#include <stdint.h>
#include <cstring>
#include <sstream>
#include <vector>
#include "refcounted.h"
#include "cstring.h"
#include "global.h"
#include "module.h"

namespace clever {

class Type;
class Value;

/**
 * Base class for value representation
 */
class NO_INIT_VTABLE Value : public RefCounted {
public:
	typedef union {
		int64_t l_value;
		double d_value;
		bool b_value;
		const CString* s_value;
		void* u_value;
		ValueVector* v_value;
	} ValueData;

	enum { SET, UNSET, MODIFIED };
	enum { NONE, INTEGER, DOUBLE, STRING, BOOLEAN, VECTOR, USER };
	enum { UNKNOWN, CONST };

	Value() : RefCounted(1), m_status(UNSET), m_type(UNKNOWN), m_type_ptr(NULL), m_name(NULL) {}
	explicit Value(double value)
		: RefCounted(1), m_status(UNSET), m_type(DOUBLE), m_type_ptr(NULL), m_name(NULL) {
			setDouble(value);
		}
	explicit Value(int64_t value)
		: RefCounted(1), m_status(UNSET), m_type(INTEGER), m_type_ptr(NULL), m_name(NULL) {
			setInteger(value);
		}
	explicit Value(bool value)
		: RefCounted(1), m_status(UNSET), m_type(BOOLEAN), m_type_ptr(NULL), m_name(NULL) {
			setBoolean(value);
		}
	explicit Value(const CString* value)
		: RefCounted(1), m_status(UNSET), m_type(STRING), m_type_ptr(NULL), m_name(NULL) {
			setString(value);
		}
//	explicit Value(const CString* name) : RefCounted(1), m_status(UNSET), m_type(UNKNOWN), m_kind(UNKNOWN), m_type_ptr(NULL), m_name(name) {}
//	explicit Value(int kind) : RefCounted(1), m_status(UNSET), m_type(UNKNOWN), m_kind(kind), m_type_ptr(NULL), m_name(NULL) {}

	virtual ~Value() {
		if (isVector()) {
			ValueVector::const_iterator it = m_data.v_value->begin(), end = m_data.v_value->end();

			while (it != end) {
				(*it)->delRef();
				++it;
			}
			delete m_data.v_value;
		}
	}

	void initialize() throw() {
		switch (m_type) {
			case Value::DOUBLE:
				m_data.d_value = 0;
				break;
			case Value::INTEGER:
				m_data.l_value = 0;
				break;
			case Value::BOOLEAN:
				m_data.b_value = false;
				break;
			case Value::STRING:
				m_data.s_value = CSTRING("");
				break;
		}
	}

	void set_type(int type) { m_type = type; }
	int get_type() const { return m_type; }
	int hasSameType(Value* value) const { return m_type == value->get_type(); }

	const Type* get_type_ptr() const { return m_type_ptr; }
	void set_type_ptr(const Type* ptr) { m_type_ptr = ptr; }

	bool hasName() const { return m_name != NULL; }
	const CString* get_name() const { return m_name; }
	void set_name(const CString* name) { m_name = name; }

	int get_status() { return m_status; }
	void set_status(int status) { m_status = status; }

	bool isInitialized() const { return m_status == SET; }
	bool isUninitialized() const { return m_status == UNSET; }
	bool isModified() const { return m_status == MODIFIED; }

	void setInitialized() { m_status = SET; }
	void setUninitialized() { m_status = UNSET; }
	void setModified() { m_status = MODIFIED; }

	bool isPrimitive() const {
		return m_type == INTEGER ||
			m_type == DOUBLE ||
			m_type == BOOLEAN ||
			m_type == STRING;
	}

	/*
	 * Avoid using this check. Type your variables as a
	 * callable value instead of Value to ensure you can call it.
	 */
	virtual bool isCallable() const { return false; }

	bool isInteger() const { return m_type == INTEGER; }
	bool isString() const { return m_type == STRING; }
	bool isDouble() const { return m_type == DOUBLE; }
	bool isBoolean() const { return m_type == BOOLEAN; }
	bool isVector() const { return m_type == VECTOR; }
	bool isUserValue() const { return m_type == USER; }

	void setInteger(int64_t i) { m_data.l_value = i; }
	void setString(const CString* s) { m_data.s_value = s; }
	void setDouble(double d) { m_data.d_value = d; }
	void setBoolean(bool b) { m_data.b_value = b; }
	void setVector(ValueVector* v) { m_data.v_value = v; }

	int64_t getInteger() const { return m_data.l_value; }
	const CString* getStringP() const { return m_data.s_value; }
	const CString& getString() const { return *m_data.s_value; }
	double getDouble() const { return m_data.d_value; }
	bool getBoolean() const { return m_data.b_value; }
	ValueVector* getVector() const { return m_data.v_value; }

	const ValueData *get_data() const { return &m_data; }

	void copy(const Value* value) {
		std::memcpy(&m_data, value->get_data(), sizeof(ValueData));
		m_type = value->get_type();
	}
	void copy(Value& value) {
		std::memcpy(&m_data, value.get_data(), sizeof(ValueData));
		m_type = value.get_type();
	}

	virtual Value* get_value() { return this; }

	virtual const CString& toString() {
		std::ostringstream str;

		switch (get_type()) {
			case INTEGER:
				str << getInteger();

				return *CSTRING(str.str());
			case DOUBLE:
				str << getDouble();

				return *CSTRING(str.str());
			case BOOLEAN:
				return *CSTRING(getBoolean() ? "true" : "false");
			case STRING:
				return getString();
			default:
				return *CSTRING("");
		}
	}
private:
	int m_status;
	int m_type;
	const Type* m_type_ptr;
	const CString* m_name;
	ValueData m_data;

	DISALLOW_COPY_AND_ASSIGN(Value);
};

/**
 * Class that represents the values of functions and methods.
 */
class CallableValue : public Value {
public:
	enum CallType {
		NEAR, /* Invoke compiled functions/methods. */
		FAR   /* Invoke built-in or loaded functions/methods. (probably faster)*/
	};

	/* TODO: generate name for anonymous functions, disable set_name(). */
	CallableValue()
		: m_context(NULL) { }

	/**
	 * Create a CallableValue to represent a named function.
	 */
	explicit CallableValue(const CString* name)
		: Value(), m_call_type(FAR), m_context(NULL) {
			set_name(name);
		}

	/**
	 * Create a CallableValue able to represent a method.
	 */
	CallableValue(const CString* name, Type* type)
		: Value(), m_call_type(FAR), m_context(NULL) {
		set_name(name);
		set_type_ptr(type);
	}

	~CallableValue() { }

	void set_callback(FunctionPtr callback) throw() {
		m_call_type = FAR;
		m_callback.f_ptr = callback;
	}

	void set_callback(MethodPtr callback) throw() {
		m_call_type = FAR;
		m_callback.m_ptr = callback;
	}

	void set_context(Value* value) throw() { m_context = value; }
	Value* get_context() const throw() { return m_context; }

	const FunctionPtr get_function() const throw() { return m_callback.f_ptr; }
	const MethodPtr get_method() const throw() { return m_callback.m_ptr; }

	bool isCallable() const { return true; }

	bool isNearCall() const throw() { return m_call_type == NEAR; }
	bool isFarCall() const throw() { return m_call_type == FAR; }

	/**
	 * Invokes the method/function pointer according with the type.
	 *
	 * Remember to set a context before calling a non-static method.
	 */
	void call(Value* result, const ValueVector* args) const throw() {

		if (UNEXPECTED(m_call_type == NEAR)) {
			/* TODO: throw error here */
		}

		const Type* type_ptr = get_type_ptr();

		if (type_ptr == NULL) {
			m_callback.f_ptr(args, result);
		} else {
			m_callback.m_ptr(args, result, m_context);
		}
	}

	void call(Value* context, Value* result, const ValueVector* args) const throw() {
		if (UNEXPECTED(m_call_type == NEAR || get_type_ptr() == NULL)) {
			/* TODO: throw error here */
		}

		m_callback.m_ptr(args, result, context);
	}

	void call(long& next_op) const throw() {
		next_op = m_callback.m_addr;
	}

	/**
	 * User defined functions
	 */
	void set_addr(unsigned int num) throw() {
		m_call_type = NEAR;
		m_callback.m_addr = num;
	}


private:
	union {
		FunctionPtr f_ptr;
		MethodPtr m_ptr;
		unsigned int m_addr;
	} m_callback;

	Value* m_context;

	CallType m_call_type;

	DISALLOW_COPY_AND_ASSIGN(CallableValue);
};

} // clever

#endif // CLEVER_VALUE_H
