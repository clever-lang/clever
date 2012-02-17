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

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "compiler/clever.h"
#include "compiler/value.h"

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
		printf("clever: Assertion '%s' failed. File: %s Line: %l Function: %s.\n\t", expr, file, line, function);

		vsprintf(out, format, vl);

		va_end(vl);

		std::cerr << out.str() << std::endl;
		std::abort();
	}
}
#endif

/**
 * Throws an error message and abort the VM execution
 */
void clever_error(const char* format, ...) {
	va_list vl;
	va_start(vl, format);
	vprintfln(format, vl);
	va_end(vl);
}

/**
 * Throws a fatal error message and abort the VM execution
 */
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
			/* std::string* */
			case 'S':
				outstr << *va_arg(ap, std::string*);
				break;
			/* const char* */
			case 's':
				outstr << va_arg(ap, const char*);
				break;
			/* Value* */
			case 'v':
				outstr << va_arg(ap, Value*)->toString();
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

} // clever

