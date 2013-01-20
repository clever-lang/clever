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
#include "modules/std/core/str.h"

namespace clever {

extern Type* g_clever_int_type;
extern Type* g_clever_double_type;
extern Type* g_clever_str_type;
extern Type* g_clever_func_type;
extern Type* g_clever_thread_type;
extern Type* g_clever_bool_type;
extern Type* g_clever_array_type;
extern Type* g_clever_map_type;

#define CLEVER_INT_TYPE    g_clever_int_type
#define CLEVER_DOUBLE_TYPE g_clever_double_type
#define CLEVER_STR_TYPE    g_clever_str_type
#define CLEVER_FUNC_TYPE   g_clever_func_type
#define CLEVER_THREAD_TYPE g_clever_thread_type
#define CLEVER_BOOL_TYPE   g_clever_bool_type
#define CLEVER_ARRAY_TYPE  g_clever_array_type
#define CLEVER_MAP_TYPE    g_clever_map_type

#ifdef MOD_STD_CONCURRENT
# define SAFETY_CTOR() pthread_mutex_init(&m_mutex, NULL)
# define SAFETY_DTOR() pthread_mutex_destroy(&m_mutex)
# define SAFETY_LOCK() pthread_mutex_lock(&m_mutex)
# define SAFETY_ULOCK() pthread_mutex_unlock(&m_mutex)
#else
# define SAFETY_CTOR()
# define SAFETY_DTOR()
# define SAFETY_LOCK()
# define SAFETY_ULOCK()
#endif

typedef std::map     <std::string, Value*>  ValueMap;
typedef std::pair    <std::string, Value*>  ValuePair;
typedef std::vector  <Value*>               ValueVector;

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

	DISALLOW_COPY_AND_ASSIGN(ValueObject);
};

class Value : public RefCounted {
public:
	union DataValue {
		bool bval;
		long lval;
		double dval;
		ValueObject* obj;

		DataValue() : lval(0) {}
		DataValue(bool value) : bval(value) {}
		DataValue(long value) : lval(value) {}
		DataValue(double value) : dval(value) {}
	};

	Value() : m_data(), m_type(NULL), m_is_const(false) {SAFETY_CTOR();}

	Value(bool n, bool is_const = false)
		: m_data(n), m_type(CLEVER_BOOL_TYPE), m_is_const(is_const) {SAFETY_CTOR();}

	Value(long n, bool is_const = false)
		: m_data(n), m_type(CLEVER_INT_TYPE), m_is_const(is_const) {SAFETY_CTOR();}

	Value(double n, bool is_const = false)
		: m_data(n), m_type(CLEVER_DOUBLE_TYPE), m_is_const(is_const) {SAFETY_CTOR();}

	Value(const CString* value, bool is_const = false)
		: m_data(value), m_type(CLEVER_STR_TYPE), m_is_const(is_const) {
		SAFETY_CTOR();
		setObj(m_type, new StrObject(value));
	}

	Value(const Type* type, bool is_const = false)
		: m_data(), m_type(type), m_is_const(is_const) {SAFETY_CTOR();}

	~Value() {
		if (m_type && !m_type->isPrimitive()) {
			if (m_data.obj) {
				m_data.obj->delRef();
			}
		}
		SAFETY_DTOR();
	}

	const Type* getType() const { return m_type; }

	void setNull() { SAFETY_LOCK(); m_type = NULL; SAFETY_ULOCK(); }
	bool isNull() const { return m_type == NULL; }

	void dump() const {	dump(std::cout); }
	void dump(std::ostream& out) const {
		if (m_type) {
			if (m_type->isPrimitive()) {
				m_type->dump(&m_data, out);
			} else {
				m_type->dump(m_data.obj, out);
			}
		} else {
			out << "null";
		}
	}

	void setObj(const Type* type, void* ptr) {
		SAFETY_LOCK();
		clever_assert_not_null(type);
		m_type = type;
		m_data.obj = new ValueObject(ptr, type);
		SAFETY_ULOCK();
	}
	void* getObj() const { return m_data.obj->getObj(); }

	void setInt(long n) {
		SAFETY_LOCK();
		m_data.lval = n;
		m_type = CLEVER_INT_TYPE;
		SAFETY_ULOCK();
	}
	long getInt() const { return m_data.lval; }

	void setBool(bool n) {
		SAFETY_LOCK();
		m_data.bval = n;
		m_type = CLEVER_BOOL_TYPE;
		SAFETY_ULOCK();
	}
	bool getBool() const { return m_data.bval; }

	void setDouble(double n) {
		SAFETY_LOCK();
		m_data.dval = n;
		m_type = CLEVER_DOUBLE_TYPE;
		SAFETY_ULOCK();
	}
	double getDouble() const { return m_data.dval; }

	void setStr(const CString* str) {
		SAFETY_LOCK();
		cleanUp();
		m_type = CLEVER_STR_TYPE;
		setObj(m_type, new StrObject(str));
		SAFETY_ULOCK();
	}
	void setStr(StrObject* str) {
		SAFETY_LOCK();
		cleanUp();
		m_type = CLEVER_STR_TYPE;
		setObj(m_type, str);
		SAFETY_ULOCK();
	}
	const CString* getStr() const { return static_cast<StrObject*>(getObj())->getStr(); }


	bool isInt()      const { return m_type == CLEVER_INT_TYPE;    }
	bool isBool()     const { return m_type == CLEVER_BOOL_TYPE;   }
	bool isDouble()   const { return m_type == CLEVER_DOUBLE_TYPE; }
	bool isStr()      const { return m_type == CLEVER_STR_TYPE;    }
	bool isFunction() const { return m_type == CLEVER_FUNC_TYPE;   }
	bool isMap()      const { return m_type == CLEVER_MAP_TYPE;    }
	bool isArray()    const { return m_type == CLEVER_ARRAY_TYPE;  }
	bool isThread()   const { return m_type == CLEVER_THREAD_TYPE; }

	const DataValue* getData() const { return &m_data; }

	void copy(const Value* value) {
		SAFETY_LOCK();
		cleanUp();
		m_type = value->getType();
		memcpy(&m_data, value->getData(), sizeof(DataValue));

		if (m_type && !m_type->isPrimitive()) {
			if (m_data.obj) {
				m_data.obj->addRef();
			}
		}
		SAFETY_ULOCK();
	}

	Value* clone() const {
		Value* val = new Value;
		val->copy(this);
		return val;
	}

	bool asBool() const {
		if (isNull()) {
			return false;
		} else if (m_type == CLEVER_BOOL_TYPE) {
			return m_data.bval;
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
	void cleanUp() {
		if (m_type && !m_type->isPrimitive()) {
			m_data.obj->delRef();
		}
	}

	DataValue m_data;
	const Type* m_type;
	bool m_is_const;
#ifdef MOD_STD_CONCURRENT
	pthread_mutex_t m_mutex;
#endif
	DISALLOW_COPY_AND_ASSIGN(Value);
};

} // clever

#endif // CLEVER_VALUE_H
