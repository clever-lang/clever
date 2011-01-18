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
#include <vector>
#include <cstdlib>
#include "compiler.h"
#include "modules.h"
#include "int.h"
#include "double.h"
#include "typetable.h"

namespace clever {

FunctionTable Compiler::s_func_table;
TypeMap TypeTable::s_type_table;

/*
 * Initializes the compiler data
 */
void Compiler::Init(ast::TreeNode* nodes) throw() {
	m_ast = nodes;

	/* Standard module */
	std_module::g_std_module->Init();
	m_modules.push_back(std_module::g_std_module);

	/* Load the primitive data types */
	loadTypes();
	/* Load internal modules */
	loadModules();
}

void Compiler::loadTypes() throw() {
	g_int_type->Init();
	g_double_type->Init();

	TypeTable::insert(CSTRING("Int"), g_int_type);
	TypeTable::insert(CSTRING("Double"), g_double_type);
}

/*
 * Load the modules
 */
void Compiler::loadModules() throw() {
	ModuleList::const_iterator it = m_modules.begin(), end_module(m_modules.end());

	while (it != end_module) {
		FunctionList& functions = (*it)->get_functions();
		FunctionList::const_iterator it2 = functions.begin(), end_func(functions.end());

		while (it2 != end_func) {
			/* Add the module functions to the global function table */
			s_func_table.insert(std::pair<const std::string, FunctionPtr>(it2->first, it2->second));
			++it2;
		}
		++it;
	}
}

/*
 * Deallocs memory used by compiler data
 */
Compiler::~Compiler() {
	FunctionTable::const_iterator it = s_func_table.begin(), end_func(s_func_table.end());
	ModuleList::const_iterator it2 = m_modules.begin(), end_module(m_modules.end());

	while (it != end_func) {
		++it;
	}

	while (it2 != end_module) {
		delete *it2;
		++it2;
	}
	TypeTable::clear();
}

/*
 * Collects all opcode
 */
void Compiler::buildIR() throw() {
	ast::TreeNode::nodeList& ast_nodes = m_ast->getNodeList();
	ast::TreeNode::nodeList::iterator it = ast_nodes.begin(), end(ast_nodes.end());

	m_builder.init();

	while (it != end) {
		Opcode* opcode = (*it)->codeGen(m_builder);

		if (opcode) {
			m_builder.push(opcode);
			// opcode->dump();
		}
		++it;
	}

	m_builder.shutdown();
	m_ast->clear();
}

/*
 * Displays an error message
 */
void Compiler::error(const char* message) throw() {
	std::cerr << "Compile error: " << message << std::endl;
	exit(1);
}

/*
 * Performs a type compatible checking
 */
bool Compiler::checkCompatibleTypes(Value* lhs, Value* rhs) throw() {
	/* Constants with different type cannot performs operation */
	if (lhs->isConst() && lhs->hasSameKind(rhs) && !lhs->hasSameType(rhs)) {
		return false;
	}
	return true;
}

/*
 * Performs a constant folding optimization
 */
ConstantValue* Compiler::constantFolding(int op, Value* lhs, Value* rhs) throw() {

#define DO_NUM_OPERATION(_op, type, x, y) \
	if (x->is##type()) return new ConstantValue(x->get##type() _op y->get##type());

#define DO_STR_OPERATION(_op, x, y) \
	if (x->isString()) return new ConstantValue(CSTRING(x->getString() _op y->getString()));

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
