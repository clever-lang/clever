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

#ifndef CLEVER_SSA_H
#define CLEVER_SSA_H

#include <tr1/unordered_map>
#include <deque>
#include "global.h"
#include "value.h"

namespace clever {

class CString;

typedef std::tr1::unordered_map<const CString*, Value*> ScopeBase;

class Scope : public ScopeBase {
public:
	Scope(int number)
		: m_number(number) { }
	~Scope() {
		ScopeBase::const_iterator it = begin(), end_ = end();

		while (it != end_) {
			it->second->delRef();
			++it;
		}
	}
	
	int getNumber() throw() { return m_number; }

	void push(const CString* name, Value* value) {
		if (EXPECTED(value->hasName())) {
			insert(std::pair<const CString*, Value*>(name, value));
		}

		// TODO: THROW ERROR HERE
	}

	void push(Value* value) {
		if (EXPECTED(value->hasName())) {
			push(value->getName(), value);
		}
		// TODO: THROW ERROR HERE
	}

	Value* fetch(const CString* name) {
		if (!empty()) {
			Scope::const_iterator it = find(name);

			if (it != end()) {
				return it->second;
			}
		}
		return NULL;
	}

	Value* fetch(const Value* value) {
		return fetch(value->getName());
	}
private:
	int m_number;
};

/**
 * Minimal SSA form
 */
typedef std::deque<Scope> SSABase;
class SSA : public SSABase {
public:
	SSA()
		: m_scope(-1) { }

	~SSA() { }

	/**
	 * Adds a new variable to current scope
	 */
	void pushVar(const CString* name, Value* var) throw() {
		at(m_scope).push(name, var);
	}

	void pushVar(Value* var) throw() {
		at(m_scope).push(var->getName(), var);
	}

	/**
	 * Returns the Value* pointer if the name is found
	 */
	Value* fetchVar(const CString* name) throw() {
		/* There is no scope to search, shit just got real. */
		if (m_scope == -1) {
			/* TODO: throw error or warning of unreslved symbol. */
			return NULL;
		}

		Value* value = at(m_scope).fetch(name);

		if (value == NULL) {
			value = deepValueSearch(name);
		}

		return value;
	}

	Value* fetchVar(Value* value) throw() {
		return fetchVar(value->getName());
	}
	
	Scope& fetchScope(int number) throw() {
		return at(number);
	}

	/**
	 * Creates a new scope block
	 */
	void beginScope() throw() {
		push_back(Scope(++m_scope));
	}

	/**
	 * Terminates the current block
	 */
	void endScope() throw() {
		pop_back();
		--m_scope;
	}

	/**
	 * Returns the current scope block
	 */
	Scope& currentScope() throw() {
		return at(m_scope);
	}

private:
	int m_scope;

	Value* deepValueSearch(const CString* name) {
		for (int i = m_scope-1; i >= 0; --i) {
			Value* value = at(i).fetch(name);

			if (value) {
				return value;
			}
		}

		return NULL;
	}

	DISALLOW_COPY_AND_ASSIGN(SSA);
};

} // clever

#endif // CLEVER_SSA_H
