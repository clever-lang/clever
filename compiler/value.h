/**
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

	/**
	 * Variable states
	 */
	enum { SET, UNSET, MODIFIED };

	/**
	 * Data type
	 */
	enum { NONE, INTEGER, DOUBLE, STRING, BOOLEAN, VECTOR, USER };

	Value()
		: RefCounted(1), m_status(UNSET), m_type(NONE), m_type_ptr(NULL), m_name(NULL) { }

	explicit Value(const Type* type_ptr)
		: RefCounted(1), m_status(UNSET), m_type(NONE), m_type_ptr(type_ptr), m_name(NULL) { }

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
	int hasSameType(const Value* const value) const { return m_type == value->get_type(); }

	const Type* get_type_ptr() const { return m_type_ptr; }
	void set_type_ptr(const Type* const ptr) { m_type_ptr = ptr; }

	bool hasName() const { return m_name != NULL; }
	const CString* get_name() const { return m_name; }
	void set_name(const CString* const name) { m_name = name; }

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

	void setInteger(int64_t i) { m_type = INTEGER; m_data.l_value = i; }
	void setString(const CString* const s) { m_type = STRING; m_data.s_value = s; }
	void setDouble(double d) { m_type = DOUBLE; m_data.d_value = d; }
	void setBoolean(bool b) { m_type = BOOLEAN; m_data.b_value = b; }
	void setVector(ValueVector* v) { m_type = VECTOR; m_data.v_value = v; }

	int64_t getInteger() const { return m_data.l_value; }
	const CString* getStringP() const { return m_data.s_value; }
	const CString& getString() const { return *m_data.s_value; }
	double getDouble() const { return m_data.d_value; }
	bool getBoolean() const { return m_data.b_value; }
	ValueVector* getVector() const { return m_data.v_value; }

	const ValueData *get_data() const { return &m_data; }

	void copy(const Value* const value) throw() {
		std::memcpy(&m_data, value->get_data(), sizeof(ValueData));
		m_type = value->get_type();
	}
	void copy(Value& value) throw() {
		std::memcpy(&m_data, value.get_data(), sizeof(ValueData));
		m_type = value.get_type();
	}

	virtual Value* get_value() throw() { return this; }

	virtual const CString& toString() throw() {
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
		NONE,
		NEAR, /* Invoke compiled functions/methods. */
		FAR   /* Invoke built-in or loaded functions/methods. (probably faster)*/
	};

	/* TODO: generate name for anonymous functions, disable set_name(). */
	CallableValue()
		: m_call_type(NONE), m_context(NULL) { }

	/**
	 * Create a CallableValue to represent a named function.
	 */
	explicit CallableValue(const CString* const name)
		: Value(), m_call_type(NONE), m_context(NULL) {
		set_name(name);
	}

	/**
	 * Create a CallableValue able to represent a method.
	 */
	CallableValue(const CString* const name, const Type* const type)
		: Value(), m_call_type(NONE), m_context(NULL) {
		set_name(name);
		set_type_ptr(type);
	}

	~CallableValue() {
		if (isNearCall() && m_handler.func) {
			delete m_handler.func;
		}
	}

	void set_handler(const Function* const handler) throw() {
		m_call_type = handler->isInternal() ? FAR : NEAR;
		m_handler.func = handler;
	}

	void set_handler(const Method* const handler) throw() {
		m_call_type = handler->isInternal() ? FAR : NEAR;
		m_handler.method = handler;
	}

	void set_context(Value* const value) throw() { m_context = value; }
	Value* get_context() const throw() { return m_context; }

	const FunctionPtr get_function_ptr() const throw() { return m_handler.func->get_ptr(); }
	const MethodPtr get_method_ptr() const throw() { return m_handler.method->get_ptr(); }

	const Function* get_function() const throw() { return m_handler.func; }
	const Method* get_method() const throw() { return m_handler.method; }

	bool isCallable() const { return true; }

	bool isNearCall() const throw() { return m_call_type == NEAR; }
	bool isFarCall() const throw() { return m_call_type == FAR; }

	/**
	 * Invokes the method/function pointer according with the type.
	 *
	 * Remember to set a context before calling a non-static method.
	 */
	void call(Value* const result, const ValueVector* const args) const throw() {
		const Type* const type_ptr = get_type_ptr();

		if (UNEXPECTED(m_call_type == NEAR)) {
			/* TODO: throw error here */
		}

		if (type_ptr == NULL) {
			m_handler.func->call(args, result);
		} else {
			m_handler.method->call(args, result, m_context);
		}
	}

	void call(long& next_op) const throw() {
		next_op = m_handler.func->call();
	}
private:
	union {
		const Function* func;
		const Method* method;
	} m_handler;

	CallType m_call_type;
	Value* m_context;

	DISALLOW_COPY_AND_ASSIGN(CallableValue);
};

class UserTypeValue : public Value {
public:
	UserTypeValue(const CString* const name)
		: m_name(name) { }
	
	~UserTypeValue() { }
private:
	const CString* m_name;
	DISALLOW_COPY_AND_ASSIGN(UserTypeValue);
};

} // clever

#endif // CLEVER_VALUE_H
