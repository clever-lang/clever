/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/resolver.h"
#include "core/compiler.h"

namespace clever { namespace ast {

Resolver::Resolver()
	: Visitor(), m_symtable(new Scope()), m_curscope(m_symtable), m_scope_id(0) {

}

void Resolver::visit(Block* node) {
	m_curscope = m_symtable->newLexicalScope();
	m_curscope->setId(m_scope_id++);

	Visitor::visit(static_cast<Node*>(node));

	m_curscope = m_curscope->getParent();
}

void Resolver::visit(VariableDecl* node) {
	const CString* name = node->getIdent()->getName();

	if (m_curscope->getAny(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare variable `%S'.", name);
	}

	m_curscope->pushValue(name, new Value());
}

void Resolver::visit(FunctionDecl* node) {
	const CString* name;

	if (node->hasIdent()) {
		name = node->getIdent()->getName();

		if (m_curscope->getAny(name)) {
			Compiler::errorf(node->getLocation(),
				"Cannot redeclare function `%S'.", name);
		}
	}

	Function* func = static_cast<Function*>(CLEVER_FUNC_TYPE->allocData());

	if (node->hasIdent()) {
		func->setName(*name);
	}

	func->setUserDefined();

	Value* fval = new Value();
	fval->setType(CLEVER_FUNC_TYPE);
	fval->setObj(func);

	m_curscope->pushValue(name, fval);

	m_curscope = m_symtable->newLexicalScope();
	m_curscope->setId(m_scope_id++);

	if (node->hasArgs()) {
		for (size_t i = 0; i < node->numArgs(); ++i) {
			static_cast<VariableDecl*>(node->getArg(i))->getAssignment()->setConditional(true);
		}

		node->getArgs()->accept(*this);

		func->setArgVars(m_curscope);
	}

	node->getBlock()->accept(*this);

	m_curscope = m_curscope->getParent();
}

void Resolver::visit(Ident* node) {
	if (!m_curscope->getAny(node->getName())) {
		Compiler::errorf(node->getLocation(),
			"Variable `%S' not found.", node->getName());
	}
}

}}
