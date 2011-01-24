/*
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
 *
 * $Id$
 */

#ifndef CLEVER_SSA_H
#define CLEVER_SSA_H

#include <tr1/unordered_map>
#include <deque>
#include "value.h"

namespace clever {

class CString;

typedef std::tr1::unordered_map<const CString*, NamedValue*> ScopeBase;

class Scope : public ScopeBase {
public:
	Scope() { }
	~Scope() { }

	void push(const CString* name, NamedValue* value) {
		insert(std::pair<const CString*, NamedValue*>(name, value));
	}

	void push(NamedValue* value) {
		if (!value->hasName()) {
			// TODO: THROW ERROR HERE
		}

		push(value->get_name(), value);
	}

	NamedValue* fetch(const CString* name) {
		if (!empty()) {
			Scope::iterator it = find(name);

			if (it != end())
				return it->second;
		}

		return NULL;
	}

	NamedValue* fetch(const NamedValue* value) {
		return fetch(value->get_name());
	}
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
	void pushVar(const CString* name, NamedValue* var) throw() {
		at(m_scope).push(name, var);
	}

	void pushVar(NamedValue* var) throw() {
		at(m_scope).push(var->get_name(), var);
	}

	/**
	 * Returns the Value* pointer if the name is found
	 */
	NamedValue* fetchVar(const CString* name) throw() {
		/* There is no scope to search, shit just got real. */
		if (m_scope == -1) {
			/* TODO: throw error or warning of unreslved symbol. */
			return NULL;
		}

		NamedValue* value = at(m_scope).fetch(name);

		if (value == NULL) {
			value = deepValueSearch(name);
		}

		return value;
	}

	NamedValue* fetchVar(NamedValue* value) throw() {
		return fetchVar(value->get_name());
	}

	/**
	 * Creates a new scope block
	 */
	void beginScope() throw() {
		push_back(Scope());
		++m_scope;
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
	
	NamedValue* deepValueSearch(const CString* name) {
		for (int i = m_scope-1; i >= 0; --i) {
			NamedValue* value = at(i).fetch(name);

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
