/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
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
#include "compiler/clever.h"
#include "compiler/cached_ptrs.h"
#include "compiler/refcounted.h"
#include "compiler/cstring.h"
#include "compiler/method.h"
#include "compiler/function.h"

namespace clever {

class Scope;

/**
 * Native types
 */
extern Type* CLEVER_INT_VAR;
extern Type* CLEVER_DOUBLE_VAR;
extern Type* CLEVER_STR_VAR;
extern Type* CLEVER_BOOL_VAR;
extern Type* CLEVER_BYTE_VAR;
extern Type* CLEVER_ARRAY_VAR;
extern Type* CLEVER_OBJ_VAR;

/**
 * Base class for value representation
 */
class Value : public RefCounted {
public:
	union ValueData {
		int64_t l_value;
		double d_value;
		bool b_value;
		const CString* s_value;
		DataValue* dv_value;
		uint8_t c_value;
		Value* ref_value;

		ValueData()
			: s_value(NULL) {}
	};

	/**
	 * Data type
	 */
	enum ValueType {
		NONE,
		VAR,
		CALL,
		REF
	};

	Value()
		: RefCounted(1), m_type(NONE), m_type_ptr(NULL), m_name(NULL),
		  m_is_const(false) {}

	explicit Value(const Type* type_ptr)
		: RefCounted(1), m_type(VAR), m_type_ptr(type_ptr), m_name(NULL),
		  m_is_const(false) {
		setTypePtr(type_ptr);
	}

	explicit Value(double value)
		: RefCounted(1), m_type(VAR), m_type_ptr(CLEVER_DOUBLE),
		  m_name(NULL), m_is_const(false) {
		setDouble(value);
	}

	explicit Value(int64_t value)
		: RefCounted(1), m_type(VAR), m_type_ptr(CLEVER_INT),
		  m_name(NULL), m_is_const(false) {
		setInteger(value);
	}

	explicit Value(bool value)
		: RefCounted(1), m_type(VAR), m_type_ptr(CLEVER_BOOL),
		  m_name(NULL), m_is_const(false) {
		setBoolean(value);
	}

	explicit Value(const CString* value)
		: RefCounted(1), m_type(VAR), m_type_ptr(CLEVER_STR),
		  m_name(NULL), m_is_const(false) {
		setString(value);
	}

	explicit Value(uint8_t value)
		: RefCounted(1), m_type(VAR), m_type_ptr(CLEVER_BYTE),
		  m_name(NULL), m_is_const(false) {
		setByte(value);
	}

	explicit Value(Value* value)
		: RefCounted(1), m_type(REF), m_type_ptr(NULL), m_name(NULL),
		  m_is_const(false) {
		setReference(value);
	}

	virtual ~Value() {
		if (isInternal()) {
			if (m_data.dv_value) {
				if (m_data.dv_value->refCount() == 1) {
					getTypePtr()->destructor(this);
				}

				m_data.dv_value->delRef();
			}
		}
		else if (isPrimitive() && isString() && m_data.s_value
			 && !m_data.s_value->isInterned()) {
			const_cast<CString*>(m_data.s_value)->delRef();
		}
	}

	void initialize();

	ValueType getType() const { return m_type; }

	void setType(ValueType type) {
		if (EXPECTED(type == NONE || type == VAR ||
		 	type == REF || type == CALL)) {
			m_type = type;
		}
	}

	bool hasSameType(const Value* const value) const {
		return m_type_ptr == value->getTypePtr();
	}

	const Type* getTypePtr() const { return m_type_ptr; }

	void setTypePtr(const Type* ptr) { m_type_ptr = ptr; }

	bool hasName() const { return m_name != NULL; }
	const CString* getName() const { return m_name; }
	void setName(const CString* const name) { m_name = name; }

	bool isPrimitive() const {
		if (m_type_ptr == NULL) return false;
		return m_type_ptr->getKind() == Type::PRIMITIVE;
	}

	/**
	 * Avoid using this check. Type your variables as a
	 * callable value instead of Value to ensure you can call it.
	 */
	virtual bool isCallable() const { return m_type == CALL; }

	bool isInteger()   const { return m_type_ptr == CLEVER_INT; }
	bool isString()    const { return m_type_ptr == CLEVER_STR; }
	bool isDouble()    const { return m_type_ptr == CLEVER_DOUBLE; }
	bool isBoolean()   const { return m_type_ptr == CLEVER_BOOL; }
	bool isByte()      const { return m_type_ptr == CLEVER_BYTE; }
	bool isReference() const { return m_type == REF; }

	bool isInternal()  const { 
		if (m_type_ptr == NULL) return false;
		return m_type_ptr->getKind() == Type::INTERNAL; 
	}

	bool isNumeric() const {
		return (isInteger() || isDouble());
	}

	void setInteger(int64_t i) {
		m_type_ptr = CLEVER_INT;
		m_type = VAR;
		m_data.l_value = i;
	}

	void setString(const CString* s) {
		if (m_data.s_value && !m_data.s_value->isInterned()) {
			const_cast<CString*>(m_data.s_value)->delRef();
		}

		m_type_ptr = CLEVER_STR;
		m_type = VAR;
		m_data.s_value = s;

		if (!s->isInterned()) {
			const_cast<CString*>(s)->addRef();
		}
	}

	void setDouble(double d) {
		m_type_ptr = CLEVER_DOUBLE;
		m_type = VAR;
		m_data.d_value = d;
	}

	void setBoolean(bool b) {
		m_type_ptr = CLEVER_BOOL;
		m_type = VAR;
		m_data.b_value = b;
	}

	void setByte(uint8_t b) {
		m_type_ptr = CLEVER_BYTE;
		m_type = VAR;
		m_data.c_value = b;
	}

	void setReference(Value* v) {
		m_type_ptr = NULL;
		m_data.ref_value = v;
		m_type = REF;
	}

	const CString* getStringP() const { return m_data.s_value; }

	const CString& getString() const { return *m_data.s_value; }
	int64_t getInteger()       const { return m_data.l_value; }
	double getDouble()         const { return m_data.d_value; }
	bool getBoolean()          const { return m_data.b_value; }
	uint8_t getByte()          const { return m_data.c_value; }
	Value* getReference()	   const { return m_data.ref_value; }
	const ValueData* getData() const { return &m_data; }

	bool getValueAsBool() const;

	// Sets the buffer for a internal type structure
	void setDataValue(DataValue* data) {
		if (m_data.dv_value && data != m_data.dv_value) {
			m_data.dv_value->delRef();
		}
		m_data.dv_value = data;
		m_type = VAR;
	}

	DataValue* getDataValue() const {
		return m_data.dv_value;
	}

	void copy(const Value* const);

	void deepCopy(const Value* const);

	virtual Value* getValue() { return this; }

	bool isConst() const {
		return m_is_const;
	}

	void setConstness(bool constness) {
		m_is_const = constness;
	}

	virtual const std::string toString();
private:
	ValueType m_type;

	const Type* m_type_ptr;
	const CString* m_name;
	ValueData m_data;
	bool m_is_const;

	DISALLOW_COPY_AND_ASSIGN(Value);
};

typedef std::vector<Value*> ValueVector;

} // clever

#endif // CLEVER_VALUE_H
