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

// print(object a, [ ...])
// Prints the object values without trailing newline
static CLEVER_FUNCTION(print) {
	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
	}
}

// println(object a, [ ...])
// Prints the object values with trailing newline
static CLEVER_FUNCTION(println) {
	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
		::std::cout << '\n';
	}
}

// printf(string format, [...])
// Prints and formats a string to standard output without trailing newline
static CLEVER_FUNCTION(printf) {
	const CString* format = args[0]->getStr();
	if (format) {
		const char* delim = "{}";
		char* tokenize = new char[format->size() + 1];
		::std::strcpy(tokenize, format->c_str());	
#ifndef _WIN32
		char* tokenized;
		char* point = strtok_r(tokenize, delim, &tokenized);
#else
		char* point = strtok(tokenize, delim);
#endif
		if (point) {
			do {
				unsigned int arg = atoi(point);
				if (arg) {
					if (args.size() > arg) {
						args[arg]->dump();
					}
				} 
				else {
					::std::cout << point;
				}
#ifndef _WIN32
			} while((point = strtok_r(NULL, delim, &tokenized)));
#else
			} while((point = strtok(NULL, delim)));
#endif
		}
	
		delete[] tokenize;
	}
}

} // clever::packages::std::io

/// Initializes Standard module
CLEVER_MODULE_INIT(IOModule) {
	using namespace io;
	
	BEGIN_DECLARE_FUNCTION();

	addFunction(new Function("print",       &CLEVER_FUNC_NAME(print)));
	addFunction(new Function("println",     &CLEVER_FUNC_NAME(println)));
	addFunction(new Function("printf",		&CLEVER_FUNC_NAME(printf)));
	END_DECLARE();
}

}}} // clever::packages::std
