/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
#include <cstdio>
#include <cmath>
#include "module.h"
#include "std/std.h"

namespace clever {

Module* g_std_module = new StdModule;

/**
 * println(object a, [ ...])
 * Prints the object values without trailing newline
 */
static CLEVER_FUNCTION(print) {
	std::ios::sync_with_stdio(false);

	for (int i = 0, size = args.size(); i < size; ++i) {
		std::cout << args.at(i)->toString();
	}
}

/**
 * println(object a, [ ...])
 * Prints the object values with trailing newline
 */
static CLEVER_FUNCTION(println) {
	for (int i = 0, size = args.size(); i < size; ++i) {
		printf("%s\n", args.at(i)->toString().c_str());
	}
}

/**
 * sqrt(double x)
 * Returns the square root of a number x
 */
static CLEVER_FUNCTION(sqrt) {
	retval->setDouble(std::sqrt(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/*
 * Initializes Standard module
 */
void StdModule::Init() throw() {
	/* Module functions */
	addFunction(new Function("print",   &CLEVER_FUNC_NAME(print)));
	addFunction(new Function("println", &CLEVER_FUNC_NAME(println)));
	addFunction(new Function("sqrt",    &CLEVER_FUNC_NAME(sqrt)));
}

} // clever