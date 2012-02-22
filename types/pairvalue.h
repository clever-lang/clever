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

#ifndef CLEVER_PAIRVALUE_H
#define CLEVER_PAIRVALUE_H

#include <utility>
#include "compiler/value.h"

namespace clever {

struct PairValue : public DataValue {
	typedef std::pair<Value*, Value*> InternalType;

	PairValue(const Type* t1, const Type* t2)
		: m_pair(new Value(t1), new Value(t2)) {
			first()->initialize();
			second()->initialize();
	}

	PairValue(Value* first, Value* second)
		: m_pair(new Value(), new Value()) {
			m_pair.first->copy(first);
			m_pair.second->copy(second);
	}

	Value* first() const {
		return m_pair.first;
	}

	Value* second() const {
		return m_pair.second;
	}

	void setFirst(Value* v) {
		m_pair.first = v;
	}

	void setSecond(Value* v) {
		m_pair.second = v;
	}

	InternalType& getPair() {
		return m_pair;
	}

	~PairValue() {
		m_pair.first->delRef();
		m_pair.second->delRef();
	}

private:
	InternalType m_pair;

	DISALLOW_COPY_AND_ASSIGN(PairValue);
};

} // clever

#endif // CLEVER_PAIRVALUE_H
