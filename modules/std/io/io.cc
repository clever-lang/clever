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

#include <iostream>
#include "compiler/value.h"
#include "modules/std/io/io.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std {

namespace io {
/**
 * println(object a, [ ...])
 * Prints the object values without trailing newline
 */
static CLEVER_FUNCTION(print) {
	for (size_t i = 0, size = CLEVER_NUM_ARGS(); i < size; ++i) {
		::std::cout << CLEVER_ARG_AS_STR(i);
	}
}

/**
 * println(object a, [ ...])
 * Prints the object values with trailing newline
 */
static CLEVER_FUNCTION(println) {
	for (size_t i = 0, size = CLEVER_NUM_ARGS(); i < size; ++i) {
		::std::cout << CLEVER_ARG_AS_STR(i) << ::std::endl;
	}
}

/**
 * readln()
 * Reads a line from the standard input.
 */
static CLEVER_FUNCTION(readln) {
	::std::string buffer;

	getline(::std::cin, buffer);

	CLEVER_RETURN_STR(CSTRINGT(buffer));
}

/**
 * readString()
 * Reads a String from the standard input.
 */
static CLEVER_FUNCTION(readString) {
	::std::string buffer;
	::std::cin >> buffer;

	CLEVER_RETURN_STR(CSTRINGT(buffer));
}

/**
 * readInt()
 * Reads an Int from the standard input.
 */
static CLEVER_FUNCTION(readInt) {
	int64_t buffer;
	::std::cin >> buffer;

	CLEVER_RETURN_INT(buffer);
}

/**
 * readDouble()
 * Reads a Double from the standard input.
 */
static CLEVER_FUNCTION(readDouble) {
	double buffer;
	::std::cin >> buffer;

	CLEVER_RETURN_DOUBLE(buffer);
}

} // namespace io

/**
 * Initializes Standard module
 */
void IOModule::init() {
	using namespace io;

	addFunction(new Function("print", &CLEVER_FUNC_NAME(print), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(1);

	addFunction(new Function("println", &CLEVER_FUNC_NAME(println), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(1);

	addFunction(new Function("readln", &CLEVER_FUNC_NAME(readln), CLEVER_STR));

	addFunction(new Function("readString", &CLEVER_FUNC_NAME(readString), CLEVER_STR));
	addFunction(new Function("readInt", &CLEVER_FUNC_NAME(readInt), CLEVER_INT));
	addFunction(new Function("readDouble", &CLEVER_FUNC_NAME(readDouble), CLEVER_DOUBLE));
}

}}} // clever::packages::std
