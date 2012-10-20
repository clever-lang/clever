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

#include "compiler/scope.h"
#include "compiler/value.h"

namespace clever {

Scope g_scope;

Symbol::~Symbol() {
	if (m_type == TYPE) {
		const_cast<Type*>(m_data.type)->delRef();
		m_data.type = NULL;
	} else if (m_type == VALUE) {
		m_data.value->delRef();
		m_data.value = NULL;
	}
}

void Scope::clear() {
	SymbolMap::const_iterator sym(m_symbols.begin()), last_sym(m_symbols.end());
	ScopeVector::const_iterator child(m_children.begin()),
		last_child(m_children.end());

	while (child != last_child) {
		delete *child;

		++child;
	}

	child = m_orphanedChildren.begin();
	last_child = m_orphanedChildren.end();

	while (child != last_child) {
		delete *child;

		++child;
	}

	m_children.clear();
	m_orphanedChildren.clear();

	/**
	 * On global scope we have to destruct the Type ptr first, then
	 * the other symbols
	 */
	if (this == &g_scope) {
		while (sym != last_sym) {
			if (!sym->second->isType()) {
				delete sym->second;
				m_symbols.erase(sym++);
			} else {
				++sym;
			}			
		}
		
		sym = m_symbols.begin();
		last_sym = m_symbols.end();
	}
		
	while (sym != last_sym) {
		delete sym->second;
		++sym;
	}		

	m_symbols.clear();

}

} // clever

