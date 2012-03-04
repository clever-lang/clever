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

#include <sstream>
#include "compiler/cstring.h"
#include "types/type.h"
#include "types/object.h"

namespace clever {


/**
 * Object::Object()
 * Construct an Byte object with a default value (if no args) or a
 * custom value
 */
CLEVER_METHOD(Object::constructor) {
}

/**
 * Object::operator==
 * Return true iff the two Values* have the same pointer
 */
CLEVER_METHOD(Object::equal) {
	CLEVER_RETURN_BOOL(CLEVER_ARG(0) == CLEVER_ARG(1));
}

/**
 * Void Object::__assign__(Object)
 */
CLEVER_METHOD(Object::do_assign) {
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * Object::toString()
 * String representing this object
 */
CLEVER_METHOD(Object::toString) {
	::std::ostringstream oss;
	oss << "[Object id: " << value << "]";

	retval->setString(CSTRINGT(oss.str()));
}

void Object::init() {
	addMethod(new Method(CLEVER_CTOR_NAME, &Object::constructor, CLEVER_OBJECT));

	addMethod((new Method(CLEVER_OPERATOR_EQUAL, &Object::equal, CLEVER_BOOL))
		->addArg("lhs", CLEVER_OBJECT)
		->addArg("rhs", CLEVER_OBJECT)
	);

	addMethod((new Method(CLEVER_OPERATOR_ASSIGN, &Object::do_assign, CLEVER_VOID, false))
		->addArg("rhs", CLEVER_OBJECT)
	);

	addMethod(new Method("toString", &Object::toString, CLEVER_STR));
}

DataValue* Object::allocateValue() const {
	return NULL;
}

} // clever
