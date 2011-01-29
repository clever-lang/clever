/*
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
 *
 * $Id$
 */

#include <iostream>
#include "value.h"
#include "module.h"
#include "std/io.h"

namespace clever { namespace std_pkg {

/**
 * println(object a, [ ...])
 * Prints the object values without trailing newline
 */
static CLEVER_FUNCTION(print) {
	for (int i = 0, size = args->size(); i < size; ++i) {
		std::cout << args->at(i)->toString();
	}
}

/**
 * println(object a, [ ...])
 * Prints the object values with trailing newline
 */
static CLEVER_FUNCTION(println) {
	for (int i = 0, size = args->size(); i < size; ++i) {
		std::cout << args->at(i)->toString() << std::endl;
	}
}

/**
 * Initializes Standard module
 */
void IOModule::Init() throw() {
	addFunction(new Function("print", &CLEVER_FUNC_NAME(print), -1));
	addFunction(new Function("println", &CLEVER_FUNC_NAME(println), -1));
}

}} // clever::std_pkg
