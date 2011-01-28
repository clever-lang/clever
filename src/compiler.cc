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

#include <iostream>
#include <cstdlib>
#include <vector>
#include "compiler.h"
#include "ast.h"
#include "int.h"
#include "double.h"
#include "astvisitor.h"
#include "typetable.h"

namespace clever {

PackageManager Compiler::s_pkgmanager;
FunctionTable Compiler::s_func_table;
TypeMap TypeTable::s_type_table;

/**
 * Initializes the compiler data
 */
void Compiler::Init(ast::Node* nodes) throw() {
	m_ast = nodes;
	/**
	 * Load package list
	 */
	s_pkgmanager.Init(&s_func_table);

	/**
	 * Load the primitive data types
	 */
	loadTypes();

	m_visitor = new ast::ASTVisitor;
}

/**
 * Loads native types
 */
void Compiler::loadTypes() throw() {
	g_int_type->Init();
	g_double_type->Init();

	TypeTable::insert(CSTRING("Int"), g_int_type);
	TypeTable::insert(CSTRING("Double"), g_double_type);
}

OpcodeList& Compiler::getOpcodes() throw() {
	return m_visitor->get_opcodes();
}

/**
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	FunctionTable::const_iterator it = s_func_table.begin(), end_func(s_func_table.end());

	/**
	 * Deallocs memory used by global function table entries
	 */
	while (it != end_func) {
		delete it->second;
		++it;
	}

	TypeTable::clear();

	s_pkgmanager.shutdown();

	delete m_visitor;

	delete m_ast;
}

/**
 * Collects all opcode
 */
void Compiler::buildIR() throw() {
	ast::NodeList& ast_nodes = m_ast->getNodes();
	ast::NodeList::iterator it = ast_nodes.begin(), end(ast_nodes.end());

	m_visitor->init();

	/**
	 * Iterating over TopNode AST node
	 */
	while (it != end) {
		(*it)->accept(*m_visitor);
		++it;
	}

	m_visitor->shutdown();

	m_ast->clearNodes();
}

/**
 * Displays an error message
 */
void Compiler::error(std::string message) throw() {
	std::cerr << "Compile error: " << message << std::endl;
	exit(1);
}

/**
 * Performs a type compatible checking
 */
bool Compiler::checkCompatibleTypes(Value* lhs, Value* rhs) throw() {
	/**
	 * Constants with different type cannot performs operation
	 */
	if (lhs->isPrimitive() && rhs->isPrimitive() && !lhs->hasSameType(rhs)) {
		return false;
	}
	return true;
}

/**
 * Performs a constant folding optimization
 */
Value* Compiler::constantFolding(int op, Value* lhs, Value* rhs) throw() {

#define DO_NUM_OPERATION(_op, type, x, y) \
	if (x->is##type()) return new Value(x->get##type() _op y->get##type());

#define DO_STR_OPERATION(_op, x, y) \
	if (x->isString()) return new Value(CSTRING(x->getString() _op y->getString()));

	/**
	 * Check if the variable value can be predicted
	 */
	if ((lhs->hasName() && lhs->isModified()) || (rhs->hasName() && rhs->isModified())) {
		return NULL;
	}

	switch (op) {
		case ast::PLUS:
			DO_NUM_OPERATION(+, Integer, lhs, rhs);
			DO_STR_OPERATION(+, lhs, rhs);
			DO_NUM_OPERATION(+, Double, lhs, rhs);
			break;
		case ast::MINUS:
			DO_NUM_OPERATION(-, Integer, lhs, rhs);
			DO_NUM_OPERATION(-, Double, lhs, rhs);
			break;
		case ast::DIV:
			DO_NUM_OPERATION(/, Integer, lhs, rhs);
			DO_NUM_OPERATION(/, Double, lhs, rhs);
			break;
		case ast::MULT:
			DO_NUM_OPERATION(*, Integer, lhs, rhs);
			DO_NUM_OPERATION(*, Double, lhs, rhs);
			break;
		case ast::OR:
			DO_NUM_OPERATION(|, Integer, lhs, rhs);
			break;
		case ast::XOR:
			DO_NUM_OPERATION(^, Integer, lhs, rhs);
			break;
		case ast::AND:
			DO_NUM_OPERATION(&, Integer, lhs, rhs);
			break;
		case ast::GREATER:
			DO_NUM_OPERATION(>, Integer, lhs, rhs);
			DO_NUM_OPERATION(>, Double, lhs, rhs);
			break;
		case ast::LESS:
			DO_NUM_OPERATION(<, Integer, lhs, rhs);
			DO_NUM_OPERATION(<, Double, lhs, rhs);
			break;
		case ast::GREATER_EQUAL:
			DO_NUM_OPERATION(>=, Integer, lhs, rhs);
			DO_NUM_OPERATION(>=, Double, lhs, rhs);
			break;
		case ast::LESS_EQUAL:
			DO_NUM_OPERATION(<=, Integer, lhs, rhs);
			DO_NUM_OPERATION(<=, Double, lhs, rhs);
			break;
		case ast::EQUAL:
			DO_NUM_OPERATION(==, Integer, lhs, rhs);
			DO_NUM_OPERATION(==, Double, lhs, rhs);
			break;
		case ast::NOT_EQUAL:
			DO_NUM_OPERATION(!=, Integer, lhs, rhs);
			DO_NUM_OPERATION(!=, Double, lhs, rhs);
			break;
		case ast::MOD:
			DO_NUM_OPERATION(%, Integer, lhs, rhs);
			break;
	}
	return NULL;
}

} // clever
