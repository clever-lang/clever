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
#include <cstdio>
#include <cstdlib>
#include "core/cthread.h"
#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/io/io.h"

namespace clever { namespace packages { namespace std {

namespace io {

#define STDIO_DELIM "{}"
#define STDIO_MAXBUF 8096

// flush(void)
// Flushes output buffer (forcefully)
static CLEVER_FUNCTION(flush) {
	fflush(stdout);
}

// print(object a, [ ...])
// Prints the object values without trailing newline
static CLEVER_FUNCTION(print) {
	for (size_t i = 0, size = CARG_COUNT(); i < size; ++i) {
		CARG_DUMP(i);
	}
}

// println(object a, [ ...])
// Prints the object values with trailing newline
static CLEVER_FUNCTION(println) {
	for (size_t i = 0, size = CARG_COUNT(); i < size; ++i) {
		CARG_DUMP(i);
		::std::cout << ::std::endl;
	}
}

// printf(string format, [...])
// Prints and formats a string to standard output without trailing newline
static CLEVER_FUNCTION(printf) {
	if (CARG_COUNT() > 0) {
		char* point = strtok(CARG_PSTR(0), STDIO_DELIM);
		if (point) {
			do {
				unsigned int arg = atoi(point);
				if (arg) {
					if (args.size() > arg) {
						CARG_DUMP(arg);
					}
				} else {
					::std::cout << point;
				}
			} while((point = strtok(NULL, STDIO_DELIM)));
		}
	}
}

} // clever::packages::std::io

/// Initializes Standard module
CLEVER_MODULE_INIT(IOModule) {
	using namespace io;

	BEGIN_DECLARE_FUNCTION();
	addFunction(new Function("print", &CLEVER_FUNC_NAME(print)));
	addFunction(new Function("println", &CLEVER_FUNC_NAME(println)));
	addFunction(new Function("printf", &CLEVER_FUNC_NAME(printf)));
	addFunction(new Function("flush", &CLEVER_FUNC_NAME(flush)));
	END_DECLARE();
}

}}} // clever::packages::std
