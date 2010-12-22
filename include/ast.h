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

#ifndef CLEVER_AST_H
#define CLEVER_AST_H

#include <string>
#include <vector>
#include "types.h"
#include "opcodes.h"

namespace clever { namespace ast {

#define CLEVER_AST_PURE_VIRTUAL_MEMBERS \
	virtual Value *codeGen();           \
	virtual std::string debug();

class ExprAST {
public:
	ExprAST() : m_reference(0) { }

	virtual ~ExprAST() { }

	/*
	 * Returns the number of references
	 */
	inline int refCount() const {
		return m_reference;
	}

	/*
	 * Increments the reference to the object
	 */
	inline void addRef() {
		++m_reference;
	}

	/*
	 * Decrements the reference to the object
	 */
	inline int delRef() {
		return --m_reference;
	}

	/*
	 * Destroy the object when the reference reaches zero
	 */
	inline void destroy(ExprAST* expr) {
		if (expr && !expr->delRef()) {
			delete expr;
		}
	}

	/*
	 * Method for generating the expression IR
	 */
	virtual Value* codeGen() = 0;
	/*
	 * Method for debug purpose
	 */
	virtual std::string debug() = 0;

	virtual Opcode* opcodeGen() {
		return NULL;
	}
private:
	int m_reference;
};


class TreeNode {
public:
	typedef std::vector<ExprAST*> nodeList;

	TreeNode() { }
	~TreeNode();

	inline void add(ExprAST* node) {
		node->addRef();
		nodes.push_back(node);
	}
	inline nodeList getNodeList() const {
		return nodes;
	}
private:
	nodeList nodes;
};

class BinaryExprAST : public ExprAST {
public:
	BinaryExprAST(char op_, ExprAST* lhs, ExprAST* rhs)
		: m_op(op_), m_lhs(lhs), m_rhs(rhs) {
		m_lhs->addRef();
		m_rhs->addRef();
		m_result = new ExprValue;
	}

	~BinaryExprAST() {
		destroy(m_lhs);
		destroy(m_rhs);
	}

	Opcode* opcodeGen(void);
	DISALLOW_COPY_AND_ASSIGN(BinaryExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	char m_op;
	ExprAST* m_lhs;
	ExprAST* m_rhs;
	Value* m_result;
};

class NumberExprAST : public ExprAST {
public:
	explicit NumberExprAST(double val)
		: m_value(val) { }

	~NumberExprAST() { }

	DISALLOW_COPY_AND_ASSIGN(NumberExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	double m_value;
};

class VariableDeclAST : public ExprAST {
public:
	VariableDeclAST(ExprAST* type, ExprAST* variable, ExprAST* rhs)
		: m_type(type), m_variable(variable), m_rhs(rhs) {
		m_type->addRef();
		m_variable->addRef();
		m_rhs->addRef();
	}

	~VariableDeclAST() {
		destroy(m_type);
		destroy(m_variable);
		destroy(m_rhs);
	}

	DISALLOW_COPY_AND_ASSIGN(VariableDeclAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ExprAST* m_type;
	ExprAST* m_variable;
	ExprAST* m_rhs;
};

class IdentifierAST : public ExprAST {
public:
	explicit IdentifierAST(const std::string& name)
		: m_name(name) { }

	DISALLOW_COPY_AND_ASSIGN(IdentifierAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	const std::string m_name;
	Value* m_value;
};

class TypeCreationAST : public ExprAST {
public:
	TypeCreationAST(ExprAST* type, ExprAST* arguments)
		: m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreationAST() {
		destroy(m_type);
		destroy(m_arguments);
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreationAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* m_type;
	ExprAST* m_arguments;
};

class NewBlockAST : public ExprAST {
public:
	NewBlockAST() { }

	DISALLOW_COPY_AND_ASSIGN(NewBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class EndBlockAST : public ExprAST {
public:
	EndBlockAST() { }

	DISALLOW_COPY_AND_ASSIGN(EndBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class CommandAST : public ExprAST {
public:
	CommandAST(ExprAST* command, ExprAST* value)
		: m_command(command), m_value(value) {
		m_command->addRef();
		m_value->addRef();
	}

	~CommandAST() {
		destroy(m_command);
		destroy(m_value);
	}

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(CommandAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* m_command;
	ExprAST* m_value;
};

}} // clever::ast

#endif // CLEVER_AST_H