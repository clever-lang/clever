/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/native_types.h"
#include "core/resolver.h"
#include "core/compiler.h"

namespace clever { namespace ast {

Resolver::Resolver(Compiler* compiler)
	: Visitor(), m_compiler(compiler)
{
	// global environment and scope
	m_symtable = m_scope = new Scope();

	// Native type allocation
	m_symtable->pushType(CSTRING("Int"),      CLEVER_INT_TYPE    = new IntType);
	m_symtable->pushType(CSTRING("Double"),   CLEVER_DOUBLE_TYPE = new DoubleType);
	m_symtable->pushType(CSTRING("String"),   CLEVER_STR_TYPE    = new StrType);
	m_symtable->pushType(CSTRING("Function"), CLEVER_FUNC_TYPE   = new FuncType);

	CLEVER_INT_TYPE->init();
	CLEVER_STR_TYPE->init();
}
Resolver::~Resolver() {
}

void Resolver::visit(Block* node)
{
	m_scope = m_scope->enter();

	node->setScope(m_scope);

	Visitor::visit(static_cast<NodeArray*>(node));

	m_scope = m_scope->leave();
}

void Resolver::visit(VariableDecl* node)
{
	const CString* name = node->getIdent()->getName();

	if (m_scope->getLocal(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare variable `%S'.", name);
	}

	Value *val = new Value();
	m_scope->pushValue(name, val);

	node->getIdent()->accept(*this);

	if (node->hasAssignment()) {
		node->getAssignment()->accept(*this);
	}
}

void Resolver::visit(FunctionDecl* node)
{
	static size_t anon_fdecls = 0;

	const CString* name;

	// Create an user-unusable symbol name for anonymous functions
	if (!node->hasIdent()) {
		std::stringstream buf;
		buf << "<anonymous " << anon_fdecls++ << ">";
		node->setIdent(new Ident(CSTRING(buf.str()),
								 node->getLocation()));
	}

	name = node->getIdent()->getName();
	clever_assert_not_null(name);

	if (m_scope->getLocal(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare function `%S'.", name);
	}

	Function* func = static_cast<Function*>(CLEVER_FUNC_TYPE->allocData(NULL));

	func->setUserDefined();

	Value* fval = new Value();
	fval->setType(CLEVER_FUNC_TYPE);
	fval->setObj(func);

	func->setName(*name);
	m_scope->pushValue(name, fval);

	node->getIdent()->accept(*this);

	m_scope = m_scope->enter();

	node->setScope(m_scope);

	if (node->hasArgs()) {
		for (size_t i = 0; i < node->numArgs(); ++i) {
			static_cast<VariableDecl*>(node->getArg(i))->getAssignment()->setConditional(true);
		}

		node->getArgs()->accept(*this);

		func->setArgVars(m_scope);
	}

	node->getBlock()->accept(*this);

	m_scope = m_scope->leave();
}

void Resolver::visit(Ident* node)
{
	Symbol* sym = m_scope->getAny(node->getName());

	if (!sym) {
		Compiler::errorf(node->getLocation(),
			"Identifier `%S' not found.", node->getName());
	}

	node->setSymbol(sym);
	node->setScope(sym->scope);
}

void Resolver::visit(Type* node)
{
	Symbol* sym = m_scope->getAny(node->getName());

	if (!sym) {
		Compiler::errorf(node->getLocation(),
			"Type `%S' not found.", node->getName());
	}

	node->setSymbol(sym);
	node->setScope(sym->scope);
}

void Resolver::visit(Import* node)
{
	if (node->getModule()) {
		m_compiler->getPkgManager().importModule(m_scope,
			node->getPackage()->getName(), node->getModule()->getName());
	} else {
		m_compiler->getPkgManager().importPackage(m_scope,
			node->getPackage()->getName());
	}
}

}} // clever::ast
