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

#ifndef CLEVER_OPERAND_H
#define CLEVER_OPERAND_H

#include "compiler/callablevalue.h"
#include "compiler/value.h"

namespace clever {

enum OperandType { UNUSED, VALUE, CALLABLE, VECTOR, ADDR };

/**
 * Operand representation
 */
class Operand {
public:
	Operand()
		: m_type(UNUSED) {}

	explicit Operand(Value* value)
		: m_type(VALUE) {
		m_data.value = value;
	}

	explicit Operand(CallableValue* callable)
		: m_type(CALLABLE) {
		m_data.callable = callable;
	}

	explicit Operand(ValueVector* vector)
		: m_type(VECTOR) {
		m_data.vector = vector;
	}

	explicit Operand(long addr)
		: m_type(ADDR) {
		m_data.addr = addr;
	}

	~Operand() {
		if (m_type == VALUE || m_type == CALLABLE) {
			CLEVER_SAFE_DELREF(m_data.value);
		} else if (m_type == VECTOR && m_data.vector) {
			ValueVector::const_iterator it(m_data.vector->begin()),
				end(m_data.vector->end());

			while (it != end) {
				CLEVER_DELREF(*it);
				++it;
			}
			delete m_data.vector;
		}
	}

	OperandType getType() const { return m_type; }

	void setAddr(long addr) {
		m_type = ADDR;
		m_data.addr = addr;
	}

	void setValue(Value* value) {
		m_type = VALUE;
		m_data.value = value;
	}

	long           getAddr() const { return m_data.addr; }
	Value*         getValue() const { return m_data.value; }
	CallableValue* getCallable() const { return m_data.callable; }
	ValueVector*   getVector() const { return m_data.vector; }
private:

	OperandType m_type;

	union OperandData {
		Value* value;
		CallableValue* callable;
		ValueVector* vector;
		long addr;

		OperandData()
			: addr(0) {}
	} m_data;

	DISALLOW_COPY_AND_ASSIGN(Operand);
};

} // clever

#endif // CLEVER_OPERAND_H
