/**
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
 */

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <cstring>
#include <tr1/unordered_map>
#include "compiler/cstring.h"
#include "compiler/method.h"

namespace clever {

class CString;

/**
 * Prototype for class methods which the class represents a type
 */
#define CLEVER_TYPE_METHOD_ARGS const ValueVector* args, Value* retval, Value* value
#define CLEVER_TYPE_METHOD(name) void CLEVER_FASTCALL name(CLEVER_TYPE_METHOD_ARGS) throw()

/**
 * Type representation
 */
class Type {
public:
	typedef std::tr1::unordered_map<std::string, Method*> MethodMap;
	typedef std::pair<std::string, Method*> MethodPair;

	explicit Type(const char* name)
		: m_name(name) { }

	virtual ~Type() {
		MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

		while (it != end) {
			delete it->second;
			++it;
		}
	}

	void addMethod(Method* method) throw() {
		m_methods.insert(MethodPair(method->get_name(), method));
	}

	const Method* getMethod(const CString* name) const throw() {
		MethodMap::const_iterator it = m_methods.find(*name);

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
	virtual void init() = 0;
	
	/**
	 * Allocate a buffer for the type's attributes (if the type is not String, Double, Int, etc.) 
	 */
	virtual void* allocateValue() const = 0;
private:
	MethodMap m_methods;
	const char* m_name;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

} // clever

#endif // CLEVER_TYPE_H
