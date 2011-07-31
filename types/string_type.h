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

#ifndef CLEVER_STRING_H
#define CLEVER_STRING_H

#include "type.h"
#include "compiler/value.h"

namespace clever {

class String : public Type {
public:
	String() :
		Type("String") { }

	void init();
	DataValue* allocateValue() const;

	/**
	 * Type methods
	 */
	static CLEVER_TYPE_METHOD(replace);
	static CLEVER_TYPE_METHOD(substring);
	static CLEVER_TYPE_METHOD(toDouble);
	static CLEVER_TYPE_METHOD(toInteger);
	
	/**
	 * Type handlers
	 */
	CLEVER_TYPE_INC_HANDLER_D { return NULL; }
	CLEVER_TYPE_DEC_HANDLER_D { return NULL; }
private:
	DISALLOW_COPY_AND_ASSIGN(String);
};

} // clever

#endif // CLEVER_STRING_H
