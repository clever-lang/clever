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
#include "modules/std/core/function.h"
#include "core/modmanager.h"
#include "modules/std/io/io.h"

namespace clever { namespace modules { namespace std {

namespace io {

CMutex g_io_mutex;
// flush(void)
// Flushes output buffer (forcefully)
static CLEVER_FUNCTION(flush)
{
	if (!clever_static_check_no_args()) {
		return;
	}
	g_io_mutex.lock();
	::fflush(stdout);
	g_io_mutex.unlock();
}

// print(object a, [ ...])
// Prints the object values without trailing newline
static CLEVER_FUNCTION(print)
{
	g_io_mutex.lock();
	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
	}
	g_io_mutex.unlock();
}

// println(object a, [ ...])
// Prints the object values with trailing newline
static CLEVER_FUNCTION(println)
{
	g_io_mutex.lock();
	for (size_t i = 0, size = args.size(); i < size; ++i) {
		args[i]->dump();
		::std::cout << '\n';
	}
	g_io_mutex.unlock();
}

// printf(string format, [...])
// Prints and formats a string to standard output without trailing newline
static CLEVER_FUNCTION(printf)
{
	g_io_mutex.lock();
	const CString* format = args[0]->getStr();
	const char* start = format->c_str();

	for (const char* point = start; point < (start + format->size());) {
		if (*point && (*point == (char)'\\')) {
			unsigned long arg;
			char* skip;

			if ((arg=::std::strtoul(++point, &skip, 10))) {
				if (args.size() > arg) {
					args[arg]->dump();
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
	g_io_mutex.unlock();
}

// read()
// Reads the next string from the standard stream
static CLEVER_FUNCTION(read)
{
	// TODO(murilov): Trigger error/exception
	if (!clever_static_check_no_args()) {
		return;
	}

	::std::string var;
	::std::cin >> var;

	result->setStr(new StrObject(var));
}

// readi()
// Reads the next integer from the standard stream
static CLEVER_FUNCTION(readi)
{
	// TODO(murilov): Trigger error/exception
	if (!clever_static_check_no_args()) {
		return;
	}

	long var;
	::std::cin >> var;

	result->setInt(var);
}

// readd()
// Reads the next double from the standard stream
static CLEVER_FUNCTION(readd)
{
	// TODO(murilov): Trigger error/exception
	if (!clever_static_check_no_args()) {
		return;
	}

	double var;
	::std::cin >> var;

	result->setDouble(var);
}

} // clever::modules::std::io

/// Initializes Standard module
CLEVER_MODULE_INIT(IOModule)
{
	addFunction(new Function("print", &CLEVER_NS_FNAME(io, print)))
		->setVariadic();

	addFunction(new Function("println", &CLEVER_NS_FNAME(io, println)))
		->setVariadic();

	addFunction(new Function("printf", &CLEVER_NS_FNAME(io, printf)))
		->setVariadic();

	addFunction(new Function("flush", &CLEVER_NS_FNAME(io, flush)));

	addFunction(new Function("read", &CLEVER_NS_FNAME(io, read)));

	addFunction(new Function("readi", &CLEVER_NS_FNAME(io, readi)));

	addFunction(new Function("readd", &CLEVER_NS_FNAME(io, readd)));
}

}}} // clever::modules::std
