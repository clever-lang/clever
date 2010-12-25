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

namespace clever {

/*
 * Initializes the compiler data
 */
void Compiler::Init(ast::TreeNode::nodeList& nodes) {
	m_ast = nodes;
}

/*
 * Displays an error message
 */
void Compiler::error(const char* message) {
	std::cout << "Compile error: " << message << std::endl;
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
		case '+':
			DO_NUM_OPERATION(+, Integer, lhs, rhs);
			DO_STR_OPERATION(+, lhs, rhs);
			DO_NUM_OPERATION(+, Double, lhs, rhs);
			break;
		case '-':
			DO_NUM_OPERATION(-, Integer, lhs, rhs);
			DO_NUM_OPERATION(-, Double, lhs, rhs);
			break;
		case '/':
			DO_NUM_OPERATION(/, Integer, lhs, rhs);
			DO_NUM_OPERATION(/, Double, lhs, rhs);
			break;
		case '*':
			DO_NUM_OPERATION(*, Integer, lhs, rhs);
			DO_NUM_OPERATION(*, Double, lhs, rhs);
			break;
		case '|':
			DO_NUM_OPERATION(|, Integer, lhs, rhs);
			break;
		case '^':
			DO_NUM_OPERATION(^, Integer, lhs, rhs);
			break;
		case '&':
			DO_NUM_OPERATION(&, Integer, lhs, rhs);
			break;
	}
	return NULL;
}

void Compiler::buildIR() {
	VM vm;
	ast::TreeNode::nodeList::iterator it = m_ast.begin();

	while (it < m_ast.end()) {
		Opcode* opcode = (*it)->opcodeGen();

		if (opcode) {
			m_opcodes.push_back(opcode);
		}
		++it;
	}

	vm.setOpcodes(&m_opcodes);
	vm.run();
}

/*
 * Dumps the AST
 */
void Compiler::dumpAST(void) {
	int level = 0;
	ast::TreeNode::nodeList::iterator it = m_ast.begin();
	std::string prefix("");

	while (it < m_ast.end()) {
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
