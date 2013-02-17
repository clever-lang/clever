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

typedef std::map     <std::string, Value*>  ValueMap;
typedef std::pair    <std::string, Value*>  ValuePair;
typedef std::vector  <Value*>               ValueVector;

/*
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
	const Type* getType() const { return m_type; }

private:
	TypeObject* m_obj;
	const Type* m_type;

	DISALLOW_COPY_AND_ASSIGN(ValueObject);
};
*/

class Value : public RefCounted {
public:
	Value()
		: m_type(NULL), m_data(NULL), m_is_const(false) {}

	explicit Value(bool n, bool is_const = false)
		: m_type(CLEVER_BOOL_TYPE), m_data(NULL), m_is_const(is_const) {
		setBool(n);
	}

	explicit Value(long n, bool is_const = false)
		: m_type(CLEVER_INT_TYPE), m_data(NULL), m_is_const(is_const) {
		setInt(n);
	}

	explicit Value(double n, bool is_const = false)
		: m_type(CLEVER_DOUBLE_TYPE), m_data(NULL), m_is_const(is_const) {
		setDouble(n);
	}

	explicit Value(const CString* value, bool is_const = false)
		: m_type(CLEVER_STR_TYPE), m_data(NULL), m_is_const(is_const) {
		setObj(m_type, new StrObject(value));
	}

	explicit Value(const Type* type, bool is_const = false)
		: m_type(type), m_data(NULL), m_is_const(is_const) {}

	~Value() {
		clever_delref(m_data);
	}

	const Type* getType() const { return m_type; }

	void setNull() { m_type = NULL; }
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
		clever_assert_not_null(type);
		clever_assert_not_null(ptr);

		m_type = type;
		m_data = ptr;
		ptr->copyMembers(type);
	}
	TypeObject* getObj() const { return  m_data; }

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

	TypeObject* getData() const { return m_data; }

	void deepCopy(const Value*);

	void copy(const Value* value) {
		cleanUp();
		m_type = value->getType();
		m_data = value->getData();

		if (EXPECTED(m_type && m_data)) {
			clever_addref(m_data);
		}
	}

	Value* clone() const {
		Value* val = new Value;

		val->copy(this);
		val->setConst(isConst());
		return val;
	}

	bool asBool() const { return isBool() ? getBool() : (isNull() ? false : true); }

	// @TODO(muriloadriano): This is a workout to allow the assign on a const
	// variable declaration. If the current data is null and it is const, the
	// assign must be performed (first assign), if it is not null and const,
	// we cannot assign because it is trying to change its value. If it this
	// value isn't const it is assignable too. Maybe this could be done in a
	// clever way.
	bool isAssignable() const {	return isNull() || !isConst(); }

	bool isConst() const { return m_is_const; }

	void setConst(bool constness = true) { m_is_const = constness; }

private:
	void cleanUp() const { clever_delref(m_data); }

	const Type* m_type;
	TypeObject* m_data;
	bool m_is_const;

	DISALLOW_COPY_AND_ASSIGN(Value);
};

} // clever

#endif // CLEVER_VALUE_H
