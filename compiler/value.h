/**
 * Clever programming language
 * Copyright (c) 2012 Clever Team
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
#include "compiler/clever.h"
#include "compiler/refcounted.h"
#include "compiler/cstring.h"
#include "compiler/method.h"
#include "compiler/function.h"
#include "compiler/symboltable.h"

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
		DataValue* dv_value;
		ValueVector* v_value;
	} ValueData;

	/**
	 * Data type
	 */
	enum { NONE, PRIMITIVE, VECTOR, USER };

	Value()
		: RefCounted(1), m_type(NONE), m_type_ptr(NULL), m_name(NULL) { }

	explicit Value(const Type* type_ptr)
		: RefCounted(1), m_type(PRIMITIVE), m_type_ptr(type_ptr), m_name(NULL) { }

	explicit Value(double value)
		: RefCounted(1), m_type(PRIMITIVE), m_type_ptr(CLEVER_TYPE("Double")), m_name(NULL) {
		setDouble(value);
	}

	explicit Value(int64_t value)
		: RefCounted(1), m_type(PRIMITIVE), m_type_ptr(CLEVER_TYPE("Int")), m_name(NULL) {
		setInteger(value);
	}

	explicit Value(bool value)
		: RefCounted(1), m_type(PRIMITIVE), m_type_ptr(CLEVER_TYPE("Bool")), m_name(NULL) {
		setBoolean(value);
	}

	explicit Value(const CString* value)
		: RefCounted(1), m_type(PRIMITIVE), m_type_ptr(CLEVER_TYPE("String")), m_name(NULL) {
		setString(value);
	}

	virtual ~Value() {
		if (isUserValue()) {
			if (m_data.dv_value->refCount() == 0) {
				// Runs the type destructor
				getTypePtr()->destructor(this);
				delete m_data.dv_value;
			} else {
				m_data.dv_value->delRef();
			}			
		} else if (isVector()) {
			ValueVector::const_iterator it = m_data.v_value->begin(), end = m_data.v_value->end();

			while (it != end) {
				(*it)->delRef();
				++it;
			}
			delete m_data.v_value;
		}
	}

	void initialize() throw() {
		if (getTypePtr() == CLEVER_TYPE("Int")) {
			setInteger(0);
		}
		else if (getTypePtr() == CLEVER_TYPE("Double")) {
			setDouble(0.0);
		}
		else if (getTypePtr() == CLEVER_TYPE("Bool")) {
			setBoolean(false);
		}
		else if (getTypePtr() == CLEVER_TYPE("String")) {
			setString(CSTRING(""));
		}
	}

	void setType(int type) { 
		if (type == NONE || type == USER || type == VECTOR || type == PRIMITIVE) {
			m_type = type;
		}
	}
	
	int hasSameType(const Value* const value) const { 
		return m_type_ptr == value->getTypePtr(); 
	}

	const Type* getTypePtr() const { return m_type_ptr; }
	void setTypePtr(const Type* const ptr) { m_type_ptr = ptr; }

	bool hasName() const { return m_name != NULL; }
	const CString* getName() const { return m_name; }
	void setName(const CString* const name) { m_name = name; }

	virtual bool isPrimitive() const {
		return m_type_ptr == CLEVER_TYPE("Int") ||
			m_type_ptr == CLEVER_TYPE("Double") ||
			m_type_ptr == CLEVER_TYPE("Bool") ||
			m_type_ptr == CLEVER_TYPE("String");
	}

	/*
	 * Avoid using this check. Type your variables as a
	 * callable value instead of Value to ensure you can call it.
	 */
	virtual bool isCallable() const { return false; }

	bool isInteger()   const { return m_type_ptr == CLEVER_TYPE("Int"); }
	bool isString()    const { return m_type_ptr == CLEVER_TYPE("String"); }
	bool isDouble()    const { return m_type_ptr == CLEVER_TYPE("Double"); }
	bool isBoolean()   const { return m_type_ptr == CLEVER_TYPE("Bool"); }
	bool isVector()    const { return m_type == VECTOR; }
	bool isUserValue() const { return m_type == USER; }

	void setInteger(int64_t i) { 
		m_type_ptr = CLEVER_TYPE("Int");
		m_type = PRIMITIVE; 
		m_data.l_value = i; 
	}
	
	void setString(const CString* const s) { 
		m_type_ptr = CLEVER_TYPE("String");
		m_type = PRIMITIVE; 
		m_data.s_value = s; 
	}
	
	void setDouble(double d) { 
		m_type_ptr = CLEVER_TYPE("Double");
		m_type = PRIMITIVE; 
		m_data.d_value = d; 
	}
	
	void setBoolean(bool b) { 
		m_type_ptr = CLEVER_TYPE("Bool");
		m_type = PRIMITIVE; 
		m_data.b_value = b; 
	}
	
	
	void setVector(ValueVector* v) { m_type = VECTOR; m_data.v_value = v; }

	int64_t getInteger() const { return m_data.l_value; }
	const CString* getStringP() const { return m_data.s_value; }
	const CString& getString() const { return *m_data.s_value; }
	double getDouble() const { return m_data.d_value; }
	bool getBoolean() const { return m_data.b_value; }
	ValueVector* getVector() const { return m_data.v_value; }
	
	bool getValueAsBool() const {
		if (m_type_ptr == CLEVER_TYPE("Int")) {
			return getInteger();
		}
		else if (m_type_ptr == CLEVER_TYPE("Double")) {
			return getDouble();
		}
		else if (m_type_ptr == CLEVER_TYPE("String")) {
			return !getString().empty();
		}
		else if (m_type_ptr == CLEVER_TYPE("Bool")) {
			return getBoolean();
		}
		
		return false;
	}
	
	bool isNumeric() const {
		return (m_type_ptr == CLEVER_TYPE("Double") || m_type_ptr == CLEVER_TYPE("Int"));
	}

	const ValueData* getData() const { return &m_data; }
	
	// Sets the buffer for a user type structure
	void setDataValue(DataValue* data) { 
		m_data.dv_value = data;
		m_type = USER;
	}
	
	DataValue* getDataValue() {
		return m_data.dv_value;
	}

	void copy(const Value* const value) throw() {
		std::memcpy(&m_data, value->getData(), sizeof(ValueData));
		m_type_ptr = value->getTypePtr();
	}
	void copy(Value& value) throw() {
		std::memcpy(&m_data, value.getData(), sizeof(ValueData));
		m_type_ptr = value.getTypePtr();
	}

	virtual Value* getValue() throw() { return this; }

	virtual const CString& toString() throw() {
		std::ostringstream str;

		if (getTypePtr() == CLEVER_TYPE("Int")) {
			str << getInteger();
		}
		else if (getTypePtr() == CLEVER_TYPE("Double")) {
			str << getDouble();
		}
		else if (getTypePtr() == CLEVER_TYPE("Bool")) {
				return *CSTRING(getBoolean() ? "true" : "false");
		}
		else if (getTypePtr() == CLEVER_TYPE("String")) {
				return getString();
		}
		else {
			return *CSTRING("");
		}
		
		return *CSTRING(str.str());
	}
