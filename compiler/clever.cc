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

#include <cstdio>
#include <cstdlib>
#include "compiler/clever.h"
#include "compiler/value.h"

namespace clever {

/**
 * Errors and stuff.
 */
#ifdef CLEVER_DEBUG
void clever_assert_(const char* file, long line, const char* expr,
		int hypothesis, const char* format, ...) throw() {
	va_list vl;
	std::ostringstream out;

	if (!hypothesis) {
		va_start(vl, format);
		printf("clever: assertion '%s' failed at %s line %l.\n\t", expr, file, line);

		vsprintf(out, format, vl);

		va_end(vl);

		std::cerr << out.str() << std::endl;
		std::abort();
	}
}
#endif

void clever_fatal(const char* format, ...) throw() {
	va_list vl;
	va_start(vl, format);
	printf("clever: a fatal error occurred.\n\t");
	vprintfln(format, vl);
	va_end(vl);
	std::abort();
}

/**
 * Formatter
 */
void vsprintf(std::ostringstream& outstr, const char* format, va_list ap) throw() {
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
			/* double */
			case 'd':
				outstr << va_arg(ap, double);
				break;
			/* long */
			case 'l':
				outstr << va_arg(ap, long);
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

void vprintfln(const char* format, va_list args) throw() {
	std::ostringstream out;
	
	vsprintf(out, format, args);

	std::cout << out.str() << std::endl;
}

void printfln(const char* format, ...) throw() {
	va_list args;

	va_start(args, format);

	vprintfln(format, args);

	va_end(args);
}

void sprintf(std::ostringstream& outstr, const char* format, ...) throw() {
	va_list args;

	va_start(args, format);

	vsprintf(outstr, format, args);

	va_end(args);
}

void printf(const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	std::cout << out.str();

	va_end(args);
}

} // clever

