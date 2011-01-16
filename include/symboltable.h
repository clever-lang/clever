/*
 * Clever language
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

#ifndef CLEVER_SYMBOLTABLE_H
#define CLEVER_SYMBOLTABLE_H

#include <deque>
#include <boost/unordered_map.hpp>
#include "global.h"
#include "value.h"

namespace clever {

class CString;
class Scope;

typedef boost::unordered_map<const CString*, Value*> ScopeBase;
typedef std::deque<Scope> ScopeManagerBase;

class Scope : public ScopeBase {
public:
	Scope() { }
	~Scope() {
		Scope::const_iterator it = begin(), end_it = end();

		while (it != end_it) {
			it->second->delRef();
			++it;
		}
	}

	void push(const CString* name, Value* value) {
		insert(std::pair<const CString*, Value*>(name, value));
	}

	void push(Value* value) {
		if (!value->hasName()) {
			// TODO: THROW ERROR HERE
		}
		push(value->get_name(), value);
	}

	Value* fetch(const CString* name) {
		if (!empty()) {
			Scope::iterator it = find(name);

			if (it != end())
				return it->second;
		}

		return NULL;
	}
};

class ScopeManager : public ScopeManagerBase {
public:
	ScopeManager() : m_scope(-1) { }

	inline void pushValue(const CString* name, Value* value) {
		at(m_scope).push(name, value);
	}

	inline void pushValue(Value* value) {
		at(m_scope).push(value);
	}

	Value* fetchValue(const CString* name) {
		if (m_scope == -1) {
			// XXX: hm, maybe we should throw a warning here?
			return NULL;
		}

		Value* value = at(m_scope).fetch(name);

		if (value == NULL) {
			value = deepValueSearch(name);
		}
		return value;
	}

	inline void enter() {
		push_back(Scope());
		++m_scope;
	}

	inline void leave() {
		if (m_scope == -1) {
			// TODO: throw error
		}

		pop_back();
		--m_scope;
	}

	DISALLOW_COPY_AND_ASSIGN(ScopeManager);
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
};

} // clever

#endif // CLEVER_SYMBOLTABLE_H
