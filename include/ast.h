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
#include "refcounted.h"

namespace clever { namespace ast {

#define CLEVER_AST_PURE_VIRTUAL_MEMBERS \
	virtual Value *codeGen();           \
	virtual std::string debug();

class ExprAST : public RefCounted {
public:
	ExprAST() : RefCounted(0) { }

	virtual ~ExprAST() { }

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
	BinaryExprAST(char, ExprAST*, ExprAST*);

	~BinaryExprAST() {
		if (m_value) {
			m_value->delRef();
		}
		if (m_lhs) {
			m_lhs->delRef();
		}
		if (m_rhs) {
			m_rhs->delRef();
		}
	}

	Opcode* opcodeGen();
	DISALLOW_COPY_AND_ASSIGN(BinaryExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	char m_op;
	bool optimized;
	ExprAST* m_lhs;
	ExprAST* m_rhs;
	TempValue* m_result;
	ConstantValue* m_value;
};

class NumberExprAST : public ExprAST {
public:
	explicit NumberExprAST(int64_t val)
		: ExprAST() {
		m_value = new ConstantValue(val);
	}

	explicit NumberExprAST(double val)
		: ExprAST() {
		m_value = new ConstantValue(val);
	}

	~NumberExprAST() {
		m_value->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(NumberExprAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ConstantValue* m_value;
};

class VariableDeclAST : public ExprAST {
public:
	VariableDeclAST(ExprAST* type, ExprAST* variable, ExprAST* rhs)
		: ExprAST(), m_type(type), m_variable(variable), m_rhs(rhs) {
		m_type->addRef();
		m_variable->addRef();
		m_rhs->addRef();
	}

	~VariableDeclAST() {
		m_type->delRef();
		m_variable->delRef();
		m_rhs->delRef();
	}

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(VariableDeclAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;

private:
	ExprAST* m_type;
	ExprAST* m_variable;
	ExprAST* m_rhs;
};

class IdentifierAST : public ExprAST {
public:
	explicit IdentifierAST(std::string name)
		: ExprAST() {
		m_value = new NamedValue(name);
	}

	~IdentifierAST() {
		m_value->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(IdentifierAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	NamedValue* m_value;
};

class StringLiteralAST : public ExprAST {
public:
	explicit StringLiteralAST(std::string name)
		: ExprAST() {
		m_value = new ConstantValue(name);
	}

	~StringLiteralAST() {
		m_value->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(StringLiteralAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ConstantValue* m_value;
};

class TypeCreationAST : public ExprAST {
public:
	TypeCreationAST(ExprAST* type, ExprAST* arguments)
		: ExprAST(), m_type(type), m_arguments(arguments) {
		m_type->addRef();
		m_arguments->addRef();
	}

	~TypeCreationAST() {
		m_type->delRef();
		m_arguments->delRef();
	}

	DISALLOW_COPY_AND_ASSIGN(TypeCreationAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* m_type;
	ExprAST* m_arguments;
};

class NewBlockAST : public ExprAST {
public:
	NewBlockAST() : ExprAST() { }

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(NewBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class EndBlockAST : public ExprAST {
public:
	EndBlockAST() : ExprAST() { }

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(EndBlockAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
};

class CommandAST : public ExprAST {
public:
	CommandAST(ExprAST* value)
		: ExprAST(), m_value(value) {
		m_value->addRef();
	}

	~CommandAST() {
		m_value->delRef();
	}

	Opcode* opcodeGen();

	DISALLOW_COPY_AND_ASSIGN(CommandAST);

	CLEVER_AST_PURE_VIRTUAL_MEMBERS;
private:
	ExprAST* m_value;
};

}} // clever::ast

#endif // CLEVER_AST_H
