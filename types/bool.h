/**
 * Clever programming language
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
 */

#ifndef CLEVER_BOOL_H
#define CLEVER_BOOL_H

#include "type.h"
#include "compiler/value.h"

namespace clever {

class Bool : public Type {
public:
	Bool() :
		Type("Bool") { }

	void init();
	DataValue* allocateValue() const;

	/**
	 * Type methods
	 */
	static CLEVER_TYPE_METHOD(constructor);
	static CLEVER_TYPE_METHOD(toString);
	
	/**
	 * Type handlers
	 */
	CLEVER_TYPE_INC_HANDLER_D { return value; }
	CLEVER_TYPE_DEC_HANDLER_D { return value; }
	CLEVER_TYPE_ASSIGN_HANDLER_D { 
		if (newvalue->getTypePtr() == this) value->copy(newvalue);
		else value->setBoolean((int64_t)newvalue->getDouble()); 
	}
	//CLEVER_TYPE_MOD_HANDLER_D { value->setInteger(op1->getBoolean() % op2->getBoolean()); }
private:
	DISALLOW_COPY_AND_ASSIGN(Bool);
};

} // clever

#endif // CLEVER_BOOL_H
