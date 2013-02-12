/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "core/clever.h"
#include "core/cstring.h"
#include "core/value.h"
#include "core/cexception.h"

namespace clever {

jmp_buf fatal_error;

/**
 * Errors and stuff.
 */
#ifdef CLEVER_DEBUG
void clever_assert_(const char* file, const char* function, long line, const char* expr,
		int hypothesis, const char* format, ...) {
	va_list vl;
	std::ostringstream out;

	if (!hypothesis) {
		va_start(vl, format);
		::printf("clever: Assertion '%s' failed. File: %s Line: %ld Function: %s.\n\t", expr, file, line, function);

		vsprintf(out, format, vl);

		va_end(vl);

		std::cerr << out.str() << std::endl;
		std::abort();
	}
}

void clever_debug_(const char* file, long line, const char* format, ...) {
	va_list vl;
	std::ostringstream out;

	va_start(vl, format);
	out << "[DEBUG] " << file << ":" << line << ": ";

	vsprintf(out, format, vl);

	va_end(vl);

	std::cerr << out.str() << std::endl;
}
#endif

void clever_error(const char* format, ...) {
	va_list vl;
	va_start(vl, format);
	vprintfln(format, vl);
	va_end(vl);
}

void clever_fatal(const char* format, ...) {
	va_list vl;
	va_start(vl, format);
	vprintfln(format, vl);
	va_end(vl);

	CLEVER_EXIT_FATAL();
}

/**
 * Formatter
 */
void vsprintf(std::ostringstream& outstr, const char* format, va_list ap) {
	char* chr = const_cast<char*>(format);

	if (!chr) {
		return;
	}

	while (*chr) {
		/* Check for escape %% */
		if (*chr != '%' || *++chr == '%') {
			outstr << *chr++;
			continue;
		}

		switch (*chr) {
			/* int */
			case 'i':
				outstr << va_arg(ap, int);
				break;
			/* double */
			case 'd':
				outstr << va_arg(ap, double);
				break;
			/* size_t */
			case 'N':
				outstr << va_arg(ap, size_t);
				break;
			/* int64_t */
			case 'l':
				outstr << va_arg(ap, int64_t);
				break;
			case 'T': {
					const Type* type = va_arg(ap, const Type*);

					if (type) {
						outstr << type->getName();
					} else {
						outstr << "null";
					}
				}
				break;
			/* const CString* */
			case 'S':
				outstr << *va_arg(ap, const CString*);
				break;
			/* const char* */
			case 's':
				outstr << va_arg(ap, const char*);
				break;
			/* Value* */
			case 'v':
				va_arg(ap, Value*)->dump(outstr);
				break;
			/* Address */
			case '@':
				outstr << std::hex << va_arg(ap, void*);
				break;
		}
		++chr;
	}
}

void vprintfln(const char* format, va_list args) {
	std::ostringstream out;

	vsprintf(out, format, args);

	std::cout << out.str() << std::endl;
}

void printfln(const char* format, ...) {
	va_list args;

	va_start(args, format);

	vprintfln(format, args);

	va_end(args);
}

void sprintf(std::ostringstream& outstr, const char* format, ...) {
	va_list args;

	va_start(args, format);

	vsprintf(outstr, format, args);

	va_end(args);
}

void printf(const char* format, ...) {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	std::cout << out.str();

	va_end(args);
}

// Verify a vector of Values conform to a specific set of types (and implicit length)
// Typespec:
//  f - a function
//	s - a string
//	i - a integral number
//	d - a double precision number
//	a - array
//  m - map
//	b - boolean
//	n - numeric
//	c - current object
//  . - any type
//	* - variadic
//  | - optional argument marker
// Example:
//	clever_check_args("sii") - check that the first arg is string and the next
//								two are integers
//	clever_check_args("sdi") - check that the first arg is a string, the second
//								a double and the third an integer
//	clever_check_args("*si") - ignore the first arg, verify the second and third
bool check_args(const ::std::vector<Value*>& args, const char* typespec,
	CException* exception, const Type* type)
{
	size_t argslen = args.size();

	// Void arguments checking
	if (typespec == NULL) {
		if (argslen) {
			exception->setException("No argument is expected");
		}
		return argslen > 0 ? false : true;
	}

	size_t speclen = ::strlen(typespec);

	// Check for different number of arguments for function/method
	if (speclen != argslen) {
		const char *spec;

		if ((spec = strpbrk(typespec, "*|")) == NULL) {
			exception->setException(
				"Wrong number of parameter: %l parameter%s expected, %l given",
				speclen, speclen > 1 ? "s": "", argslen);
			return false;
		} else {
			size_t pos = spec - typespec;

			if (argslen < pos) {
				exception->setException(
					"Wrong number of parameter: at least %l parameter%s expected, %l given",
					pos, pos > 1 ? "s": "", argslen);
				return false;
			}
		}
	}

	for (size_t arg = 0, index = 0; arg < speclen; ++arg, ++index) {
		// Check for optional argument
		if (index >= argslen) {
			return true;
		}

		const Type* const arg_type = args[index]->getType();

		switch (typespec[arg]) {
			// Function
			case 'f':
				if (arg_type != CLEVER_FUNC_TYPE) {
					exception->setException(
						"Argument #%l expects a Function, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// String
			case 's':
				if (arg_type != CLEVER_STR_TYPE) {
					exception->setException(
						"Argument #%l expects a String, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Integer
			case 'i':
				if (arg_type != CLEVER_INT_TYPE) {
					exception->setException(
						"Argument #%l expects an Integer, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Double
			case 'd':
				if (arg_type != CLEVER_DOUBLE_TYPE) {
					exception->setException(
						"Argument #%l expects a Double, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Array
			case 'a':
				if (arg_type != CLEVER_ARRAY_TYPE) {
					exception->setException(
						"Argument #%l expects an Array, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Map
			case 'm':
				if (arg_type != CLEVER_MAP_TYPE) {
					exception->setException(
						"Argument #%l expects a Map, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Boolean
			case 'b':
				if (arg_type != CLEVER_BOOL_TYPE) {
					exception->setException(
						"Argument #%l expects a Boolean, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Number
			case 'n':
				if ((arg_type != CLEVER_DOUBLE_TYPE)
					&& (arg_type != CLEVER_INT_TYPE)) {
					exception->setException(
						"Argument #%l expects a Number, but %T was supplied",
						index+1, arg_type);
					return false;
				}
				break;
			// Current type
			case 'c':
				if (arg_type != type) {
					exception->setException(
						"Argument #%l expects a %s, but %T was supplied",
						index+1, &type->getName(), arg_type);
					return false;
				}
				break;
			// Any type (not null)
			case '.':
				if (arg_type == NULL) {
					exception->setException(
						"Argument #%l expects a non null value, but null was supplied",
						index+1);
					return false;
				}
				break;
			// Var arg
			case '*':
				goto done;
			// Optional argument marker
			case '|':
				--index;
				break;
			default:
				clever_fatal("Wrong type specifier found");
				break;
		}
	}
done:
	return true;
}

} // clever
