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
#include "compiler/value.h"
#include "compiler/symboltable.h"
#include "modules/std/io/io.h"

namespace clever { namespace packages { namespace std {

namespace io {
/**
 * println(object a, [ ...])
 * Prints the object values without trailing newline
 */
static CLEVER_FUNCTION(print) {
	for (int i = 0, size = args->size(); i < size; ++i) {
		::std::cout << args->at(i)->toString();
	}
}

/**
 * println(object a, [ ...])
 * Prints the object values with trailing newline
 */
static CLEVER_FUNCTION(println) {
	for (int i = 0, size = args->size(); i < size; ++i) {
		::std::cout << args->at(i)->toString() << ::std::endl;
	}
}

/**
 * readln()
 * Reads a line from the standard input.
 */
static CLEVER_FUNCTION(readln) {
	::std::string buffer;

	getline(::std::cin, buffer);
	
	retval->setString(CSTRING(buffer));
	retval->setType(Value::STRING);
}

} // namespace io

/**
 * Initializes Standard module
 */
void IOModule::init() throw() {
	const Type* string_type = CLEVER_TYPE("String");
	
	using namespace io;
	addFunction(new Function("print", &CLEVER_FUNC_NAME(print), -1));
	addFunction(new Function("println", &CLEVER_FUNC_NAME(println), -1));
	addFunction(new Function("readln", &CLEVER_FUNC_NAME(readln), string_type));
}

}}} // clever::packages::std
