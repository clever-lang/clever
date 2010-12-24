/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 * $Id:$
 */

#ifndef CLEVER_CSTRING_H
#define CLEVER_CSTRING_H

#include <string>
#include <vector>
#include <algorithm>

namespace clever {

class CStringTable;

class CString : public std::string {
public:
	CString(std::string& str) : std::string(str) { store(); }
	CString(char* str) : std::string(str) { store(); }

	const CString& intern();

	bool hasSameId(const CString& cstring) const { return get_id() == cstring.get_id(); }
	int get_id() const { return m_id; }

private:
	static CStringTable table;
	int m_id;

	void store();
};

typedef std::vector<CString> CStringVector;

class CStringTable : public CStringVector {
public:
	CStringTable() : CStringVector() {  }

	bool contains(const CString& cstring) const {
		int id = cstring.get_id();
		return id != -1 && id < size() && at(id).hasSameId(cstring);
	}

	int findId(const CString& cstring) const {
		CStringVector::const_iterator it = find(begin(), end(), cstring);

		if (it == end()) {
			return -1;
		}

		return distance(begin(), it);
	}

	const CString& getCString(int id) const {
		return at(id);
	}

	int push_back(const CString& cstring) {
		int id = findId(cstring);

		if (id == -1) {
			CStringVector::push_back(cstring);
			id = size()-1;
		}

		return id;
	}
};

} // clever

#endif /* CLEVER_CSTRING_H */

