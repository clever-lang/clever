/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
#include <vector>
#include <cstdlib>
#include "compiler.h"
#include "modules.h"

namespace clever {

FunctionTable Compiler::s_func_table;

/*
 * Initializes the compiler data
 */
void Compiler::Init(ast::TreeNode& nodes) {
	m_ast = nodes;

	/* Standard module */
	g_std_module->Init();
	m_modules.push_back(g_std_module);

	loadModules();
}

/*
 * Load the modules
 */
void Compiler::loadModules() {
	ModuleList::iterator it = m_modules.begin();

	while (it != m_modules.end()) {
		FunctionList& functions = (*it)->get_functions();
		FunctionList::iterator it2 = functions.begin();

		while (it2 != functions.end()) {
			/* Add the module functions to the global function table */
			s_func_table.insert(std::pair<const std::string, Function*>((*it2)->get_name(), *it2));
			++it2;
		}
		++it;
	}
}

/*
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	FunctionTable::iterator it = s_func_table.begin();
	ModuleList::iterator it2 = m_modules.begin();

	while (it != s_func_table.end()) {
		delete it->second;
		++it;
	}

	while (it2 != m_modules.end()) {
		delete *it2;
		++it2;
	}
}

/*
 * Collects all opcode
 */
void Compiler::buildIR() {
	ast::TreeNode::nodeList& ast_nodes = m_ast.getNodeList();
	ast::TreeNode::nodeList::const_iterator it = ast_nodes.begin();

	m_builder.init();

	while (it != ast_nodes.end()) {
		Opcode* opcode = (*it)->codeGen(m_builder);

		if (opcode) {
			m_builder.push(opcode);
			// opcode->dump();
		}
		++it;
	}

	m_builder.shutdown();
	m_ast.clear();
}

/*
 * Displays an error message
 */
void Compiler::error(const char* message) {
	std::cerr << "Compile error: " << message << std::endl;
	exit(1);
}

/*
 * Performs a type compatible checking
 */
bool Compiler::checkCompatibleTypes(Value* lhs, Value* rhs) {
	/* Constants with different type cannot performs operation */
	if (lhs->isConst() && lhs->hasSameKind(rhs) && !lhs->hasSameType(rhs)) {
		return false;
	}
	return true;
}

/*
 * Performs a constant folding optimization
 */
ConstantValue* Compiler::constantFolding(char op, Value* lhs, Value* rhs) {

#define DO_NUM_OPERATION(_op, type, x, y) \
	if (x->is##type()) return new ConstantValue(x->get##type() _op y->get##type());

#define DO_STR_OPERATION(_op, x, y) \
	if (x->isString()) return new ConstantValue(CSTRING(x->getString() _op y->getString()));

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
	}
	return NULL;
}

/*
 * Dumps the AST
 */
void Compiler::dumpAST(void) {
	int level = 0;
	ast::TreeNode::nodeList ast_nodes = m_ast.getNodeList();
	ast::TreeNode::nodeList::iterator it = ast_nodes.begin();
	std::string prefix("");

	while (it != ast_nodes.end()) {
		if (!(*it)->debug().compare("{")) {
			prefix = std::string(level, ' ');
			++level;
		} else if (!(*it)->debug().compare("}")) {
			--level;
			prefix = std::string(level, ' ');
		}

		std::cout << prefix << "(" << (*it)->refCount() << ") " << (*it)->debug() << std::endl;
		++it;
	}
}

} // clever
