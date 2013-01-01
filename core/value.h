/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_VALUE_H
#define CLEVER_VALUE_H

#include <cstring>
#include "core/clever.h"
#include "core/refcounted.h"
#include "types/type.h"
#include "core/cstring.h"

namespace clever {

extern Type* g_clever_int_type;
extern Type* g_clever_double_type;
extern Type* g_clever_str_type;
extern Type* g_clever_func_type;

#define DECLARE_CLEVER_NATIVE_TYPES() \
	Type* g_clever_int_type;          \
	Type* g_clever_double_type;       \
	Type* g_clever_str_type;          \
	Type* g_clever_func_type;

#define CLEVER_INT_TYPE    g_clever_int_type
#define CLEVER_DOUBLE_TYPE g_clever_double_type
#define CLEVER_STR_TYPE g_clever_str_type
#define CLEVER_FUNC_TYPE   g_clever_func_type

class ValueObject : public RefCounted {
public:
	ValueObject() :
		RefCounted(1), m_obj(NULL), m_type(NULL) {}

	ValueObject(void* obj, const Type* type)
		: RefCounted(1), m_obj(obj), m_type(type) {}

	~ValueObject() {
		if (m_type) {
			const_cast<Type*>(m_type)->deallocData(m_obj);
		}
	}

	void* getObj() { return m_obj; }
private:
	void* m_obj;
	const Type* m_type;
};

class Value : public RefCounted {
public:
	enum ValueKind {
		PRIMITIVE,
		OBJECT
	};
	union DataValue {
		long lval;
		double dval;
		const CString* sval;
		ValueObject* obj;

		DataValue() : lval(0) {}
		DataValue(long value) : lval(value) {}
		DataValue(double value) : dval(value) {}
		DataValue(const CString* value) : sval(value) {}
	};

	Value() : m_data(), m_kind(PRIMITIVE), m_type(NULL) {}
	Value(long n) : m_data(n), m_kind(PRIMITIVE), m_type(CLEVER_INT_TYPE) {}
	Value(double n) : m_data(n), m_kind(PRIMITIVE), m_type(CLEVER_DOUBLE_TYPE) {}
	Value(const CString* value) : m_data(value), m_kind(PRIMITIVE), m_type(CLEVER_STR_TYPE) {}

	~Value() {
		if (m_type && !isPrimitive()) {
			m_data.obj->delRef();
		}
	}

	bool isPrimitive() const { return m_kind == PRIMITIVE; }

	void setKind(ValueKind kind) { m_kind = kind; }
	ValueKind getKind() const { return m_kind; }

	void setType(const Type* type) { m_type = type; }
	const Type* getType() const { return m_type; }

	void setNull() { m_type = NULL; }
	bool isNull() const { return m_type == NULL; }

	void dump() const {
		if (m_type) {
			m_type->dump(&m_data);
		} else {
			std::cout << "null";
		}
	}

	void setObj(void* ptr) {
		clever_assert_not_null(m_type);
		m_kind = OBJECT;
		m_data.obj = new ValueObject(ptr, m_type);
	}
	void* getObj() const { return m_data.obj->getObj(); }

	void setInt(long n) { m_data.lval = n; m_type = CLEVER_INT_TYPE; }
	long getInt() const { return m_data.lval; }

	void setDouble(double n) { m_data.dval = n; m_type = CLEVER_DOUBLE_TYPE; }
	double getDouble() const { return m_data.dval; }

	const DataValue* getData() const { return &m_data; }

	const CString* getStr() const { return m_data.sval; }

	void copy(Value* value) {
		m_kind = value->getKind();
		m_type = value->getType();
		memcpy(&m_data, value->getData(), sizeof(DataValue));

		if (!value->isPrimitive()) {
			if (m_data.obj) {
				static_cast<ValueObject*>(m_data.obj)->addRef();
			}
		}
	}

	bool asBool() const {
		if (isNull()) {
			return false;
		} else if (m_kind == PRIMITIVE) {
			if (m_type == CLEVER_INT_TYPE) {
				return m_data.lval != 0;
			} else if (m_type == CLEVER_DOUBLE_TYPE) {
				return m_data.dval != 0;
			} else if (m_type == CLEVER_STR_TYPE) {
				return m_data.sval != NULL;
			}
		}
		return true;
	}
private:
	DataValue m_data;
	ValueKind m_kind;
	const Type* m_type;
};

} // clever

#endif // CLEVER_VALUE_H
