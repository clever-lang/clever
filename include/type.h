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

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <string>
#include <tr1/unordered_map>
#include "module.h"

namespace clever {

class CString;

/**
 * Type representation
 */
class Type {
public:
	typedef std::tr1::unordered_map<const CString*, MethodPtr> MethodMap;
	typedef std::pair<const CString*, MethodPtr> MethodPair;

	explicit Type(const char* name)
		: m_name(name) { }

	virtual ~Type() {
		MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

		while (it != end) {
			++it;
		}
	}

	void addMethod(const CString* name, MethodPtr method) throw() {
		m_methods.insert(std::pair<const CString*, MethodPtr>(name, method));
	}

	MethodPtr getMethod(const CString* name) const throw() {
		MethodMap::const_iterator it = m_methods.find(name);

		if (it != m_methods.end()) {
			return it->second;
		}
		return NULL;
	}

	const char* get_name() const throw() {
		return m_name;
	}

	/**
	 * Pure virtual methods
	 */
	virtual void Init() = 0;
private:
	MethodMap m_methods;
	const char* m_name;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

} // clever

#endif // CLEVER_TYPE_H
