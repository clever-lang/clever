/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/ast.h"
#include "core/codegen.h"
#include "core/scope.h"
#include "core/compiler.h"

namespace clever { namespace ast {

void Codegen::init()
{
	m_scope = new Scope;
	m_scope_pool[m_scope_id++] = m_scope;
}

void Codegen::visit(IntLit* node)
{
	node->setConstId(m_compiler->addConstant(new Value(node->getValue())));
}

void Codegen::visit(DoubleLit* node)
{
	node->setConstId(m_compiler->addConstant(new Value(node->getValue())));
}

void Codegen::visit(StringLit* node)
{
	node->setConstId(m_compiler->addConstant(new Value(node->getValue())));
}

void Codegen::visit(Import* node)
{
	m_compiler->getPkgManager().importModule(m_scope,
		node->getPackage()->getName(), node->getModule()->getName());
}

void Codegen::visit(Block* node)
{
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(m_scope_id);
	m_scope_pool[m_scope_id++] = m_scope;

	std::vector<Node*> nodes = node->getNodes();
	std::vector<Node*>::const_iterator it = nodes.begin(), end = nodes.end();
	while (it != end) {
		(*it)->accept(*this);
		++it;
	}

	m_scope = m_scope->getParent();
}

void Codegen::visit(VariableDecl* node)
{
	if (node->hasAssignment()) {
		m_scope->pushValue(node->getIdent()->getName(), new Value());
		node->getAssignment()->accept(*this);
	} else {
		size_t var_id = m_scope->pushValue(node->getIdent()->getName(), new Value());

		m_ir.push_back(
			IR(OP_ASSIGN,
				Operand(FETCH_VAL, var_id, m_scope->getId()),
				Operand(FETCH_VAL, m_scope->pushConst(new Value()), m_scope->getId())));
	}
}

void Codegen::visit(Assignment* node)
{
	// TODO: allow assignment of any possible left hand side.

	Ident* ident = static_cast<Ident*>(node->getLhs());
	Symbol* sym = m_scope->getLocal(ident->getName());
	Node* rhs = node->getRhs();

	if (!sym) {
		m_compiler->errorf(node->getLocation(),
			"Variable `%S' not found!", ident->getName());
	}

	if (rhs->isLiteral()) {
		rhs->accept(*this);

		Literal* literal = static_cast<Literal*>(rhs);

		m_ir.push_back(IR(OP_ASSIGN,
			Operand(FETCH_VAL, sym->value_id, sym->scope->getId()),
			Operand(FETCH_CONST, literal->getConstId())));
	}

	// TODO: if node->isConditional() is true, emit branching code to avoid assignment when ident has been initialized.
}

void Codegen::visit(FunctionCall* node)
{
	Ident* ident = static_cast<Ident*>(node->getCallee());
	Symbol* sym = m_scope->getAny(ident->getName());

	if (!sym) {
		m_compiler->errorf(node->getLocation(),
			"Function `%S' not found!", ident->getName());
	}

	if (node->hasArgs()) {
		NodeList& args = node->getArgs()->getNodes();
		NodeList::const_iterator it = args.begin(), end = args.end();

		while (it != end) {
			// m_ir.push_back(IR(OP_SEND_VAL, ...));
			++it;
		}
	}

	m_ir.push_back(IR(OP_FCALL,
		Operand(FETCH_VAL, sym->value_id, sym->scope->getId())));
}

void Codegen::visit(FunctionDecl* node)
{
	const CString* name = node->getIdent()->getName();
	Symbol* sym = m_scope->getLocal(name);
	size_t start_func;

	if (sym) {
		m_compiler->errorf(node->getLocation(),
			"Function `%S' already defined in the scope!", name);
	}

	Function* func = static_cast<Function*>(CLEVER_FUNC_TYPE->allocData());

	func->setName(*name);
	func->setUserDefined();
	func->setAddr(m_ir.size());

	Value* fval = new Value();
	fval->setType(CLEVER_FUNC_TYPE);
	fval->setObj(func);

	m_scope->pushValue(name, fval);

	start_func = m_ir.size();

	// XXX: what's the point of a jump here?
	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, 0)));

	// TODO: find a cleaner way to enter and leave scopes
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(m_scope_id);
	m_scope_pool[m_scope_id++] = m_scope;

	if (node->hasArgs()) {
		for (size_t i = 0; i < node->numArgs(); ++i) {
			VariableDecl* decl = static_cast<VariableDecl*>(node->getArg(i));

			if (decl->hasAssignment()) {
				decl->getAssignment()->setConditional(true);
			}
		}

		node->getArgs()->accept(*this);
	}

	node->getBlock()->accept(*this);

	m_scope = m_scope->getParent();

	m_ir.push_back(IR(OP_LEAVE));

	m_ir[start_func].op1.value_id = m_ir.size();
}

void Codegen::visit(Return* node)
{
	// TODO: return value
	m_ir.push_back(IR(OP_RET));
}

void Codegen::visit(While* node)
{
	size_t start_while = m_ir.size();

	node->getCondition()->accept(*this);

	m_ir.push_back(IR(OP_JMPZ));

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, start_while)));

	m_ir[start_while].op2.value_id = m_ir.size();
}


}} // clever::ast
