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
#include "types/bool.h"
#include "types/nativetypes.h"

namespace clever {


/**
 * Bool::Bool([Bool value])
 * Construct an Bool object with a default value (if no args) or a 
 * custom value
 */
CLEVER_TYPE_METHOD(Bool::constructor) {
	if (args) {
		retval->setBoolean(args->at(0)->getBoolean());
	}
	else {
		retval->setBoolean(0);
	}
}

/**
 * Bool::toString()
 * Converts the number to string
 */
CLEVER_TYPE_METHOD(Bool::toString) {
	retval->setString(CSTRING(value->toString()));
}

void Bool::init() {
	addMethod(new Method("toString", (MethodPtr)&Bool::toString, 
			makeArgs(NULL), CLEVER_STR));
}

DataValue* Bool::allocateValue() const {
	return NULL;
}

} // clever
