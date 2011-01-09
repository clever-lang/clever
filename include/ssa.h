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

#ifndef CLEVER_SSA_H
#define CLEVER_SSA_H

#include <boost/unordered_map.hpp>
#include <deque>

namespace clever {

class Value;

/**
 * SSA form
 */
class SSA {
public:
	typedef std::pair<Value*, Value*> VarTrack;
	typedef boost::unordered_map<const CString*, VarTrack> var_map;
	typedef std::deque<var_map> var_scope;

	SSA()
		: m_var_at(-1) { }
	~SSA() { }

	void register_var(Value* var, Value* value) throw() {
		m_variables.at(m_var_at).insert(std::pair<CString*, VarTrack>(var->get_name(), VarTrack(var, value)));
	}

	VarTrack* get_var(Value* var) throw() {
		CString* name = var->get_name();

		/* Searchs for the variable in the inner and out scopes */
		for (int i = m_var_at; i >= 0; --i) {
			var_map::iterator it = m_variables.at(i).find(name);

			if (it != m_variables.at(i).end()) {
				return &it->second;
			}
		}
		return NULL;
	}

	void pushVarMap(var_map map) throw() {
		m_variables.push_back(map);
		++m_var_at;
	}

	var_map& topVarMap() throw() {
		return m_variables.at(m_var_at);
	}

	void popVarMap() throw() {
		var_map::iterator it = topVarMap().begin();

		while (it != topVarMap().end()) {
			it->second.first->delRef();
			++it;
		}
		m_variables.pop_back();
		--m_var_at;
	}
private:
	var_scope m_variables;
	int m_var_at;
};

} // clever

#endif // CLEVER_SSA_H
