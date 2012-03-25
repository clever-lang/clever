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

#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/file/glob.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace file {

/**
 * Glob::Glob(String pattern)
 */
CLEVER_METHOD(Glob::constructor) {
}

/**
 * Glob::toString()
 * A representation of this class as a string
 */
CLEVER_METHOD(Glob::toString) {
	CLEVER_RETURN_STR(CSTRINGT("Glob class"));
}

void Glob::init() {
	const Type* glob = CLEVER_TYPE("Glob");

	addMethod(
		(new Method(CLEVER_CTOR_NAME, &Glob::constructor, glob))
			->addArg("pattern", CLEVER_STR)
	);

	addMethod(new Method("toString", &Glob::toString, CLEVER_STR));
}

DataValue* Glob::allocateValue() const {
	return new GlobValue;
}

void Glob::destructor(Value* value) const {
}

}}}} // clever::packages::std::file
