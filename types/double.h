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

#ifndef CLEVER_DOUBLE_H
#define CLEVER_DOUBLE_H

#include "type.h"
#include "compiler/value.h"

namespace clever {

class Double : public Type {
public:
	Double() :
		Type("Double") { }

	void init();
	DataValue* allocateValue() const;

	/**
	 * Type methods
	 */
	static CLEVER_TYPE_METHOD(constructor);
	static CLEVER_TYPE_METHOD(toString);
	static CLEVER_TYPE_METHOD(sqrt);
	
	/**
	 * Type operator methods
	 */
	static CLEVER_TYPE_METHOD(plus);

	/**
	 * Type handlers
	 */
	CLEVER_TYPE_INC_HANDLER_D { value->setDouble(value->getDouble() + 1); return value; }
	CLEVER_TYPE_DEC_HANDLER_D { value->setDouble(value->getDouble() - 1); return value; }

	CLEVER_TYPE_ASSIGN_HANDLER_D {
		if (newvalue->getTypePtr() == this) {
			value->copy(newvalue);
		} else {
			value->setDouble(newvalue->getInteger());
		}
	}

	CLEVER_TYPE_MINUS_HANDLER_D {
		double x = op1->isDouble() ? op1->getDouble() : op1->getInteger();
		double y = op2->isDouble() ? op2->getDouble() : op2->getInteger();
		value->setDouble(x - y);
	}

	CLEVER_TYPE_MULT_HANDLER_D {
		double x = op1->isDouble() ? op1->getDouble() : op1->getInteger();
		double y = op2->isDouble() ? op2->getDouble() : op2->getInteger();
		value->setDouble(x * y);
	}

	CLEVER_TYPE_DIV_HANDLER_D {
		double x = op1->isDouble() ? op1->getDouble() : op1->getInteger();
		double y = op2->isDouble() ? op2->getDouble() : op2->getInteger();
		value->setDouble(x / y);
	}
private:
	DISALLOW_COPY_AND_ASSIGN(Double);
};

} // clever

#endif // CLEVER_DOUBLE_H
