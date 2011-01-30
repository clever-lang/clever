/*
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
 *
 * $Id$
 */

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <cstdarg>
#include <stack>
#include <sstream>
#include "value.h"
#include "module.h"
#include "pkgmanager.h"
#include "vm.h"
#include "ssa.h"
#include "opcode.h"
#include "location.hh"
#include "astvisitor.h"

namespace clever { namespace ast {

class ASTNode;
class CodeGenVisitor;

}} // clever::ast

namespace clever {

class Compiler {
public:
	Compiler()
		: m_ast(NULL) { }

	~Compiler();

	/**
	 * Initializes compiler data
	 */
	void Init() throw();
	/**
	 * Sets the AST tree to be compiled into intermediate representation
	 */
	void set_ast(ast::ASTNode* ast) throw() { m_ast = ast; }
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
	OpcodeList& getOpcodes() throw() { return m_cgvisitor.get_opcodes(); }
	/**
	 * Displays an error message and exits
	 */
	static void error(std::string, const location&) throw();
	/**
	 * Checks if the supplied value pointers are compatibles
	 */
	static bool checkCompatibleTypes(Value*, Value*) throw();
	/**
	 * Performs a constant folding and constant propagation optimization
	 */
	static Value* constantFolding(int, Value*, Value*) throw();
	/**
	 * Import a package
	 */
	static void import(const CString* package) throw() {
		s_pkgmanager.loadPackage(package);
	}
	/**
	 * Import a package module
	 */
	static void import(const CString* package, const CString* module) throw() {
		s_pkgmanager.loadModule(package, module);
	}
	/**
	 * Returns the reference to static member function table
	 */
	static FunctionTable& get_functions() throw() {
		return s_func_table;
	}
	/**
	 * Checks if a function exists
	 */
	static bool functionExists(const std::string& name) throw() {
		return s_func_table.find(name) != s_func_table.end();
	}
	/**
	 * Returns the a Function pointer
	 */
	static const Function* getFunction(const std::string& name) throw() {
		FunctionTable::const_iterator it = s_func_table.find(name);

		if (it != s_func_table.end()) {
			return it->second;
		} else {
			return NULL;
		}
	}
	/**
	 * Adds a new function into the global function table
	 */
	static void addFunction(const std::string& name, Function* func) throw() {
		s_func_table.insert(FunctionPair(name, func));
	}
	/**
	 * Checks function arguments
	 */
	static void checkFunctionArgs(const Function*, int, const location&) throw();
	/**
	 * Methods for formatted messages
	 */
	static void vsprintf(std::ostringstream&, const char*, va_list) throw();
	static void sprintf(std::ostringstream&, const char*, ...) throw();
	static void printf(const char*, ...) throw();
	static void printfln(const char*, ...) throw();
	static void errorf(const location&, const char*, ...) throw();
private:
	ast::ASTNode* m_ast;
	ast::CodeGenVisitor m_cgvisitor;

	static PackageManager s_pkgmanager;
	static FunctionTable s_func_table;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
