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

		// XXX: is this really needed?
		m_ir.push_back(
			IR(OP_ASSIGN, FETCH_VAL, var_id,
				FETCH_VAL, m_scope->pushConst(new Value())));

		m_ir.back().op1_scope = m_scope->getId();
		m_ir.back().op2_scope = m_scope->getId();
	}
}

void Codegen::visit(Assignment* node)
{
	// TODO: allow assignment of any possible left hand side.

	Ident* ident = static_cast<Ident*>(node->getLhs());
	Symbol* sym = m_scope->getLocal(ident->getName());

	if (!sym) {
		m_compiler->errorf(node->getLocation(),
			"Variable `%S' not found!", ident->getName());
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

	m_ir.push_back(IR(OP_FCALL, FETCH_VAL, sym->value_id));
	m_ir.back().op1_scope = sym->scope->getId();
}

void Codegen::visit(FunctionDecl* node)
{
	const CString* name = node->getIdent()->getName();
	Symbol* sym = m_scope->getLocal(name);

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

	m_jmps.push(AddrVector());
	m_jmps.top().push_back(m_ir.size());

	// XXX: what's the point of a jump here?
	m_ir.push_back(IR(OP_JMP, JMP_ADDR, 0));

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

	m_ir[m_jmps.top().back()].op1 = m_ir.size();
}

void Codegen::visit(Return* node)
{
	// TODO: return value
	m_ir.push_back(IR(OP_RET));
}

}} // clever::ast
