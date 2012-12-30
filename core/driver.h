/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DRIVER_H
#define CLEVER_DRIVER_H

#include <stack>
#include "core/compiler.h"
#include "core/parser.hh"

namespace clever { namespace ast {

class ASTNode;

}} // clever::ast

namespace clever {

class ScannerState;

// Lexer prototype
Parser::token_type yylex(Parser::semantic_type*,
		Parser::location_type*, Driver&,
		ScannerState&);

/// Driver - Handles the lexer, parser and compiler
class Driver {
public:
	typedef std::stack<ScannerState*> ScannerStack;

	Driver()
		: m_is_file(false), m_trace_parsing(false), m_file(NULL)
#ifdef CLEVER_DEBUG
			, m_dump_opcode(false)
#endif
		 {}

	virtual ~Driver() {}

	// Returns the parsed file
	CString* getFile() const {
		return const_cast<CString*>(m_file);
	}

	// Read file to the scanner
	void readFile(std::string&) const;

	// Starts the parser and loads the Symbol table
	int loadStr(const std::string&, bool importStd);
	int loadFile(const std::string&);

	// Error handling
	void error(const location&, const std::string&) const;
	void error(const std::string&) const;

	// Executes the script
	virtual void execute(bool) = 0;

	// Tracing
	void setTraceParsing(bool trace) { m_trace_parsing = trace; }
protected:
	// Indicates if it's a file is being parsed
	bool m_is_file;

	// Debug option
	bool m_trace_parsing;

	// The file path -f
	const CString* m_file;

#ifdef CLEVER_DEBUG
	// Opcode dumping option
	bool m_dump_opcode;
#endif

	// Compiler
	Compiler m_compiler;

	// Scanners stack
	ScannerStack m_scanners;
private:
	DISALLOW_COPY_AND_ASSIGN(Driver);
};

/// Interpreter
class Interpreter : public Driver {
public:
	Interpreter(int* argc, char*** argv);

#ifdef CLEVER_DEBUG
	void setDebug() { m_dump_opcode = true; }
#endif
	void execute(bool interactive);
	void shutdown();
private:
	DISALLOW_COPY_AND_ASSIGN(Interpreter);
};

} // clever

#endif // CLEVER_DRIVER_H
