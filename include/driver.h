/*
 * Clever language
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
 *
 * $Id$
 */

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H

#include <string>
#include <stack>
#include "parser.hh"
#include "compiler.h"
#include "ast.h"

namespace clever {
class ScannerState;
}

/**
 * Lexer prototype
 */
clever::Parser::token_type yylex(clever::Parser::semantic_type*,
		clever::Parser::location_type*, clever::Driver&,
		clever::ScannerState*);

namespace clever {

/**
 * Driver - Handles the lexer, parser and compiler
 */
class Driver {
public:
	typedef std::stack<ScannerState*> ScannerStack;

	Driver()
		: m_is_file(false), m_trace_parsing(false) { }

	virtual ~Driver() { }

	/* Initializes the compiler with AST nodes */
	void initCompiler(ast::TreeNode* nodes) throw() {
		m_compiler.Init(nodes);
	}

	/* Returns the parsed file */
	std::string& get_file() throw() {
		return m_file;
	}

	/* Read file to the scanner */
	void readFile() throw();

	/* Run the parser */
	int parseStr(const std::string&);
	int parseFile(const std::string&);

	/* Error handling */
	void error(const clever::location&, const std::string&) const throw();
	void error(const std::string&) const throw();
protected:
	/* The file path -f */
	std::string m_file;
	/* The source */
	std::string m_source;
	/* The source as input -r */
	std::string m_input;
	/* Compiler */
	Compiler m_compiler;
private:
	/* Indicates if it's a file is being parsed */
	bool m_is_file;
	/* Debug option */
	bool m_trace_parsing;
	/* Scanners stack */
	static ScannerStack s_scanners;

	DISALLOW_COPY_AND_ASSIGN(Driver);
};

/**
 * Interpreter
 */
class Interpreter : public Driver {
public:
	Interpreter() { }

	void execute();
	void shutdown();
private:
	DISALLOW_COPY_AND_ASSIGN(Interpreter);
};

} // clever

#endif // CLEVER_DRIVER_H
