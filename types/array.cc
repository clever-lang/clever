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

#include "types/type.h"
#include "types/array.h"

namespace clever {

CLEVER_TYPE_METHOD(Array::push) {
	ValueVector* vec = CLEVER_THIS()->getVector();

	vec->push_back(CLEVER_ARG(0));

	CLEVER_ARG(0)->addRef();
}

CLEVER_TYPE_METHOD(Array::toString) {
	ValueVector* vec = CLEVER_THIS()->getVector();
	std::string ret = "[", sep = ", ";

	for (unsigned int i = 0, j = vec->size(); i < j; ++i) {
		ret += vec->at(i)->toString();
		if (i+1 < j) {
			ret += sep;
		}
	}
	ret += "]";

	CLEVER_RETURN_STR(CSTRING(ret));
}

void Array::init() {
	addMethod(new Method("toString", (MethodPtr)&Array::toString, CLEVER_STR));

	addMethod(
		(new Method("push", (MethodPtr)&Array::push, CLEVER_VOID))
			->addArg("arg1", CLEVER_INT)
	);
}

DataValue* Array::allocateValue() const {
	return NULL;
}

} // clever
