/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CSTRING_H
#define CLEVER_CSTRING_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include "core/clever.h"
#include "core/refcounted.h"
#include <iostream>

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

#ifdef CLEVER_MSVC
} // std
#else
}} // std::tr1
#endif

namespace clever {

typedef std::string CString;

class CStringTable {
public:
	typedef CString::size_type IdType;

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
#ifdef CLEVER_MSVC
		IdType id = std::tr1::hash<const std::string*>()(&needle);
#else
		IdType id = std::tr1::hash<std::string>()(needle);
#endif
		CStringTableBase::const_iterator it(m_map.find(id));

		if (it == m_map.end()) {
			const CString* str = new CString(needle);
			m_map.insert(std::pair<IdType, const CString*>(id, str));

			return str;
		}
		return it->second;
	}

private:
	CStringTableBase m_map;
	DISALLOW_COPY_AND_ASSIGN(CStringTable);
};

extern CStringTable* g_cstring_tbl;

/**
 * Returns the CString* pointer to a string
 */
inline const CString* CSTRING(const std::string& str) {
	return g_cstring_tbl->intern(str);
}

/**
 * Returns the CString* pointer to a possible temporary string
 */
inline const CString* CSTRINGT(const std::string& str, bool interned = false) {
	return new CString(str);
}

} // clever

#endif /* CLEVER_CSTRING_H */
