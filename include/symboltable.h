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

#ifndef CLEVER_SYMBOLTABLE_H
#define CLEVER_SYMBOLTABLE_H

#include <deque>
#include <boost/unordered_map.hpp>

namespace clever {

class Value;

class SymbolTable {
public:
	typedef boost::unordered_map<const CString*, Value*> var_map;
	typedef std::deque<var_map> var_scope;

	SymbolTable()
		: m_var_at(-1) { }

	inline void register_var(Value* var) {
		m_variables.at(m_var_at).insert(std::pair<CString*, Value*>(var->getStringP(), var));
	}

	inline void register_var(Value* var, Value* value) {
		m_variables.at(m_var_at).insert(std::pair<CString*, Value*>(var->getStringP(), value));
		var->set_value(value);
	}

	inline Value* get_var(Value* var) {
		Value* value = var->isNamedValue() ? var->get_value() : NULL;
		CString* name;

		if (value) {
			return value;
		}

		name = var->getStringP();

		/* Searchs for the variable in the inner and out scopes */
		for (int i = m_var_at; i >= 0; --i) {
			var_map::iterator it = m_variables.at(i).find(name);

			if (it != m_variables.at(i).end()) {
				var->set_value(it->second);
				return it->second;
			}
		}
		return NULL;
	}

	inline void pushVarMap(var_map map) {
		m_variables.push_back(map);
		++m_var_at;
	}

	inline var_map& topVarMap() {
		return m_variables.at(m_var_at);
	}

	inline void popVarMap() {
		var_map::iterator it = topVarMap().begin();

		while (it != topVarMap().end()) {
			it->second->delRef();
			++it;
		}
		m_variables.pop_back();
		--m_var_at;
	}

	DISALLOW_COPY_AND_ASSIGN(SymbolTable);
private:
	var_scope m_variables;
	int m_var_at;
};

} // clever

#endif // CLEVER_SYMBOLTABLE_H