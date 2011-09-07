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

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <cstdarg>
#include <stack>
#include <sstream>
#include "module.h"
#include "pkgmanager.h"
#include "vm/vm.h"
#include "vm/opcode.h"
#include "build/location.hh"
#include "interpreter/ast.h"
#include "compiler/cgvisitor.h"
#include "compiler/typechecker.h"

namespace clever {

class Compiler {
public:
	Compiler()
		: m_ast(NULL) { }

	~Compiler();

	/**
	 * Initializes compiler data
	 */
	void init() throw();
	/**
	 * Sets the AST tree to be compiled into intermediate representation
	 */
	void setAST(ast::ASTNode* ast) throw() { m_ast = ast; }
	/**
	 * Set interactive mode ON
	 */
	void setInteractive() throw() { m_cgvisitor.setInteractive(); }
	/**
	 * Loads primitive data types
	 */
	void loadTypes() throw();
	/**
	 * Generates the intermediate representation
	 */
	void buildIR() throw();
	/**
	 * Returns the collected opcodes
	 */
	OpcodeList& getOpcodes() throw() { return m_cgvisitor.getOpcodes(); }
	/**
	 * Displays an error message and exits
	 */
	static void error(std::string) throw();
	static void error(std::string, const location&) throw();

	/**
	 * Import a package
	 */
	static void import(Scope* scope, const CString* package) throw() {
		s_pkgmanager.loadPackage(scope, package);
	}
	/**
	 * Import a package module
	 */
	static void import(Scope* scope, const CString* package, const CString* module) throw() {
		if (module) {
			s_pkgmanager.loadModule(scope, package, module);
		} else {
			s_pkgmanager.loadPackage(scope, package);
		}
	}

	/**
	 * Methods for formatted messages
	 */
	static void errorf(const location&, const char*, ...) throw();
private:
	ast::ASTNode* m_ast;
	ast::CodeGenVisitor m_cgvisitor;
	ast::TypeChecker m_tcvisitor;

	static PackageManager s_pkgmanager;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
