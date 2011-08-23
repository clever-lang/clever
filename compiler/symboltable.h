/**
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
#include "global.h"
#include "value.h"

namespace clever {

class CString;
class Symbol;
class Scope;

typedef std::pair<const CString*, Symbol> ScopeEntry;
typedef std::deque<Scope> ScopeDeque;

class Symbol {
public:
	typedef	enum { INVALID, UNKNOWN, VALUE, TYPE } SymbolType;

	Symbol()
		: m_name(NULL), m_type(INVALID) {}

	Symbol(const CString* name, Value* value)
		: m_name(name), m_type(VALUE) {
		m_data.value = value;
	}

	Symbol(const CString* name, Type* type)
		: m_name(name), m_type(TYPE) {
		m_data.type = type;
	}

	const CString* getSymbolName() const { return m_name; }
	SymbolType     getSymbolType() const { return m_type; }

	bool isInvalid() const { return m_type == INVALID; }
	bool isUnknown() const { return m_type == UNKNOWN; }
	bool isValue()   const { return m_type == VALUE;   }
	bool isType()    const { return m_type == TYPE;    }

	// TODO: add type check
	Value* getValue()             { return m_data.value; }
	Type*  getType()              { return m_data.type;  }

private:
	const CString* m_name;
	SymbolType     m_type;

	union {
		Value *value;
		Type  *type;
	} m_data;
};

typedef std::tr1::unordered_map<const CString*, Symbol> ScopeBase;

class Scope : public ScopeBase {
public:

	Scope(int level) : m_level(level) {}
	~Scope() {
		Scope::iterator it = begin(), end_ = end();

		while(it != end_) {
			Symbol& s = it->second;

			if (s.isValue())
				s.getValue()->delRef();

			++it;
		}
	}

	int getLevel() const { return m_level; }
	
	/**
	 * Pushes a new value
	 */
	void push(const CString* name, Value* value) throw() {
		insert(ScopeEntry(name, Symbol(name, value)));
	}

	void push(Value *value) throw() {
		push(value->getName(), value);
	}

	/**
	 * Pushes a new type
	 */
	void push(const CString* name, Type* type) throw() {
		insert(ScopeEntry(name, Symbol(name, type)));
	}

	/**
	 * Attempts to find a symbol with the given name.
	 */
	Symbol getSymbol(const CString* name) throw() {
		Scope::iterator it = find(name);

		if (it == end()) {
			return Symbol(); // return an invalid symbol
		}
		
		return it->second;
	}

	/**
	 * Returns the value pointer for the given symbol name.
	 */
	Value* getValue(const CString* name) throw() {

		Symbol s = getSymbol(name);

		if (s.isInvalid())
			return NULL;

		return s.getValue();
	}

	/**
	 * Returns the type pointer for the given symbol name.
	 */
	Type* getType(const CString* name) throw() {
		
		Symbol s = getSymbol(name);

		if (s.isInvalid())
			return NULL;

		return s.getType();
	}

private:
	int m_level;
};

class SymbolTable {
public:
	SymbolTable()
		: m_level(-1) {}

	~SymbolTable() {}

	/**
	 * Pushes a new variable or constant to the current scope.
	 */
	void push(const CString* name, Value* value) throw() {
		getScope().push(name, value);
	}

	void push(Value *value) throw() {
		getScope().push(value);
	}

	/**
	 * Pushes a new type to the current scope.
	 */
	void push(const CString* name, Type* type) throw() {
		getScope().push(name, type);
	}

	/**
	 * Attempts to find a symbol with the given name in the current scope.
	 */
	Symbol getSymbol(const CString* name, bool recurse) throw() {
		Symbol s;
				
		s = getScope().getSymbol(name);

		if (s.isInvalid() && recurse) {
			int i = m_level-1;

			while (s.isInvalid() && i >= 0)
				s = getScope(i--).getSymbol(name);
		}

		return s;
	}

	Symbol getSymbol(const CString* name) throw() {
		return getSymbol(name, true);
	}

	/**
	 * Returns the value pointer for the given symbol name.
	 */
	Value* getValue(const CString* name, bool recurse) throw() {

		Symbol s = getSymbol(name, recurse);

		if (s.isInvalid())
			return NULL;

		return s.getValue();
	}

	Value* getValue(const CString* name) throw() {
		return getValue(name, true);
	}

	/**
	 * Returns the type pointer for the given symbol name.
	 */
	Type* getType(const CString* name, bool recurse) throw() {
		
		Symbol s = getSymbol(name, recurse);

		if (s.isInvalid())
			return NULL;

		return s.getType();
	}
	
	Type* getType(const CString* name) throw() {
		return getType(name, true);
	}

	/**
	 * Returns the current scope.
	 */
	Scope& getScope() throw() { 
		return getScope(m_level);
	}

	/**
	 * Returns the scope at the given level number.
	 */
	Scope& getScope(int level) throw() {
		if (level < 0) {
			// TODO: throw error.
		}

		return m_scope.at(level);
	}

	/**
	 * Enters a new scope.
	 */
	void beginScope() throw() {
		m_scope.push_back(Scope(++m_level));
	}

	/**
	 * Leaves the current scope.
	 */
	void endScope() throw() {
		m_scope.pop_back();
		m_level--;
	}

private:
		int m_level;
		ScopeDeque m_scope;

		DISALLOW_COPY_AND_ASSIGN(SymbolTable);
};

} // clever

#endif // CLEVER_SYMBOLTABLE_H
