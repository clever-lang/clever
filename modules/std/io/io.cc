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
#include "core/cthread.h"
#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/io/io.h"

namespace clever { namespace packages { namespace std {

namespace io {

Mutex io_mutex;

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
		::std::cout << ::std::endl;
	}
}

// safeprint(object a, [ ...])
// Prints the object values without trailing newline [thread safed]
static CLEVER_FUNCTION(safeprint) {
	io_mutex.lock();

	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
	}

	io_mutex.unlock();
}

// safeprintln(object a, [ ...])
// Prints the object values with trailing newline [thread safed]
static CLEVER_FUNCTION(safeprintln) {
	io_mutex.lock();

	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
		::std::cout << ::std::endl;
	}

	io_mutex.unlock();
}


} // namespace io

/// Initializes Standard module
CLEVER_MODULE_INIT(IOModule) {
	using namespace io;

	io_mutex.init();

	BEGIN_DECLARE_FUNCTION();

	addFunction(new Function("safeprint",   &CLEVER_FUNC_NAME(safeprint)));
	addFunction(new Function("safeprintln", &CLEVER_FUNC_NAME(safeprintln)));
	addFunction(new Function("print",       &CLEVER_FUNC_NAME(print)));
	addFunction(new Function("println",     &CLEVER_FUNC_NAME(println)));

	END_DECLARE();
}

}}} // clever::packages::std
