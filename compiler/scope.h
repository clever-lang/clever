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

#ifndef CLEVER_SYMBOLTABLE_H
#define CLEVER_SYMBOLTABLE_H

#include <tr1/unordered_map>
#include <vector>
#include "compiler/clever.h"
#include "compiler/cstring.h"
#include "compiler/refcounted.h"

#define CLEVER_TYPE(name)  ::clever::g_scope.getType(CSTRING(name))
#define CLEVER_VALUE(name) ::clever::g_scope.getValue(CSTRING(name))

namespace clever {

class Type;
class Value;

class Scope;
class Symbol;

extern Scope g_scope;

class Symbol {
public:
	typedef	enum { INVALID, VALUE, TYPE } SymbolType;

	Symbol()
		: m_name(NULL), m_type(INVALID), m_data() {
	}

	Symbol(const CString* name, Value* value)
		: m_name(name), m_type(VALUE), m_data() {
		clever_assert(name != NULL,  "No name provided.");
		clever_assert(value != NULL, "No value provided.");

		m_data.value = value;
	}

	Symbol(const CString* name, const Type* type)
		: m_name(name), m_type(TYPE), m_data() {
		clever_assert(name != NULL, "No name provided.");
		clever_assert(type != NULL, "No type provided.");

		m_data.type = type;
	}

	~Symbol() { }

	Symbol(const Symbol& rhs)
		: m_name(rhs.m_name), m_type(rhs.m_type), m_data(rhs.m_data) {}

	Symbol& operator=(const Symbol& rhs) {
		m_name = rhs.m_name;
		m_type = rhs.m_type;
		m_data = rhs.m_data;

		return *this;
	}

	const CString* getSymbolName() const { return m_name; }
	SymbolType     getSymbolType() const { return m_type; }

	bool isInvalid() const { return m_type == INVALID; }
	bool isValue()   const { return m_type == VALUE;   }
	bool isType()    const { return m_type == TYPE;    }

	// TODO: add type check
	const Type*  getType()  { return m_data.type;  }
	Value*       getValue() { return m_data.value; }

private:
	const CString* m_name;
	SymbolType     m_type;

	union {
		Value* value;
		const Type* type;
	} m_data;
};

class Scope : public RefCounted {
	typedef std::tr1::unordered_map<const CString*, Symbol*> SymbolMap;
	typedef SymbolMap::value_type ScopeEntry;
public:

	// Constructor for non-global scopes
	explicit Scope(Scope* parent)
		: RefCounted(), m_parent(parent), m_children(), m_symbols() {
		clever_assert_not_null(parent);
	}
	
	// Global scope constructor
	Scope() : RefCounted(), m_parent(NULL), m_children(), m_symbols() {}

	~Scope();

	// Binds a Value* to an interned string.
	void pushValue(const CString* name, Value* value) {
		clever_assert_not_null(name);
		clever_assert_not_null(value);

		m_symbols.insert(ScopeEntry(name, new Symbol(name, value)));
	}

	// Binds a Type* to an interned string.
	void pushType(const CString* name, const Type* type) {
		clever_assert_not_null(name);
		clever_assert_not_null(type);

		m_symbols.insert(ScopeEntry(name, new Symbol(name, type)));
	}

	// Resolve a symbol name locally
	Symbol* getLocalSym(const CString* name) {
		SymbolMap::iterator it = m_symbols.find(name);

		if (it == m_symbols.end()) {
			return NULL;
		}
		return it->second;
	}
	
	// Resolve a symbol name recursively
	Symbol* getSym(const CString* name) {
		Symbol* sym = getLocalSym(name);

		if (sym != NULL) {
			return sym;
		}

		if (m_parent != NULL) {
			sym = m_parent->getSym(name);
		}

		return sym;
	}
	
	// Resolve a value-symbol name locally
	Value* getLocalValue(const CString* name) {
		Symbol* s = getLocalSym(name);

		if (s == NULL || !s->isValue())
			return NULL;

		return s->getValue();

	}

	// Resolve a value-symbol name recursively
	Value* getValue(const CString* name) {
		Symbol* s = getSym(name);

		if (s == NULL || !s->isValue())
			return NULL;

		return s->getValue();
	}

	// Resolve a type-symbol name recursively
	const Type* getType(const CString* name) {
		Symbol* s = getSym(name);

		if (s == NULL || !s->isType())
			return NULL;

		return s->getType();
	}

	Scope* newChild() {
		Scope* s = new Scope(this);
		m_children.push_back(s);	
		return s;
	}

	Scope* getParent() const { return m_parent; }
	std::vector<Scope*>& getChildren() { return m_children; }

	bool isGlobal() const { return m_parent == NULL; }

private:
	DISALLOW_COPY_AND_ASSIGN(Scope);

	Scope* m_parent;
	std::vector<Scope*> m_children;
	SymbolMap m_symbols;
};


} // clever

#endif // CLEVER_SYMBOLTABLE_H
