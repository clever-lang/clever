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

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H

#include <stack>
#include "compiler/compiler.h"
#include "interpreter/parser.hh"

namespace clever { namespace ast {

class ASTNode;

}} // clever::ast

namespace clever {

class CString;
class ScannerState;

/**
 * Lexer prototype
 */
Parser::token_type yylex(Parser::semantic_type*,
		Parser::location_type*, Driver&,
		ScannerState&);

/**
 * Driver - Handles the lexer, parser and compiler
 */
class Driver {
public:
	typedef std::stack<ScannerState*> ScannerStack;

	Driver()
		: m_is_file(false), m_trace_parsing(false), m_file(NULL) {}

	virtual ~Driver() {}

	/* Returns the parsed file */
	CString* getFile() const {
		return const_cast<CString*>(m_file);
	}

	/* Read file to the scanner */
	void readFile(std::string&) const;

	/* Starts the parser and loads the Symbol table */
	int loadStr(const std::string&, bool importStd);
	int loadFile(const std::string&);

	/* Error handling */
	void error(const location&, const std::string&) const;
	void error(const std::string&) const;

	/* Executes the script */
	virtual void execute(bool) = 0;

	/* Tracing */
	void setTraceParsing(bool trace) { m_trace_parsing = trace; }
protected:
	/* Indicates if it's a file is being parsed */
	bool m_is_file;

	/* Debug option */
	bool m_trace_parsing;

	/* The file path -f */
	const CString* m_file;

	/* Compiler */
	Compiler m_compiler;

	/* Scanners stack */
	ScannerStack m_scanners;
private:
	DISALLOW_COPY_AND_ASSIGN(Driver);
};

/**
 * Interpreter
 */
class Interpreter : public Driver {
public:
	Interpreter(int* argc, char*** argv);

	void execute(bool interactive);
	void shutdown() {}
private:
	DISALLOW_COPY_AND_ASSIGN(Interpreter);
};

} // clever

#endif // CLEVER_DRIVER_H
