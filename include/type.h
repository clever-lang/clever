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

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <string>
#include <boost/unordered_map.hpp>
#include "module.h"

namespace clever {

class CString;
class Method;
class Type;

typedef void (Type::*MethodPtr)(CLEVER_METHOD_ARGS);

class Method {
public:
	Method(const CString* name, MethodPtr method)
		: m_name(name), m_method(method) { }

	~Method() { }

	const CString* get_name() const throw() {
		return m_name;
	}

	MethodPtr get_method() const throw() {
		return m_method;
	}
private:
	const CString* m_name;
	MethodPtr m_method;
};

class Type {
public:
	typedef boost::unordered_map<const CString*, Method*> MethodMap;
	typedef std::pair<const CString*, Method*> MethodPair;


	explicit Type(const std::string& name)
		: m_name(name) { }

	virtual ~Type() {
		MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

		while (it != end) {
			delete it->second;
			++it;
		}
	}

	void addMethod(Method* method) throw() {
		m_methods.insert(std::pair<const CString*, Method*>(method->get_name(), method));
	}

	Method* getMethod(const CString* name) throw() {
		MethodMap::iterator it = m_methods.find(name);

		if (it != m_methods.end()) {
			return it->second;
		}
		return NULL;
	}

	std::string get_name() const throw() {
		return m_name;
	}

	virtual void Init() = 0;
private:
	MethodMap m_methods;
	const std::string& m_name;
};

} // clever

#endif // CLEVER_TYPE_H