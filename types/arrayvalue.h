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

#ifndef CLEVER_ARRAYVALUE_H
#define CLEVER_ARRAYVALUE_H

#include "compiler/value.h"

namespace clever {

struct ArrayValue : public DataValue
{
	ValueVector* m_array;
	uint32_t m_version;

	ArrayValue() : m_array(new ValueVector), m_version(0) {}
	ArrayValue(ValueVector* array) : m_array(array), m_version(0) {}
	
	ValueVector* getArray() const {
		return m_array;
	}

	bool valid() const {
		return true;
	}
	
	uint32_t getVersion() const {
		return m_version;
	}
	
	void changeVersion() {
		m_version++;
	}

	~ArrayValue() {
		delete m_array;
	}
};

} // clever

#endif // CLEVER_ARRAYVALUE_H
