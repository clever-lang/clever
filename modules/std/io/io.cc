/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
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
	::fflush(stdout);
}

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
	if (!args.size()) {
		return;
	}
	// TODO(Felipe): add a way to use check_args with variadic functions

	const CString* format = args[0]->getStr();
	const char* start = format->c_str();

	for (const char* point = start; point < (start + format->size());) {
		if (*point && (*point == (char)'\\')) {
			unsigned long arg;
			char* skip;

			if ((arg=::std::strtoul(++point, &skip, 10))) {
				if (CLEVER_ARG_COUNT() > arg) {
					CLEVER_ARG_DUMP(arg);
				}
				point = skip;
			} else {
				::std::cout << *(--point);
				point++;
			}
		} else {
			::std::cout << *point;
			point++;
		}
	}
}

} // clever::packages::std::io

/// Initializes Standard module
CLEVER_MODULE_INIT(IOModule)
{
	using namespace io;

	addFunction(new Function("print",   &CLEVER_NS_FNAME(io, print)));
	addFunction(new Function("println", &CLEVER_NS_FNAME(io, println)));
	addFunction(new Function("printf",  &CLEVER_NS_FNAME(io, printf)));
	addFunction(new Function("flush",   &CLEVER_NS_FNAME(io, flush)));
}

}}} // clever::packages::std
