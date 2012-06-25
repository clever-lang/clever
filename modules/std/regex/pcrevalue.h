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

#ifndef CLEVER_STD_REGEX_PCREVALUE_H
#define CLEVER_STD_REGEX_PCREVALUE_H

#include <pcrecpp.h>
#include <string>
#include "compiler/datavalue.h"


namespace clever { namespace packages { namespace std { namespace regex {

class PcreMatch {
public:
	PcreMatch()
		: last_input(NULL), groups(NULL), matches(NULL), n_groups(0) {}

	~PcreMatch() {
		if (groups == NULL) {
			return;
		}
		delete[] matches;

		for (int i = 0; i < n_groups; ++i) {
			delete groups[i];
		}

		delete[] groups;
	}

	const CString* last_input;
	pcrecpp::Arg** groups;
	::std::string* matches;
	int n_groups;
	pcrecpp::StringPiece input;
private:
	DISALLOW_COPY_AND_ASSIGN(PcreMatch);
};

class PcreValue : public DataValue {
public:
	PcreValue()
		: re(NULL) {}

	virtual ~PcreValue() {
		if (re) {
			delete re;
		}
	}
	
	bool valid() const {
		return re != NULL;
	}

	pcrecpp::RE* re;
	PcreMatch match;
private:
	DISALLOW_COPY_AND_ASSIGN(PcreValue);
};

}}}} // clever::packages::std::regex

#endif
