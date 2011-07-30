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

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H

#include <stack>
#include "build/parser.hh"
#include "compiler/compiler.h"

namespace clever { namespace ast {

class ASTNode;

}} // clever::ast

namespace clever {

class CString;
class ScannerState;

/**
 * Lexer prototype
 */
clever::Parser::token_type yylex(clever::Parser::semantic_type*,
		clever::Parser::location_type*, clever::Driver&,
		clever::ScannerState&);

/**
 * Driver - Handles the lexer, parser and compiler
 */
class Driver {
public:
	typedef std::stack<ScannerState*> ScannerStack;

	Driver()
		: m_is_file(false), m_trace_parsing(false), m_file(NULL) { }

	virtual ~Driver() { }

	/* Initializes the compiler with AST nodes */
	void initCompiler(ast::ASTNode* nodes) throw() {
		m_compiler.init();
		m_compiler.setAST(nodes);
	}

	/* Returns the parsed file */
	CString* getFile() throw() {
		return const_cast<CString*>(m_file);
	}

	/* Read file to the scanner */
	void readFile() throw();

	/* Run the parser */
	int parseStr(const std::string&, bool importStd);
	int parseFile(const std::string&);

	/* Error handling */
	void error(const clever::location&, const std::string&) const throw();
	void error(const std::string&) const throw();
protected:
	/* Indicates if it's a file is being parsed */
	bool m_is_file;
	/* Debug option */
	bool m_trace_parsing;
	/* The file path -f */
	const CString* m_file;
	/* The source */
	std::string m_source;
	/* The source as input -r */
	std::string m_input;
	/* Compiler */
	Compiler m_compiler;
private:
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

	void execute(bool interactive);
	void shutdown();
private:
	DISALLOW_COPY_AND_ASSIGN(Interpreter);
};

} // clever

#endif // CLEVER_DRIVER_H
