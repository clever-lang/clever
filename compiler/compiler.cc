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

#include <cstdlib>
#include <cstdarg>
#include <vector>
#include "compiler/clever.h"
#include "compiler/compiler.h"
#include "compiler/symboltable.h"
#include "interpreter/ast.h"
#include "types/nativetypes.h"
#include "interpreter/astvisitor.h"

namespace clever {

PackageManager g_pkgmanager;

THREAD_TLS Type* CLEVER_INT_VAR    = NULL;
THREAD_TLS Type* CLEVER_DOUBLE_VAR = NULL;
THREAD_TLS Type* CLEVER_STR_VAR    = NULL;
THREAD_TLS Type* CLEVER_BOOL_VAR   = NULL;
THREAD_TLS Type* CLEVER_BYTE_VAR   = NULL;
THREAD_TLS Type* CLEVER_ARRAY_VAR  = NULL;

Compiler::Error Compiler::m_error_level = Compiler::ALL;
std::ostream& Compiler::m_error_stream  = std::cout;

/**
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	if (m_initialized) {
		g_symtable.endScope();
		g_pkgmanager.shutdown();
	}

	if (m_ast) {
		delete m_ast;
	}
}

/**
 * Initializes the compiler data
 */
void Compiler::init() throw() {
	/* Load package list */
	g_pkgmanager.init();

	g_symtable.beginScope();

	/* Load the primitive data types */
	loadNativeTypes();

	m_initialized = true;
}

/**
 * Loads the class representations of native types
 */
void Compiler::loadNativeTypes() throw() {
	CLEVER_INT    = new Integer;
	CLEVER_STR    = new String;
	CLEVER_DOUBLE = new Double;
	CLEVER_BOOL   = new Bool;
	CLEVER_BYTE   = new Char;
	CLEVER_ARRAY  = new Array; // Virtual Array

	/**
	 * Registers all native types
	 */
	g_symtable.push(CSTRING("Int"), CLEVER_INT);
	g_symtable.push(CSTRING("Double"), CLEVER_DOUBLE);
	g_symtable.push(CSTRING("String"), CLEVER_STR);
	g_symtable.push(CSTRING("Bool"), CLEVER_BOOL);
	g_symtable.push(CSTRING("Byte"), CLEVER_BYTE);
	g_symtable.push(CSTRING("Array"), CLEVER_ARRAY);

	CLEVER_INT->init();
	CLEVER_DOUBLE->init();
	CLEVER_STR->init();
	CLEVER_BOOL->init();
	CLEVER_BYTE->init();
	CLEVER_ARRAY->init();
}

/**
 * Collects all opcode
 */
void Compiler::buildIR() throw() {
	m_cgvisitor.init();

	m_ast->accept(m_tcvisitor);
	m_ast->accept(m_cgvisitor);

	m_cgvisitor.shutdown();

	if (m_cgvisitor.isOpcodeDump()) {
		dumpOpcodes();
	}

	m_ast->clear();
}

void Compiler::dumpOpcodes() throw() {
	const OpcodeList& opcodes = m_cgvisitor.getOpcodes();
	size_t i = 0, size = opcodes.size();

	while (i < size) {
		opcodes[i]->dump();
		++i;
	}
}

/**
 * Displays an error message
 */
void Compiler::error(std::string message, const location& loc) throw() {
	if (loc.begin.filename) {
		m_error_stream << "Compile error: " << message << " on "
			<< *loc.begin.filename << " line " << loc.begin.line << "\n";
	} else {
		m_error_stream << "Compile error: " << message << " on line "
			<< loc.begin.line << "\n";
	}

	exit(1);
}

void Compiler::error(std::string message) throw() {
	m_error_stream << "Compile error: " << message << "\n";
	exit(1);
}


void Compiler::errorf(const location& loc, const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	error(out.str(), loc);
}

void Compiler::warning(std::string message) throw() {
	if (!(m_error_level & Compiler::WARNING)) {
		return;
	}

	m_error_stream << "Warning: " << message << "\n";
}

void Compiler::warningf(const char* format, ...) throw() {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	warning(out.str());
}

} // clever
