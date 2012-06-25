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

#ifndef CLEVER_GLOB_ITERATOR_VALUE_H
#define CLEVER_GLOB_ITERATOR_VALUE_H

#include <vector>
#include <iterator>
#include "compiler/datavalue.h"

namespace clever { namespace packages { namespace std { namespace file {

class GlobIteratorValue : public DataValue {
public:
	GlobIteratorValue()
		: data(NULL), index(0) {}

	virtual ~GlobIteratorValue() {}

	bool valid() const {
		return data != NULL;
	}

	::std::vector<char*>* data;
	size_t index;
};

}}}} // clever::packages::std::file

#endif // CLEVER_GLOB_ITERATOR_VALUE_H
