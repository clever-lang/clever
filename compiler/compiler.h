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

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <cstdarg>
#include <stack>
#include <sstream>
#include "pkgmanager.h"
#include "build/interpreter/location.hh"
#include "compiler/cgvisitor.h"
#include "compiler/typechecker.h"

namespace clever { namespace ast {
class ASTNode;
}} // clever::ast

namespace clever {

class Driver;

class Compiler {
public:
	enum Error {
		ERROR   = 0x1,
		WARNING = 0x2,
		NOTICE  = 0x4,
		ALL     = ERROR | WARNING | NOTICE
	};

	Compiler()
		: m_ast(NULL), m_initialized(false) { }

	~Compiler();

	/**
	 * Initializes compiler data
	 */
	void init();
	/**
	 * Sets the AST tree to be compiled into intermediate representation
	 */
	void setAST(ast::ASTNode* ast) { m_ast = ast; }

	ast::ASTNode* getAST() const { return m_ast; }
	/**
	 * Set interactive mode ON
	 */
	void setInteractive() { m_cgvisitor.setInteractive(); }
	/**
	 * Set opcode dumper mode ON
	 */
	void setOpcodeDump() { m_cgvisitor.setOpcodeDump(); }
	/**
	 * Loads native data types
	 */
	void loadNativeTypes();
	/**
	 * Generates the intermediate representation
	 */
	void buildIR();
	/**
	 * Returns the collected opcodes
	 */
	OpcodeList& getOpcodes() { return m_cgvisitor.getOpcodes(); }
	/**
	 * Dumps the opcodes
	 */
	void dumpOpcodes();

	/**
	 * Displays an error message and exits
	 */
	static void error(std::string) CLEVER_NO_RETURN;
	static void error(std::string, const location&) CLEVER_NO_RETURN;

	/**
	 * Displays an warning message
	 */
	static void warning(std::string);

	/**
	 * Import a package
	 */
	static void import(Scope* scope, const CString* package) {
		g_pkgmanager.loadPackage(scope, package);
	}
	/**
	 * Import a package module
	 */
	static void import(Scope* scope, const CString* package, const CString* module, const CString* alias) {
		if (module) {
			g_pkgmanager.loadModule(scope, package, module, alias);
		} else {
			g_pkgmanager.loadPackage(scope, package);
		}
	}
	/**
	 * Import a file
	 */
	ast::BlockNode* importFile(Driver&, const CString*, const CString*);

	/**
	 * Methods for formatted messages
	 */
	static void errorf(const location&, const char*, ...);
	static void warningf(const char*, ...);

	static void setErrorReporting(Error level) {
		m_error_level = level;
	}
private:
	ast::ASTNode* m_ast;
	ast::CodeGenVisitor m_cgvisitor;
	ast::TypeChecker m_tcvisitor;

	bool m_initialized;
	static Error m_error_level;
	static std::ostream& m_error_stream;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
