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

#ifndef CLEVER_THREADS
# define SAFETY_CTOR() ,m_mutex()
# define SAFETY_DTOR()
# define SAFETY_LOCK()  m_mutex.lock();
# define SAFETY_ULOCK() m_mutex.unlock();
# define SAFETY_GET(A, B, C) return static_cast<B*>(getObj())->value;
# define SAFETY_GET_STR(A, B, C) return static_cast<B*>(getObj())->getStr();
#else
# define SAFETY_CTOR()
# define SAFETY_DTOR()
# define SAFETY_LOCK()
# define SAFETY_ULOCK()
# define SAFETY_GET(A, B, C) return static_cast<B*>(getObj())->value;
# define SAFETY_GET_STR(A, B, C) return static_cast<B*>(getObj())->getStr();
#endif

typedef std::map     <std::string, Value*>  ValueMap;
typedef std::pair    <std::string, Value*>  ValuePair;
typedef std::vector  <Value*>               ValueVector;

class ValueObject : public RefCounted {
public:
	ValueObject()
		: RefCounted(1), m_obj(NULL), m_type(NULL) {}

	ValueObject(TypeObject* obj, const Type* type)
		: RefCounted(1), m_obj(obj), m_type(type) {}

	virtual ~ValueObject() {
		if (m_type) {
			const_cast<Type*>(m_type)->deallocData(m_obj);
		}
	}

	TypeObject* getObj() const { return m_obj; }

private:
	TypeObject* m_obj;
	const Type* m_type;

	DISALLOW_COPY_AND_ASSIGN(ValueObject);
};

class Value : public RefCounted {
public:
	Value()
		: m_data(NULL), m_type(NULL), m_is_const(false)
		SAFETY_CTOR()
		{}

	Value(bool n, bool is_const = false)
		: m_data(NULL), m_type(CLEVER_BOOL_TYPE), m_is_const(is_const)
		SAFETY_CTOR()
	{
		setBool(n);
	}

	Value(long n, bool is_const = false)
		: m_data(NULL), m_type(CLEVER_INT_TYPE), m_is_const(is_const)
		SAFETY_CTOR()
	{

		setInt(n);
	}

	Value(double n, bool is_const = false)
		: m_data(NULL), m_type(CLEVER_DOUBLE_TYPE), m_is_const(is_const)
		SAFETY_CTOR()
	{
		setDouble(n);
	}

	Value(const CString* value, bool is_const = false)
		: m_data(NULL), m_type(CLEVER_STR_TYPE), m_is_const(is_const)
		SAFETY_CTOR()
	{
		setObj(m_type, new StrObject(value));
	}

	Value(const Type* type, bool is_const = false)
		: m_data(), m_type(type), m_is_const(is_const)
		SAFETY_CTOR()
	{
	}

	~Value() {
		if (m_type && m_data) {
			m_data->delRef();
		}
		SAFETY_DTOR();
	}

	const Type* getType() const { return m_type; }

	void setNull() { SAFETY_LOCK(); m_type = NULL; SAFETY_ULOCK(); }
	bool isNull() const { return m_type == NULL; }

	void dump() const {	dump(std::cout); }
	void dump(std::ostream& out) const {
		if (m_type) {
			m_type->dump(getObj(), out);
		} else {
			out << "null";
		}
	}

	void setObj(const Type* type, TypeObject* ptr) {
		SAFETY_LOCK();
		clever_assert_not_null(type);
		clever_assert_not_null(ptr);
		m_type = type;
		m_data = new ValueObject(ptr, type);
		ptr->copyMembers(type);
		SAFETY_ULOCK();
	}

	TypeObject* getObj() const { return  m_data->getObj(); }

	void setInt(long);
	long getInt() const;

	void setBool(bool);
	bool getBool() const;

	void setDouble(double);
	double getDouble() const;

	void setStr(const CString*);
	void setStr(StrObject*);
	const CString* getStr() const;

	bool isInt()      const { return m_type == CLEVER_INT_TYPE;    }
	bool isBool()     const { return m_type == CLEVER_BOOL_TYPE;   }
	bool isDouble()   const { return m_type == CLEVER_DOUBLE_TYPE; }
	bool isStr()      const { return m_type == CLEVER_STR_TYPE;    }
	bool isFunction() const { return m_type == CLEVER_FUNC_TYPE;   }
	bool isMap()      const { return m_type == CLEVER_MAP_TYPE;    }
	bool isArray()    const { return m_type == CLEVER_ARRAY_TYPE;  }
	bool isThread()   const { return m_type == CLEVER_THREAD_TYPE; }

	ValueObject* getData() const { return m_data; }

	void copy(const Value*);

	Value* clone() {
		SAFETY_LOCK();
		Value* val = new Value;
		val->copy(this);
		val->setConst(isConst());
		SAFETY_ULOCK();
		return val;
	}

	bool asBool() const;

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
		SAFETY_LOCK();
		if (m_type && m_data) {
			m_data->delRef();
		}
		SAFETY_ULOCK();
	}

	ValueObject* m_data;
	const Type* m_type;
	bool m_is_const;
#ifdef CLEVER_THREADS
	CMutex m_mutex;
#endif
	DISALLOW_COPY_AND_ASSIGN(Value);
};

} // clever

#endif // CLEVER_VALUE_H
