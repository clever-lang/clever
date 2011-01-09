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

#ifndef CLEVER_TYPETABLE_H
#define CLEVER_TYPETABLE_H

#include <boost/unordered_map.hpp>
#include "type.h"

namespace clever {

class CString;

typedef boost::unordered_map<const CString*, Type*> TypeMap;

class TypeTable {
public:
	TypeTable() { }

	~TypeTable() {
		TypeMap::const_iterator it = s_type_table.begin(), end_type(s_type_table.end());

		while (it != end_type) {
			delete it->second;
			++it;
		}
	}

	static void insert(const CString* name, Type* type) {
		s_type_table.insert(std::pair<const CString*, Type*>(name, type));
	}

	/*
	 * Returns the Type pointer
	 */
	static Type* getType(const CString* name) throw() {
		TypeMap::const_iterator it = s_type_table.find(name);

		if (it != s_type_table.end()) {
			return it->second;
		}
		return NULL;
	}

	static TypeMap s_type_table;
};

extern TypeTable* g_type_table;

} // clever

#endif // CLEVER_TYPETABLE_H