private:
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

	/* TODO: generate name for anonymous functions, disable setName(). */
	CallableValue()
		: m_call_type(NONE), m_context(NULL) { }

	/**
	 * Create a CallableValue to represent a named function.
	 */
	explicit CallableValue(const CString* const name)
		: Value(), m_call_type(NONE), m_context(NULL) {
		setName(name);
	}

	/**
	 * Create a CallableValue able to represent a method.
	 */
	CallableValue(const CString* const name, const Type* const type)
		: Value(), m_call_type(NONE), m_context(NULL) {
		setName(name);
		setTypePtr(type);
	}

	~CallableValue() {
		if (isNearCall() && m_handler.func) {
			delete m_handler.func;
		}
	}

	void setHandler(Function* handler) throw() {
		m_call_type = handler->isInternal() ? FAR : NEAR;
		m_handler.func = handler;
	}

	void setHandler(const Method* const handler) throw() {
		m_call_type = handler->isInternal() ? FAR : NEAR;
		m_handler.method = handler;
	}

	void setContext(Value* const value) throw() { m_context = value; }
	Value* getContext() const throw() { return m_context; }

	const FunctionPtr getFunctionPtr() const throw() { return m_handler.func->getPtr(); }
	const MethodPtr getMethodPtr() const throw() { return m_handler.method->getPtr(); }

	Function* getFunction() const throw() { return m_handler.func; }
	const Method* getMethod() const throw() { return m_handler.method; }

	bool isCallable() const { return true; }

	bool isNearCall() const throw() { return m_call_type == NEAR; }
	bool isFarCall() const throw() { return m_call_type == FAR; }
	
	/**
	 * A callable value is not primitive
	 */
	virtual bool isPrimitive() const { return false; }

	/**
	 * Invokes the method/function pointer according with the type.
	 *
	 * Remember to set a context before calling a non-static method.
	 */
	void call(Value* const result, const ValueVector* const args) const throw() {
		const Type* const type_ptr = getTypePtr();

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
		Function* func;
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
