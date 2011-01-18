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

#include <boost/unordered_map.hpp>
#include "ast.h"
#include "irbuilder.h"
#include "module.h"
#include "typetable.h"

namespace clever {

/**
 * Function table
 */
typedef boost::unordered_map<const std::string, Function*> FunctionTable;

class Compiler {
public:
	Compiler() { }

	~Compiler();

	void Init(ast::TreeNode*) throw();
	void loadTypes() throw();
	void loadModules() throw();
	void buildIR() throw();

	/**
	 * Returns the reference to static member function table
	 */
	FunctionTable& get_functions() const throw() {
		return s_func_table;
	}
	/**
	 * Returns the pointer to opcode vector
	 */
	VM::OpcodeList* getOpcodes() {
		return m_builder.get_opcodes();
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
	static Function* getFunction(const std::string& name) throw() {
		return s_func_table.find(name)->second;
	}
	/**
	 * Displays the error message and exits the program
	 */
	static void error(const char*) throw();
	/**
	 * Checks if two operands has compatible types to perform some operation
	 */
	static bool checkCompatibleTypes(Value*, Value*) throw();
	/**
	 * Performs the constant folding and constant propagation optimization
	 */
	static ConstantValue* constantFolding(int, Value*, Value*) throw();
private:
	/* AST nodes */
	ast::TreeNode* m_ast;
	/* IR Builder */
	IRBuilder m_builder;
	/* Module list */
	ModuleList m_modules;
	/* Global function table */
	static FunctionTable s_func_table;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
