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

#ifndef CLEVER_VALUE_H
#define CLEVER_VALUE_H

#include "compiler/refcounted.h"

namespace clever {

class Value : public RefCounted {
public:
	union Data {
		long lval;
		double dval;

		Data(long n) : lval(n) {}
		Data(double n) : dval(n) {}
	};

	enum DataType { INT, DOUBLE };

	Value() : RefCounted(), m_data(0L) {}
	Value(long n) : RefCounted(), m_data(n), m_type(INT) {}
	Value(double n) : RefCounted(), m_data(n), m_type(DOUBLE) {}

	bool isInt() const { return m_type == INT; }
	long getInt() const { return m_data.lval; }

	bool isDouble() const { return m_type == DOUBLE; }
	double getDouble() const { return m_data.dval; }

	DataType getType() const { return m_type; }
private:
	Data m_data;
	DataType m_type;
};

} // clever

#endif // CLEVER_VALUE_H
