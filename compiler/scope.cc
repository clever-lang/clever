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
#include <stdio.h>

namespace clever {

Scope g_scope;

Scope::~Scope() {
	SymbolMap::const_iterator sym = m_symbols.begin(), last_sym = m_symbols.end();
	std::vector<Scope*>::const_iterator child = m_children.begin(), last_child = m_children.end();

	while (sym != last_sym) {
		Symbol* s = sym->second;

		if (s->isValue()) {
			printf("value addr: %p\n", (void*)s->getValue());
			s->getValue()->delRef();
		}

		++sym;
	}
	
	sym = m_symbols.begin();
	
	while (sym != last_sym) {
		Symbol* s = sym->second;

		if (s->isType()) {
			printf("type addr: %p\n", (void*)s->getType());
			const_cast<Type*>(s->getType())->delRef();
		}
		
		delete s;
		++sym;
	}

	while (child != last_child) {
		delete *child;
		++child;
	}
}

} // clever

