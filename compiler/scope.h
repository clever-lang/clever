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

#ifndef CLEVER_SCOPE_H
#define CLEVER_SCOPE_H

namespace clever {

class CString;

class Scope {
public:
	typedef std::vector<Scope*> ScopeVector;
	typedef std::vector<const CString*> SymbolMap;

	Scope()
		: m_parent(NULL), m_children(), m_symbols(), m_size(0), m_id(0) {}

	explicit Scope(Scope* parent)
		: m_parent(parent), m_children(), m_symbols(), m_size(0), m_id(0) {}

	~Scope() {
		ScopeVector::const_iterator it = m_children.begin(),
			end = m_children.end();

		while (it != end) {
			delete *it;
			++it;
		}
	}

	size_t push(const CString* name) {
		m_symbols.push_back(name);
		return m_size++;
	}

	const CString* at(size_t idx) { return m_symbols[idx]; }

	void setId(size_t id) { m_id = id; }
	size_t getId() const { return m_id; }

	size_t size() const { return m_size; }

	Scope* newLexicalScope() {
		Scope* s = new Scope(this);
		m_children.push_back(s);
		return s;
	}

	Scope* getParent() const { return m_parent; }

	void clear();
private:
	Scope* m_parent;
	ScopeVector m_children;
	SymbolMap m_symbols;
	size_t m_size;
	size_t m_id;

	DISALLOW_COPY_AND_ASSIGN(Scope);
};

} // clever

#endif // CLEVER_SCOPE_H
