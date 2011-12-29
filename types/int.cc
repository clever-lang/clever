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

#include <iostream>
#include "compiler/cstring.h"
#include "types/typeutils.h"
#include "types/type.h"
#include "types/int.h"
#include "types/nativetypes.h"

namespace clever {


/**
 * Int::Int([Int value])
 * Construct an Int object with a default value (if no args) or a 
 * custom value
 */
CLEVER_TYPE_METHOD(Integer::constructor) {
	if (args) {
		retval->setInteger(args->at(0)->getInteger());
	}
	else {
		retval->setInteger(0);
	}
}

/**
 * Int::toString()
 * Converts the number to string
 */
CLEVER_TYPE_METHOD(Integer::toString) {
	retval->setString(CSTRING(value->toString()));
}

void Integer::init() {
	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Integer::constructor, CLEVER_INT));
	
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&Integer::constructor, CLEVER_INT))
			->addArg("value", CLEVER_INT)
	);

	addMethod(new Method("toString", (MethodPtr)&Integer::toString, CLEVER_STR));
}

DataValue* Integer::allocateValue() const {
	return NULL;
}

} // clever
