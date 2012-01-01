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

#ifndef CLEVER_SYMBOLTABLE_H
#define CLEVER_SYMBOLTABLE_H

#include <tr1/unordered_map>
#include <deque>
#include "compiler/clever.h"
#include "compiler/cstring.h"
#include "compiler/refcounted.h"

#define CLEVER_TYPE(name)  ::clever::g_symtable.getType(CSTRING(name))
#define CLEVER_VALUE(name) ::clever::g_symtable.getValue(CSTRING(name))

namespace clever {

class Type;
class Value;

class Scope;
class Symbol;
class SymbolTable;

extern SymbolTable g_symtable;

class Symbol {
public:
	typedef	enum { INVALID, VALUE, TYPE } SymbolType;

	Symbol()
		: m_name(NULL), m_type(INVALID) {
	}

	Symbol(const CString* name, Value* value)
		: m_name(name), m_type(VALUE) {
		clever_assert(name != NULL,  "No name provided.");
		clever_assert(value != NULL, "No value provided.");

		m_data.value = value;
	}

	Symbol(const CString* name, const Type* type)
		: m_name(name), m_type(TYPE) {
		clever_assert(name != NULL, "No name provided.");
		clever_assert(type != NULL, "No type provided.");

		m_data.type = type;
	}
	
	~Symbol() { }

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

/*
 * TODO: XXX: FIXME: Developer note:
 *
 * I believe this class can/should, somehow, be merged with or replace 
 * SymbolTable provided the funcionality (scoping depth manipulation) of the 
 * latter one is kept intact or improved.
 * 
 * One thing we must pay attention to is that merging the two classes will 
 * require a change of the way we push new entries into the scope. Perhaps 
 * we should keep an alias to std::deque<const CString*, Scope*> named 
 * SymbolTable or build a tree/list like structure with pointers to the next 
 * and the previous scopes using the Scope class.
 *
 * -- Higor.
 * 
 */
class Scope : public RefCounted {
	typedef std::tr1::unordered_map<const CString*, Symbol*> SymbolMap;
	typedef std::pair<const CString*, Symbol*> ScopeEntry;

public:

	Scope(int depth, Scope* parent = NULL) : RefCounted(), m_syms(), m_parent(parent), m_depth(depth) {
		if (depth > 0) {
			clever_assert(parent != NULL, "No parent provided to non-root scope.");
		}
	}
	~Scope();

	int getDepth() const { return m_depth; }
	
	/**
	 * Binds a Value* to an interned string.
	 */
	void bind(const CString* name, Value* value) throw() {
		clever_assert(name != NULL,  "No name provided.");
		clever_assert(value != NULL, "No value provided.");

		m_syms.insert(ScopeEntry(name, new Symbol(name, value)));
	}

	/**
	 * Binds a Type* to an interned string.
	 */
	void bind(const CString* name, const Type* type) throw() {
		clever_assert(name != NULL, "No name provided.");
		clever_assert(type != NULL, "No type provided.");

		m_syms.insert(ScopeEntry(name, new Symbol(name, type)));
	}

	/**
	 * Attempts to resolve a symbol name.
	 *
	 * Please use an error message like "unresolved symbol" or something 
	 * if the symbol is really needed.
	 */
	Symbol* resolve(const CString* name, bool recurse = true) throw() {
		SymbolMap::iterator it = m_syms.find(name);

		if (it != m_syms.end()) {
			return it->second;
		}

		if (!recurse || m_parent == NULL) {
			return NULL;
		}

		return m_parent->resolve(name, true);
	}

	/**
	 * Returns a Value* for the given symbol name.
	 *
	 * See resolve() for more information.
	 */
	Value* resolveValue(const CString* name, bool recurse = true) throw() {

		Symbol* s = resolve(name, recurse);

		if (s == NULL || !s->isValue())
			return NULL;

		return s->getValue();
	}

	/**
	 * Returns a Type* for the given symbol name.
	 *
	 * See resolve() for more information.
	 */
	const Type* resolveType(const CString* name, bool recurse = true) throw() {
		
		Symbol* s = resolve(name, recurse);

		if (s == NULL || !s->isType())
			return NULL;

		return s->getType();
	}

private:
	SymbolMap m_syms;
	Scope* m_parent;
	int    m_depth;
};

class SymbolTable {
	typedef std::deque<Scope*> ScopeDeque;
public:
	SymbolTable()
		: m_level(-1) {}

	~SymbolTable() {
		//clever_assert(m_level < 0, "%i scopes were not properly cleaned.", m_level);
	}

	/**
	 * Pushes a new variable or constant to the current scope.
	 */
	void push(const CString* name, Value* value) throw() {
		getScope()->bind(name, value);
	}

	/**
	 * Pushes a new type to the current scope.
	 */
	void push(const CString* name, const Type* type) throw() {
		getScope()->bind(name, type);
	}

	/**
	 * Attempts to find a symbol with the given name in the current scope.
	 */
	Symbol* getSymbol(const CString* name, bool recurse = true) throw() {
		return getScope()->resolve(name, recurse);
	}

	/**
	 * Returns the value pointer for the given symbol name.
	 */
	Value* getValue(const CString* name, bool recurse = true) throw() {
		return getScope()->resolveValue(name, recurse);
	}

	/**
	 * Returns the type pointer for the given symbol name.
	 */
	const Type* getType(const CString* name, bool recurse = true) throw() {
		return getScope()->resolveType(name, recurse);
	}

	/**
	 * Returns the current scope.
	 */
	Scope* getScope() throw() { 
		return getScope(m_level);
	}

	/**
	 * Returns the scope at the given level number.
	 */
	Scope* getScope(int level) throw() {
		clever_assert(level >= 0, "No scope available.");

		return m_scope.at(level);
	}

	/**
	 * Enters a new scope.
	 */
	Scope* beginScope() throw() {
		Scope* parent = m_level < 0 ? NULL : getScope();
		Scope* s = new Scope(++m_level, parent);

		m_scope.push_back(s);

		return s;
	}

	/**
	 * Leaves the current scope.
	 */
	Scope* endScope() throw() {
		Scope* s = m_scope.back();
		m_scope.pop_back();
		m_level--;
		
		s->delRef();
		return s;
	}

private:
	int m_level;
	ScopeDeque m_scope;

	DISALLOW_COPY_AND_ASSIGN(SymbolTable);
};

} // clever

#endif // CLEVER_SYMBOLTABLE_H
