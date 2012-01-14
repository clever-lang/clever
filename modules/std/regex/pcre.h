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

#ifndef CLEVER_STD_REGEX_PCRE_H
#define CLEVER_STD_REGEX_PCRE_H

#include "compiler/module.h"
#include "compiler/value.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std { namespace regex {

class Pcre : public Type {
public:
	Pcre() : Type(CSTRING("Pcre")) {}

	void init();
	DataValue* allocateValue() const;
	void destructor(Value* value) const;

	static CLEVER_TYPE_METHOD(constructor);
	static CLEVER_TYPE_METHOD(matches);
	static CLEVER_TYPE_METHOD(replace);
	static CLEVER_TYPE_METHOD(replaceAll);

	CLEVER_TYPE_ASSIGN_HANDLER_D {
		newvalue->getDataValue()->addRef();
		value->copy(newvalue);
	}
};

}}}} // clever::packages::std::regex

#endif
