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
#include <vector>
#include "compiler/clever.h"
#include "compiler/compiler.h"
#include "interpreter/ast.h"
#include "types/nativetypes.h"
#include "types/type.h"
#include "interpreter/astvisitor.h"
#include "interpreter/driver.h"
#include "interpreter/ast.h"

namespace clever {

PackageManager g_pkgmanager;

Type* CLEVER_INT_VAR    = NULL;
Type* CLEVER_DOUBLE_VAR = NULL;
Type* CLEVER_STR_VAR    = NULL;
Type* CLEVER_BOOL_VAR   = NULL;
Type* CLEVER_BYTE_VAR   = NULL;
Type* CLEVER_ARRAY_VAR  = NULL;
Type* CLEVER_MAP_VAR    = NULL;
Type* CLEVER_OBJ_VAR    = NULL;

#ifndef CLEVER_APPLE
# define CLEVER_ERROR_EXIT_ACTION() longjmp(Compiler::failure, 1)
#else
# define CLEVER_ERROR_EXIT_ACTION() exit(1)
#endif

/**
 * Set the default error level
 */
Compiler::Error Compiler::m_error_level = Compiler::ALL;

/**
 * Set the stream to be used on error message
 */
std::ostream& Compiler::m_error_stream  = std::cout;

jmp_buf Compiler::failure;

/**
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	if (m_initialized) {
		g_pkgmanager.shutdown();
	}

	if (m_ast) {
		delete m_ast;
	}
}

/**
 * Initializes the compiler data
 */
void Compiler::init() {
	if (!m_initialized) {
		/* Load package list */
		g_pkgmanager.init();

		/* Load the primitive data types */
		loadNativeTypes();
	}

	m_initialized = true;
}

/**
 * Shutdown compiler on error
 */
void Compiler::shutdown() {
	m_cgvisitor.shutdown();
	m_ast->clear();
}

/**
 * Loads the class representations of native types
 */
void Compiler::loadNativeTypes() {
	CLEVER_OBJECT = new Object;
	CLEVER_INT    = new Integer;
	CLEVER_STR    = new String;
	CLEVER_DOUBLE = new Double;
	CLEVER_BOOL   = new Bool;
	CLEVER_BYTE   = new Char;

	// Virtual Standard Template Types
	CLEVER_ARRAY  = new Array;
	CLEVER_MAP    = new Map;
	Type* pair    = new Pair;

	// Registers all native data types
	g_scope.pushType(CSTRING("Object"), CLEVER_OBJECT);
	g_scope.pushType(CSTRING("Int"),    CLEVER_INT);
	g_scope.pushType(CSTRING("Double"), CLEVER_DOUBLE);
	g_scope.pushType(CSTRING("String"), CLEVER_STR);
	g_scope.pushType(CSTRING("Bool"),   CLEVER_BOOL);
	g_scope.pushType(CSTRING("Byte"),   CLEVER_BYTE);
	g_scope.pushType(CSTRING("Array"),  CLEVER_ARRAY);
	g_scope.pushType(CSTRING("Map"),    CLEVER_MAP);
	g_scope.pushType(CSTRING("Pair"),   pair);

	init_type_cached_ptrs();

	// Initialize native data types
	CLEVER_INT->init();
	CLEVER_DOUBLE->init();
	CLEVER_STR->init();
	CLEVER_BOOL->init();
	CLEVER_BYTE->init();
	CLEVER_ARRAY->init();
	CLEVER_MAP->init();
	CLEVER_OBJECT->init();
	pair->init();
}

/**
 * Make the visitor traverse accross the AST tree, doing the
 * typechecking, and generating the intermediate representation.
 * On error, Compiler::shutdown() will be called via longjmp.
 */
void Compiler::buildIR() {
	m_cgvisitor.init();

	// Make the visitor traverse accross the AST tree
	m_ast->acceptVisitor(m_tcvisitor);
	m_ast->acceptVisitor(m_cgvisitor);

	m_cgvisitor.shutdown();

	// If used -d option in command-line, display the generated opcodes
	if (m_cgvisitor.isOpcodeDump()) {
		dumpOpcodes();
	}

	m_ast->clear();
}

/**
 * Direct the driver to parser a new file and return its AST tree
 * to be appended to the main tree
 */
ast::UnscopedBlockNode* Compiler::importFile(Driver& driver, const CString* file,
	ast::Identifier* alias) {

	driver.parseFile(file->str());

	return new ast::UnscopedBlockNode(alias, static_cast<ast::BlockNode*>(getAST()));
}

void Compiler::dumpOpcodes() {
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
void Compiler::error(const std::string& message, const location& loc) {
	if (loc.begin.filename) {
		m_error_stream << "Compile error: " << message << " on "
			<< *loc.begin.filename << " line " << loc.begin.line << "\n";
	} else {
		m_error_stream << "Compile error: " << message << " on line "
			<< loc.begin.line << "\n";
	}
}

/**
 * Displays an error message and abort the compilation
 */
void Compiler::error(const std::string& message) {
	m_error_stream << "Compile error: " << message << "\n";

	// Abort the compilation
	CLEVER_ERROR_EXIT_ACTION();
}

/**
 * Displays a formatted error message and abort the compilation
 */
void Compiler::errorf(const location& loc, const char* format, ...) {
	std::ostringstream* out = new std::ostringstream;
	va_list args;

	va_start(args, format);

	vsprintf(*out, format, args);

	va_end(args);

	error(out->str(), loc);

	delete out;

	// Abort the compilation
	CLEVER_ERROR_EXIT_ACTION();
}

/**
 * Displays an warning message
 */
void Compiler::warning(const std::string& message) {
	if (!(m_error_level & Compiler::WARNING)) {
		return;
	}

	m_error_stream << "Warning: " << message << "\n";
}

/**
 * Displays a formatted warning message
 */
void Compiler::warningf(const char* format, ...) {
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	warning(out.str());
}

} // clever
