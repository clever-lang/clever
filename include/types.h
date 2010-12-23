/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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

#ifndef CLEVER_TYPES_H
#define CLEVER_TYPES_H

#include <iostream>
#include <sstream>
#include <string>
#include "config.h"
#include "refcounted.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

namespace clever {

class Value : public RefCounted {
public:
	Value() : m_value_type(NO_VALUE), RefCounted(1) { }

	explicit Value(int type) : m_value_type(type), RefCounted(1) { }

	virtual ~Value() { }

	virtual void set_value(Value* value) { }

	int get_value_type(void) {
		return m_value_type;
	}

	virtual Value* get_value(void) {
		return this;
	}

	virtual std::string toString(void) {
		return std::string();
	}

	enum { NO_VALUE, NAMED_VALUE, CONST_VALUE, TEMP_VALUE };

	int m_value_type;
};

class NamedValue : public Value {
	std::string name;
};

/*
 * Constant values used for opcodes
 */
class ConstantValue : public Value {
public:
	explicit ConstantValue(double l_value)
		: Value(CONST_VALUE) {
		m_type = INTEGER;
		m_data.l_value = l_value;
	}

	explicit ConstantValue(std::string s_value)
		: Value(CONST_VALUE) {
		m_type = STRING;
		m_data.s_value = new std::string(s_value);
	}

	inline int get_type() const {
		return m_type;
	}

	inline double get_int(void) const {
		return m_data.l_value;
	}

	inline std::string get_string(void) const {
		return *m_data.s_value;
	}

	std::string toString(void) {
		if (m_type == INTEGER) {
			std::stringstream str;

			str << m_data.l_value;

			return str.str();
		} else {
			return *m_data.s_value;
		}
	}
	enum { INTEGER,	STRING };
private:
	int m_type;
	union {
		double l_value;
		std::string* s_value;
	} m_data;
};

/*
 * Temporary storage used for opcodes to storage results
 */
class TempValue : public Value {
public:
	TempValue() : Value(TEMP_VALUE), m_value(NULL) { }

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

class Type {
public:
	enum {
		ABSTRACT  = 0,
		CONCRETE  = 1,
		INTERFACE = 2,
		BUILT_IN  = 4
	};

	Type(const std::string& name, int kind)
		: m_name(name), m_kind(kind) {};
	Type(const std::string& package, const std::string& name, int kind)
		: m_package(name), m_name(name), m_kind(kind) {};

	virtual ~Type();

	virtual void Init();

	inline std::string package() const { return m_package; };
	inline std::string name() const { return m_name; };
	inline bool is_interface() const { return m_kind & INTERFACE; };
	inline bool is_abstract() const { return m_kind & ABSTRACT; };
	inline bool is_concrete() const { return m_kind & ABSTRACT; };
	inline bool is_built_in() const { return m_kind & BUILT_IN; };

private:
	Type() {};
	DISALLOW_COPY_AND_ASSIGN(Type);

	std::string m_package;
	std::string m_name;
	int m_kind;
};

} // Clever

#endif // CLEVER_TYPES_H
