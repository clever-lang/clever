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

class CString;
class Value;

/**
 * Minimal SSA form
 */
class SSA {
public:
	typedef boost::unordered_map<const CString*, Value*> VarMap;
	typedef std::deque<VarMap> VarScope;
	typedef std::pair<const CString*, Value*> VarPair;

	SSA()
		: m_var_at(-1) { }

	~SSA() { }

	/**
	 * Adds a new variable to current scope
	 */
	void pushVar(Value* var) throw() {
		m_variables.at(m_var_at).insert(VarPair(var->get_name(), var));
	}
	/**
	 * Returns the Value* pointer if the name is found
	 */
	Value* fetchVar(Value* var) throw() {
		const CString* name = var->get_name();

		/* Searchs for the variable in the inner and out scopes */
		for (int i = m_var_at; i >= 0; --i) {
			VarMap::const_iterator it = m_variables.at(i).find(name);

			if (it != m_variables.at(i).end()) {
				return it->second;
			}
		}
		return NULL;
	}
	/**
	 * Creates a new scope block
	 */
	void newBlock() throw() {
		m_variables.push_back(VarMap());
		++m_var_at;
	}
	/**
	 * Returns the current scope block
	 */
	VarMap& topBlock() throw() {
		return m_variables.at(m_var_at);
	}
	/**
	 * Terminates the current block
	 */
	void endBlock() throw() {
		m_variables.pop_back();
		--m_var_at;
	}
private:
	VarScope m_variables;
	int m_var_at;

	DISALLOW_COPY_AND_ASSIGN(SSA);
};

} // clever

#endif // CLEVER_SSA_H
