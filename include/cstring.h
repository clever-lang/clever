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

#ifndef CLEVER_CSTRING_H
#define CLEVER_CSTRING_H

#include <string>
#include <tr1/unordered_map>
#include "global.h"

/**
 * Returns the CString* pointer to a string
 */
//#define CSTRING(xstring) (clever::CString(xstring).intern())

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
		: std::string(str), m_id(0) { }

	explicit CString(const std::string& str)
		: std::string(str), m_id(0) { }

	bool hasSameId(const CString* cstring) const throw() {
		return get_id() == cstring->get_id();
	}

	IdType get_id() const throw() {
		return m_id;
	}

	bool operator==(const CString* cstring) throw() {
		return hasSameId(cstring);
	}

	bool operator==(const std::string& string) throw() {
		return compare(string) == 0;
	}
private:
	IdType m_id;
};

} // clever

/**
 * Specialization of boost::hash<> for working with CStrings
 */
namespace std { namespace tr1 {

template <>
struct hash<clever::CString*> : public unary_function<clever::CString*, size_t> {
public:
	size_t operator()(const clever::CString* key) const throw() {
		return hash<std::string>()(*static_cast<const std::string*>(key));
	}
};

}} // std::tr1

namespace clever {

class CStringTable;

extern CStringTable g_cstring_tbl;

typedef std::tr1::unordered_map<std::size_t, const CString*> CStringTableBase;

class CStringTable : public CStringTableBase {
public:
	typedef CString::IdType IdType;

	CStringTable() {}

	~CStringTable() {
		CStringTableBase::const_iterator it(begin()), end_table(end());

		while (it != end_table) {
			delete it->second;
			++it;
		}
	}

	bool contains(const CString* cstring) const {
		IdType id = cstring->get_id();
		return id != 0 && id < size() && find(id)->second->hasSameId(cstring);
	}

	const CString* getCString(long id) const throw() {
		return find(id)->second;
	}

	const CString* intern(const std::string& needle) throw() {
		std::tr1::hash<std::string> hash;
		const CString* str;

		IdType id = hash(needle);
		CStringTable::const_iterator it(find(id));

		if (it == end()) {
			str = new CString(needle, id);
			insert(std::pair<IdType, const CString*>(id, str));
		} else {
			str = it->second;
		}

		return str;
	}

	const CString* intern(const CString& needle) throw() {
		IdType id = needle.get_id();

		if (id) {
			return find(id)->second;
		}

		return intern(static_cast<std::string>(needle));
	}

private:
	DISALLOW_COPY_AND_ASSIGN(CStringTable);
};

} // clever

#endif /* CLEVER_CSTRING_H */

