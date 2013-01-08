/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/compiler.h"
#include "core/resolver.h"
#include "types/native_types.h"

namespace clever { namespace ast {

Resolver::Resolver(Compiler* compiler)
	: Visitor(), m_compiler(compiler)
{
	// global environment and scope
	m_symtable = m_scope = new Scope();
	m_scope->setEnvironment(new Environment(NULL));
	m_stack.push(m_scope->getEnvironment());
	m_scope->getEnvironment()->delRef();

	// Native type allocation
	Value* intval = new Value(CLEVER_INT_TYPE    = new IntType);
	Value* strval = new Value(CLEVER_STR_TYPE    = new StrType);
	Value* dblval = new Value(CLEVER_DOUBLE_TYPE = new DoubleType);
	Value* fncval = new Value(CLEVER_FUNC_TYPE   = new FuncType);
	Value* bolval = new Value(CLEVER_BOOL_TYPE   = new BoolType);
	Value* trdval = new Value(CLEVER_THREAD_TYPE = new ThreadType);

	m_scope->pushValue(CSTRING("Int"),      intval);
	m_scope->pushValue(CSTRING("String"),   strval);
	m_scope->pushValue(CSTRING("Double"),   dblval);
	m_scope->pushValue(CSTRING("Function"), fncval);
	m_scope->pushValue(CSTRING("Thread"),    trdval);
	m_scope->pushValue(CSTRING("Bool"),     bolval);

	m_stack.top()->pushValue(intval);
	m_stack.top()->pushValue(strval);
	m_stack.top()->pushValue(dblval);
	m_stack.top()->pushValue(fncval);
	m_stack.top()->pushValue(trdval);
	m_stack.top()->pushValue(bolval);

	CLEVER_INT_TYPE->init();
	CLEVER_STR_TYPE->init();
}

void Resolver::visit(Block* node)
{
	m_scope = m_scope->enter();
	m_scope->setEnvironment(m_stack.top());

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

	Value* val = new Value();
	m_scope->pushValue(name, val);

	m_stack.top()->pushValue(val);


	node->getIdent()->accept(*this);

	if (node->hasAssignment()) {
		node->getAssignment()->accept(*this);
	}

	val->setConst(node->isConst());
}

void Resolver::visit(ThreadBlock* node)
{
	const CString* name;

	if (node->getSize() != NULL) {
		node->getSize()->accept(*this);
	}

	name = node->getName()->getName();
	clever_assert_not_null(name);

	if (m_scope->getLocal(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare thread `%S'.", name);
	}

	Thread* thread = static_cast<Thread*>(CLEVER_THREAD_TYPE->allocData(NULL));

	thread->setUserDefined();

	Value* tval = new Value();
	tval->setType(CLEVER_THREAD_TYPE);
	tval->setObj(thread);

	thread->setName(*name);
	m_scope->pushValue(name, tval);

	m_stack.top()->pushValue(tval);

	node->getName()->accept(*this);

	m_scope = m_scope->enter();

	m_scope->setEnvironment(new Environment(m_stack.top()));
	m_stack.push(m_scope->getEnvironment());
	thread->setEnvironment(m_scope->getEnvironment());
	m_scope->getEnvironment()->delRef();

	node->setScope(m_scope);

	node->getBlock()->accept(*this);

	m_scope = m_scope->leave();

	m_stack.pop();
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

	m_stack.top()->pushValue(fval);

	node->getIdent()->accept(*this);

	m_scope = m_scope->enter();

	m_scope->setEnvironment(new Environment(m_stack.top()));
	m_stack.push(m_scope->getEnvironment());
	func->setEnvironment(m_scope->getEnvironment());
	m_scope->getEnvironment()->delRef();

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

	m_stack.pop();
}

void Resolver::visit(Ident* node)
{
	Symbol* sym = m_scope->getAny(node->getName());

	if (!sym) {
		Compiler::errorf(node->getLocation(),
			"Identifier `%S' not found.", node->getName());
	}

	node->setVOffset(m_scope->getOffset(sym));
	sym->voffset = node->getVOffset();

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

	node->setVOffset(m_scope->getOffset(sym));

	node->setSymbol(sym);
	node->setScope(sym->scope);
}

void Resolver::visit(Import* node)
{
	if (node->getModule()) {
		m_compiler->getPkgManager().importModule(m_scope, m_stack.top(),
			node->getPackage()->getName(), node->getModule()->getName());
	} else {
		m_compiler->getPkgManager().importPackage(m_scope, m_stack.top(),
			node->getPackage()->getName());
	}
}

void Resolver::visit(Catch* node)
{
	m_scope = m_scope->enter();

	m_scope->setEnvironment(m_stack.top());

	Value* val = new Value();

	m_scope->pushValue(node->getVar()->getName(), val);

	m_stack.top()->pushValue(val);

	node->getVar()->accept(*this);

	node->setScope(m_scope);

	Visitor::visit(static_cast<NodeArray*>(node->getBlock()));

	m_scope = m_scope->leave();
}

}} // clever::ast
