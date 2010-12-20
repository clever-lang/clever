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
#include "parser.hpp"

namespace Clever {
class ScannerState;
}

// Scanner prototype
Clever::Parser::token_type yylex(Clever::Parser::semantic_type*,
		Clever::Parser::location_type*, Clever::Driver&,
		Clever::ScannerState*);

namespace Clever {
	
class Driver {
public:
	// Compiler pointer
	//Clever::Compiler* compiler_p;
	// Indicates if it's a file is being parsed
	bool is_file;
	// The file path -f
	std::string file;
	// The source
	std::string source;
	// The source as input -r
	std::string input;
	// Debug option
	bool trace_parsing;
	// Scanners stack
	static std::stack<Clever::ScannerState*> scanners;

	Driver() : is_file(false), trace_parsing(false) { }
	virtual ~Driver() { }
	
	// Read file to the scanner
	void read_file(void);

	// Run the parser
	int parse_str(const std::string&);
	int parse_file(const std::string&);

	// Error handling
	void error(const Clever::location&, const std::string&) const;
	void error(const std::string&) const;
};

class Interpreter : public Driver {
public:
	void execute(void);
	void shutdown(void);
};

} // Clever

#endif // CLEVER_DRIVER_H
