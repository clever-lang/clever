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

#include <stack>
#include "value.h"
#include "module.h"
#include "pkgmanager.h"
#include "vm.h"
#include "ssa.h"
#include "opcode.h"

namespace clever { namespace ast {

class Expression;
class BinaryExpression;
class VariableDecl;
class PosIncrement;
class PosDecrement;
class PreIncrement;
class PreDecrement;
class IfExpression;
class ElseIfExpression;
class ElseExpression;
class WhileExpression;
class EndWhileExpression;
class StartExpr;
class LogicExpression;
class FunctionCall;
class MethodCall;
class Assignment;
class Import;
class TreeNode;

typedef std::vector<Expression*> Arguments;

}} // clever::ast

namespace clever {

class Compiler {
public:
	typedef std::stack<Opcode*> Jmp;
	typedef std::stack<Jmp> JmpStack;

	Compiler() { }

	~Compiler();

	void Init(ast::TreeNode*) throw();
	void loadTypes() throw();
	/**
	 * Generates the intermediate representation
	 */
	void buildIR() throw();

	VM::OpcodeList* get_opcodes() throw() {
		return &m_opcodes;
	}

	unsigned int getOpNum() const throw() {
		return m_opcodes.size()-1;
	}

	Value* getValue(ast::Expression*) throw();
	ValueVector* functionArgs(const ast::Arguments*) throw();

	void pushOpcode(Opcode* opcode) throw() {
		m_opcodes.push_back(opcode);
		/**
		 * Sets the opcode number, which is used by JMP opcodes
		 */
		opcode->set_op_num(getOpNum());
	}
	/**
	 * Import a package
	 */
	void import(const CString* package) throw() {
		m_pkgmanager.loadPackage(package);
	}
	/**
	 * Import a package module
	 */
	void import(const CString* package, const CString* module) throw() {
		m_pkgmanager.loadModule(package, module);
	}
	/**
	 * Returns the reference to static member function table
	 */
	FunctionTable& get_functions() const throw() {
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
	static FunctionPtr getFunction(const std::string& name) throw() {
		FunctionTable::const_iterator it = s_func_table.find(name);

		if (it != s_func_table.end()) {
			return it->second;
		} else {
			return NULL;
		}
	}
	/**
	 * Displays the error message and exits the program
	 */
	static void error(std::string) throw();
	/**
	 * Checks if two operands has compatible types to perform some operation
	 */
	static bool checkCompatibleTypes(Value*, Value*) throw();
	/**
	 * Performs the constant folding and constant propagation optimization
	 */
	static ConstantValue* constantFolding(int, Value*, Value*) throw();

	/**
	 * Opcode generators
	 */
	Opcode* binaryExpression(ast::BinaryExpression*) throw();
	Opcode* variableDecl(ast::VariableDecl*) throw();
	Opcode* preIncrement(ast::PreIncrement*) throw();
	Opcode* posIncrement(ast::PosIncrement*) throw();
	Opcode* preDecrement(ast::PreDecrement*) throw();
	Opcode* posDecrement(ast::PosDecrement*) throw();
	Opcode* newBlock() throw();
	Opcode* endBlock() throw();
	Opcode* ifExpression(ast::IfExpression*) throw();
	Opcode* elseIfExpression(ast::ElseIfExpression*) throw();
	Opcode* elseExpression(ast::ElseExpression*) throw();
	Opcode* endIfExpression() throw();
	Opcode* whileExpression(ast::WhileExpression*) throw();
	Opcode* endWhileExpression(ast::EndWhileExpression*) throw();
	Opcode* startExpr(ast::StartExpr*) throw();
	Opcode* logicExpression(ast::LogicExpression*) throw();
	Opcode* breakExpression() throw();
	Opcode* functionCall(ast::FunctionCall*) throw();
	Opcode* methodCall(ast::MethodCall*) throw();
	Opcode* assignment(ast::Assignment*) throw();
	Opcode* import(ast::Import*) throw();
private:
	/* AST nodes */
	ast::TreeNode* m_ast;
	VM::OpcodeList m_opcodes;
	SSA m_ssa;
	JmpStack m_jmps;
	JmpStack m_brks;
	/* Package manager */
	PackageManager m_pkgmanager;
	/* Global function table */
	static FunctionTable s_func_table;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
