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

#ifndef CLEVER_CSTRING_H
#define CLEVER_CSTRING_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include "compiler/clever.h"
#include <iostream>

/**
 * Returns the CString* pointer to a string
 */
#define CSTRING(xstring) (clever::g_cstring_tbl.intern(xstring))

namespace clever {

/**
 * String interning implementation
 */
class CString : public std::string {
public:
	typedef std::size_t IdType;

	CString()
		: std::string(), m_id(0) { };

	CString(const std::string& str, IdType id)
		: std::string(str), m_id(id) { }

	CString(const CString& str)
		: std::string(str.str()), m_id(str.m_id) { }

	bool hasSameId(const CString* cstring) const {
		return m_id == cstring->m_id;
	}

	IdType getId() const {
		return m_id;
	}

	const std::string& str() const {
		return *static_cast<const std::string*>(this);
	}

	const char* c_str() const {
		return static_cast<const std::string*>(this)->c_str();
	}

	bool operator==(const CString* cstring) {
		return hasSameId(cstring);
	}

	bool operator==(const std::string& string) {
		return compare(string) == 0;
	}
private:
	IdType m_id;
};

} // clever

/**
 * Specialization of boost::hash<> for working with CStrings
 */
#ifdef CLEVER_MSVC
namespace std {
#else
namespace std { namespace tr1 {
#endif

/**
 * Mersenne prime hash implementation for std::string on Windows
 */
#ifdef CLEVER_MSVC

template <>
struct hash<const std::string*> : public unary_function<const std::string*, size_t> {
public:
	size_t operator()(const std::string* s) const {
		size_t result = 2166136261U;
		std::string::const_iterator end = s->end();

		for (std::string::const_iterator it = s->begin(); it != end; ++it) {
			result = 127 * result + static_cast<unsigned char>(*it);
		}
		return result;
	}
};

#endif

template <>
struct hash<const clever::CString*> : public unary_function<const clever::CString*, size_t> {
public:
	size_t operator()(const clever::CString* key) const {
		return hash<std::string>()(key->str());
	}
};

#ifdef CLEVER_MSVC
} // std
#else
}} // std::tr1
#endif

namespace clever {

class CStringTable;

extern CStringTable g_cstring_tbl;

class CStringTable {
public:
	typedef CString::IdType IdType;
	typedef std::tr1::unordered_map<IdType, const CString*> CStringTableBase;

	CStringTable()
		: m_map() {}

	~CStringTable() {
		CStringTableBase::const_iterator it(m_map.begin()), end_table(m_map.end());

		while (it != end_table) {
			delete it->second;
			++it;
		}
	}

	const CString* intern(const std::string& needle) {
		IdType id = std::tr1::hash<const std::string*>()(&needle);
		CStringTableBase::const_iterator it(m_map.find(id));

		if (it == m_map.end()) {
			const CString* str = new CString(needle, id);
			m_map.insert(std::pair<IdType, const CString*>(id, str));

			return str;
		}
		return it->second;
	}

private:
	CStringTableBase m_map;
	DISALLOW_COPY_AND_ASSIGN(CStringTable);
};

} // clever

#endif /* CLEVER_CSTRING_H */

