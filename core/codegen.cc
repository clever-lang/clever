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
#include "core/pkgmanager.h"

namespace clever { namespace ast {

void Codegen::init()
{
	m_scope = new Scope;
	m_scope_pool[m_scope_id++] = m_scope;
}

void Codegen::visit(Import* node)
{
	m_pkg.importModule(m_scope,
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
			IR(OP_ASSIGN, FETCH_VAL, var_id,
				FETCH_VAL, m_scope->pushConst(new Value())));

		m_ir.back().op1_scope = m_scope->getId();
		m_ir.back().op2_scope = m_scope->getId();
	}
}

void Codegen::visit(Assignment* node)
{
	Ident* ident = static_cast<Ident*>(node->getLhs());
	Symbol* sym = m_scope->getLocal(ident->getName());

	if (!sym) {
		std::cerr << "Variable not found!" << std::endl;
	}
}

}} // clever::ast
