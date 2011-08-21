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

/**
 * Hashmap representing values in a scope
 */
typedef std::tr1::unordered_map<const CString*, Value*> ScopeBase;

class Scope : public ScopeBase {
public:
	explicit Scope(int number)
		: m_number(number) { }

	~Scope() {
		ScopeBase::const_iterator it = begin(), end_ = end();

		while (it != end_) {
			it->second->delRef();
			++it;
		}
	}
	
	/**
	 * Returns the number identifying the scope
	 */
	int getNumber() const throw() { return m_number; }

	/**
	 * Pushes a new named Value pointer to the scope
	 */
	void push(const CString* name, Value* value) {
		if (EXPECTED(value->hasName())) {
			insert(std::pair<const CString*, Value*>(name, value));
		}

		// TODO: THROW ERROR HERE
	}

	/**
	 * Pushes a new Value pointer to the scope
	 */
	void push(Value* value) {
		if (EXPECTED(value->hasName())) {
			push(value->getName(), value);
		}
		// TODO: THROW ERROR HERE
	}

	/**
	 * Fetchs a Value pointer in the scope by name
	 */
	Value* fetch(const CString* name) {
		if (!empty()) {
			Scope::const_iterator it = find(name);

			if (it != end()) {
				return it->second;
			}
		}
		return NULL;
	}

	/**
	 * Fetchs a Value pointer in the scope by a Value pointer
	 */
	Value* fetch(const Value* value) {
		return fetch(value->getName());
	}
private:
	/**
	 * Number identifying the scope
	 */
	int m_number;
};

typedef std::deque<Scope> SymbolTableBase;

class SymbolTable : public SymbolTableBase {
public:
	SymbolTable()
		: m_level(-1) { }

	~SymbolTable() { }

	/**
	 * Pusshes a new Value pointer to the current scope
	 */
	void pushVar(const CString* name, Value* var) throw() {
		at(m_level).push(name, var);
	}

	/**
	 * Pushes a new Value pointer to the current scope
	 */
	void pushVar(Value* var) throw() {
		at(m_level).push(var->getName(), var);
	}

	/**
	 * Returns the Value* pointer if the name is found
	 */
	Value* fetchVar(const CString* name) throw() {
		Value* value;

		/* There is no scope to search, shit just got real. */
		if (m_level == -1) {
			/* TODO: throw error or warning of unresolved symbol. */
			return NULL;
		}
		value = at(m_level).fetch(name);

		/**
		 * If not found in the current scope, try the outermost scopes
		 */
		if (value == NULL) {
			value = deepValueSearch(name);
		}

		return value;
	}
	
	/**
	 * Fetches a Value pointer if its name is found in the specified scope
	 */
	Value* fetchVarByScope(const CString* name, const Scope& scope) throw() {             
		return at(scope.getNumber()).fetch(name);
	}

	/**
	 * Fetches a Value pointer by a Value pointer
	 */
	Value* fetchVar(Value* value) throw() {
		return fetchVar(value->getName());
	}
	
	/**
	 * Fetches an specified scope by its number
	 */
	Scope& fetchScope(int level) throw() {
		return at(level);
	}

	/**
	 * Creates a new scope block
	 */
	void beginScope() throw() {
		push_back(Scope(++m_level));
	}

	/**
	 * Terminates the current block
	 */
	void endScope() throw() {
		pop_back();
		--m_level;
	}

	/**
	 * Returns the current scope block
	 */
	Scope& currentScope() throw() {
		return at(m_level);
	}

private:
	/**
	 * Number representing the scope level
	 */
	int m_level;

	/**
	 * Makes the deep search in the scopes innermost to outermost
	 */
	Value* deepValueSearch(const CString* name) {
		for (int i = m_level-1; i >= 0; --i) {
			Value* value = at(i).fetch(name);

			if (value) {
				return value;
			}
		}

		return NULL;
	}

	DISALLOW_COPY_AND_ASSIGN(SymbolTable);
};

} // clever

#endif // CLEVER_SYMBOLTABLE_H
