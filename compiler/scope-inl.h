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

#ifndef CLEVER_SCOPEINL_H
#define CLEVER_SCOPEINL_H

#ifndef CLEVER_SCOPE_H
#include "scope.h"
#endif

namespace clever {
inline Symbol* Scope::getLocalSym(const CString* name) {
	SymbolMap::iterator it = m_symbols.find(name);

	if (it == m_symbols.end()) {
		return NULL;
	}
	return it->second;
}

// Resolve a symbol name recursively
inline Symbol* Scope::getSym(const CString* name) {
	Symbol* sym = getLocalSym(name);

	if (sym != NULL) {
		return sym;
	}

	if (m_parent != NULL) {
		sym = m_parent->getSym(name);
	}

	return sym;
}

// Resolve a value-symbol name locally
inline Value* Scope::getLocalValue(const CString* name) {
	Symbol* s = getLocalSym(name);

	if (s == NULL || !s->isValue())
		return NULL;

	return s->getValue();

}

// Resolve a value-symbol name recursively
inline Value* Scope::getValue(const CString* name) {
	Symbol* s = getSym(name);

	if (s == NULL || !s->isValue())
		return NULL;

	return s->getValue();
}

// Resolve a type-symbol name recursively
inline const Type* Scope::getType(const CString* name) {
	Symbol* s = getSym(name);

	if (s == NULL || !s->isType())
		return NULL;

	return s->getType();
}
} // clever

#endif // CLEVER_SCOPEINL_H
