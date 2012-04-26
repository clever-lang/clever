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

#ifndef CLEVER_SYMBOL_H
#define CLEVER_SYMBOL_H

namespace clever {

class CString;
class Type;
class Value;

class Symbol {
public:
	typedef	enum { INVALID, VALUE, TYPE } SymbolType;

	Symbol() : m_name(NULL), m_type(INVALID), m_data() {}

	Symbol(const CString* name, Value* value)
		: m_name(name), m_type(VALUE), m_data() {
		clever_assert_not_null(name);
		clever_assert_not_null(value);

		m_data.value = value;
	}

	Symbol(const CString* name, const Type* type)
		: m_name(name), m_type(TYPE), m_data() {
		clever_assert_not_null(name);
		clever_assert_not_null(type);

		m_data.type = type;
	}

	~Symbol();

	const CString* getSymbolName() const { return m_name; }
	SymbolType     getSymbolType() const { return m_type; }

	bool isInvalid() const { return m_type == INVALID; }
	bool isValue()   const { return m_type == VALUE;   }
	bool isType()    const { return m_type == TYPE;    }

	// TODO: add type check
	const Type*  getType()  { return m_data.type;  }
	Value*       getValue() { return m_data.value; }

private:
	DISALLOW_COPY_AND_ASSIGN(Symbol);

	const CString* m_name;
	SymbolType     m_type;

	union {
		Value* value;
		const Type* type;
	} m_data;
};
} // clever

#endif // CLEVER_SYMBOL_H
