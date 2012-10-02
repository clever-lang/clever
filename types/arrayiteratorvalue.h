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

#ifndef CLEVER_ARRAYITERATORVALUE_H
#define CLEVER_ARRAYITERATORVALUE_H

#include "types/arrayvalue.h"
#include "compiler/value.h"

namespace clever {

struct ArrayIteratorValue : public DataValue {
	ArrayIteratorValue(ArrayValue* vec) : m_iterator(vec->m_array->begin()),
		m_end(vec->m_array->end()) {
	}
	
	ArrayIteratorValue() {}
	
	bool valid() const {
		return m_iterator != m_end;
	}
	
	void operator--() {
		--m_iterator;
	}
	
	void operator++() {
		++m_iterator;
	}
	
	ValueVector::iterator operator+(int offset) {
		return m_iterator + offset;
	}
	
	ValueVector::iterator operator-(int offset) {
		return m_iterator - offset;
	}

	ValueVector::iterator& getIterator() {
		return m_iterator;
	}
	
	ValueVector::iterator& getEnd() {
		return m_end;
	}

	Value* get() {
		return *m_iterator;
	}
	
	void setIterator(ValueVector::iterator& it) {
		m_iterator = it;
	}
	
	void setEnd(ValueVector::iterator& it) {
		m_end = it;
	}

	~ArrayIteratorValue() {
	}
private:
	ValueVector::iterator m_iterator, m_end;
	DISALLOW_COPY_AND_ASSIGN(ArrayIteratorValue);
};

} // clever

#endif

