/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_VALUE_H
#define CLEVER_VALUE_H

#include <cstring>

#include "core/cstring.h"
#include "types/type.h"

namespace clever {

extern Type* g_clever_int_type;
extern Type* g_clever_double_type;
extern Type* g_clever_str_type;
extern Type* g_clever_func_type;
extern Type* g_clever_thread_type;
extern Type* g_clever_bool_type;

#define DECLARE_CLEVER_NATIVE_TYPES() \
	Type* g_clever_int_type;          \
	Type* g_clever_double_type;       \
	Type* g_clever_str_type;          \
	Type* g_clever_func_type;         \
	Type* g_clever_thread_type;       \
	Type* g_clever_bool_type;

#define CLEVER_INT_TYPE    g_clever_int_type
#define CLEVER_DOUBLE_TYPE g_clever_double_type
#define CLEVER_STR_TYPE    g_clever_str_type
#define CLEVER_FUNC_TYPE   g_clever_func_type
#define CLEVER_THREAD_TYPE g_clever_thread_type
#define CLEVER_BOOL_TYPE   g_clever_bool_type

class ValueObject : public RefCounted {
public:
	ValueObject()
		: RefCounted(1), m_obj(NULL), m_type(NULL) {}

	ValueObject(void* obj, const Type* type)
		: RefCounted(1), m_obj(obj), m_type(type) {}

	virtual ~ValueObject() {
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
	union DataValue {
		bool bval;
		long lval;
		double dval;
		const CString* sval;
		ValueObject* obj;

		DataValue() : lval(0) {}
		DataValue(bool value) : bval(value) {}
		DataValue(long value) : lval(value) {}
		DataValue(double value) : dval(value) {}
		DataValue(const CString* value) : sval(value) {}
	};

	Value() : m_data(), m_type(NULL), m_is_const(false) {}

	Value(bool n)
		: m_data(n), m_type(CLEVER_BOOL_TYPE), m_is_const(false) {}

	Value(long n)
		: m_data(n), m_type(CLEVER_INT_TYPE), m_is_const(false) {}

	Value(double n)
		: m_data(n), m_type(CLEVER_DOUBLE_TYPE), m_is_const(false) {}

	Value(const CString* value)
		: m_data(value), m_type(CLEVER_STR_TYPE), m_is_const(false) {}

	Value(const Type* type)
		: m_data(), m_type(type), m_is_const(false) {}

	~Value() {
		if (m_type && !m_type->isPrimitive()) {
			if (m_data.obj) {
				m_data.obj->delRef();
			}
		}
	}

	void setType(const Type* type) { m_type = type; }
	const Type* getType() const { return m_type; }

	void setNull() { m_type = NULL; }
	bool isNull() const { return m_type == NULL; }

	void dump() const {
		dump(std::cout);
	}

	void dump(std::ostream& out) const {
		if (m_type) {
			m_type->dump(&m_data, out);
		} else {
			out << "null";
		}
	}
	void setObj(void* ptr) {
		clever_assert_not_null(m_type);
		m_data.obj = new ValueObject(ptr, m_type);
	}
	void* getObj() const { return m_data.obj->getObj(); }

	void setInt(long n) { m_data.lval = n; m_type = CLEVER_INT_TYPE; }
	long getInt() const { return m_data.lval; }

	void setBool(bool n) { m_data.bval = n; m_type = CLEVER_BOOL_TYPE; }
	bool getBool() const { return m_data.bval; }

	void setDouble(double n) { m_data.dval = n; m_type = CLEVER_DOUBLE_TYPE; }
	double getDouble() const { return m_data.dval; }

	const DataValue* getData() const { return &m_data; }

	void setStr(const CString* str) { m_data.sval = str; m_type = CLEVER_STR_TYPE; }
	const CString* getStr() const { return m_data.sval; }

	void copy(const Value* value) {
		m_type = value->getType();
		memcpy(&m_data, value->getData(), sizeof(DataValue));

		if (m_type && !m_type->isPrimitive()) {
			if (m_data.obj) {
				m_data.obj->addRef();
			}
		}
	}

	bool asBool() const {
		if (isNull()) {
			return false;
		} else if (m_type->isPrimitive()) {
			if (m_type == CLEVER_INT_TYPE) {
				return m_data.lval != 0;
			} else if (m_type == CLEVER_DOUBLE_TYPE) {
				return m_data.dval != 0;
			} else if (m_type == CLEVER_STR_TYPE) {
				return m_data.sval != NULL;
			} else if (m_type == CLEVER_BOOL_TYPE) {
				return m_data.bval;
			}
		}
		return true;
	}

	// @TODO(muriloadriano): This is a workout to allow the assign on a const
	// variable declaration. If the current data is null and it is const, the
	// assign must be performed (first assign), if it is not null and const,
	// we cannot assign because it is trying to change its value. If it this
	// value isn't const it is assignable too. Maybe this could be done in a
	// clever way.
	bool isAssignable() const {
		return isNull() || !isConst();
	}

	bool isConst() const {
		return m_is_const;
	}

	void setConst(bool constness = true) {
		m_is_const = constness;
	}
private:
	DataValue m_data;
	const Type* m_type;
	bool m_is_const;
};

} // clever

#endif // CLEVER_VALUE_H
