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

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H
#include <string>
#include <stack>
#include "parser.hh"
#include "compiler.h"

namespace clever {
class ScannerState;
}

// Scanner prototype
clever::Parser::token_type yylex(clever::Parser::semantic_type*,
		clever::Parser::location_type*, clever::Driver&,
		clever::ScannerState*);

namespace clever {

class Driver {
public:
	Driver() : m_is_file(false), m_trace_parsing(false) { }
	virtual ~Driver() { }

	// Read file to the scanner
	void readFile(void);

	// Run the parser
	int parseStr(const std::string&);
	int parseFile(const std::string&);

	// Error handling
	void error(const clever::location&, const std::string&) const;
	void error(const std::string&) const;

	typedef std::stack<clever::ScannerState*> ScannerStack;

	// Indicates if it's a file is being parsed
	bool m_is_file;
	// The file path -f
	std::string m_file;
	// The source
	std::string m_source;
	// The source as input -r
	std::string m_input;
	// Debug option
	bool m_trace_parsing;
	// Scanners stack
	static ScannerStack m_scanners;
	// Compiler
	Compiler compiler;
};

class Interpreter : public Driver {
public:
	Interpreter() { }

	void execute(void);
	void shutdown(void);
};

} // clever

#endif // CLEVER_DRIVER_H
