/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/compiler.h"
#include "core/resolver.h"
#include "core/native_types.h"
#include "core/module.h"
#include "core/user.h"

namespace clever { namespace ast {

Resolver::Resolver(const ModManager& ModManager, const std::string& ns_name)
	: Visitor(), m_modmanager(ModManager), m_ns_name(ns_name), m_mod(NULL), m_class(NULL)
{
	// Global environment and scope
	m_symtable = m_scope = new Scope();
	m_scope->setEnvironment(new Environment());
	m_stack.push(m_scope->getEnvironment());

	m_modmanager.importModule(m_scope, "std.core");
	m_mod = m_modmanager.getUserModule();
}

void Resolver::visit(Block* node)
{
	m_scope = m_scope->enter();
	m_scope->setEnvironment(m_stack.top());
	m_stack.top()->addRef();

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

	node->getIdent()->accept(*this);

	if (node->hasAssignment()) {
		node->getAssignment()->accept(*this);
	}

	val->setConst(node->isConst());
}

void Resolver::visit(FunctionDecl* node)
{
	static size_t anon_fdecls = 0;

	const CString* name;

	// Create an user-unusable symbol name for anonymous functions
	if (!node->hasIdent() && !node->hasType()) {
		std::stringstream buf;
		buf << "<anonymous " << anon_fdecls++ << ">";

		name = CSTRING(buf.str());

		node->setIdent(new Ident(name, node->getLocation()));
	} else if (node->isCtor()) {
		name = CSTRING("Constructo#" + *node->getType()->getName());
		node->setType(new Type(name, node->getLocation()));
	} else if (node->isDtor()) {
		name = CSTRING("Destructor#" + *node->getType()->getName());
		node->setType(new Type(name, node->getLocation()));
	} else {
		name = node->getIdent()->getName();

		if (!m_ns_name.empty()) {
			name = CSTRING(m_ns_name + ":" + *name);
			node->setIdent(new Ident(name, node->getLocation()));
		}
	}
	clever_assert_not_null(name);

	if (m_scope->getLocal(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare function `%S'.", name);
	}

	Function* func = new Function;

	func->setUserDefined();
	func->setName(*name);

	Value* fval = new Value;
	fval->setObj(CLEVER_FUNC_TYPE, func);

	if (m_class && !node->isAnonymous()) {
		func->setContext(m_class);

		node->setMethod(func);

		// Class member
		if (node->isCtor()) {
			m_class->setUserConstructor(func);
		} else if (node->isDtor()) {
			m_class->setUserDestructor(func);
		}
		if (m_class->hasMember(name)) {
			Compiler::errorf(node->getLocation(),
				"Cannot redeclare member `%S'", name);
		}
		m_class->addMember(name, MemberData(fval, node->getVisibility()));

		switch (node->getVisibility()) {
			case ast::PUBLIC:  func->setPublic();  break;
			case ast::PRIVATE: func->setPrivate(); break;
		}
	} else {
		m_scope->pushValue(name, fval);

		if (node->hasIdent()) {
			node->getIdent()->accept(*this);
		} else {
			node->getType()->accept(*this);
		}
		// Regular function
		func->setPublic();
	}

	m_scope = m_scope->enter();

	m_scope->setEnvironment(new Environment(m_stack.top()));
	m_stack.push(m_scope->getEnvironment());
	func->setEnvironment(m_scope->getEnvironment());

	node->setScope(m_scope);

	if (node->hasArgs()) {
		size_t required_args = 0;
		bool found_rhs = false;

		for (size_t i = 0, n = node->numArgs(); i < n;  ++i) {
			Assignment* assign = static_cast<VariableDecl*>(node->getArg(i))->getAssignment();

			assign->setConditional(true);

			if (found_rhs && !assign->getRhs()) {
				Compiler::errorf(assign->getLocation(),
					"Non-default argument found after the default argument list");
			} else if (!found_rhs && assign->getRhs()) {
				found_rhs = assign->getRhs();
			} else {
				++required_args;
			}
		}

		node->getArgs()->accept(*this);

		func->setNumArgs(node->numArgs());
		func->setNumRequiredArgs(required_args);
	}

	if (node->hasVarArg()) {
		node->getVarArg()->getAssignment()->setConditional(true);
		node->getVarArg()->accept(*this);

		func->setVariadic();
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
	size_t kind = node->getFunction() ? ModManager::FUNCTION
		: (node->getType() ? ModManager::TYPE : ModManager::ALL);

	const CString* name = (kind == ModManager::ALL) ? NULL
		: (kind == ModManager::FUNCTION ? node->getFunction()->getName()
			: node->getType()->getName());

	if (node->isNamespaced()) {
		kind |= ModManager::NAMESPACE;
	}

	ast::Node* tree = m_modmanager.importModule(m_scope,
		*node->getModule()->getName(), kind, name);

	node->setModuleTree(tree);

	if (tree) {
		Visitor::visit(static_cast<NodeArray*>(tree));
	}
}

void Resolver::visit(Catch* node)
{
	m_scope = m_scope->enter();
	m_scope->setEnvironment(m_stack.top());
	m_stack.top()->addRef();
	node->setScope(m_scope);

	Value* val = new Value();

	m_scope->pushValue(node->getVar()->getName(), val);

	node->getVar()->accept(*this);

	Visitor::visit(static_cast<NodeArray*>(node->getBlock()));

	m_scope = m_scope->leave();
}

void Resolver::visit(ClassDef* node)
{
	const CString* name = node->getType()->getName();

	UserType* type = new UserType(name);

	m_mod->addType(type);
	type->init();

	Value* tmp = new Value(type);
	m_scope->pushValue(name, tmp);

	m_scope = m_scope->enter();
	m_scope->setEnvironment(new Environment(m_stack.top()));
	m_stack.push(m_scope->getEnvironment());
	node->setScope(m_scope);

	Value* val = new Value(type, true);

	m_scope->pushValue(CSTRING("this"), val);

	type->setEnvironment(m_stack.top());

	m_class = type;

	if (node->hasMembers()) {
		node->getMembers()->accept(*this);
	}

	m_class = NULL;
	m_scope = m_scope->leave();
	m_stack.pop();
}

void Resolver::visit(AttrDecl* node)
{
	const CString* name = node->getIdent()->getName();

	if (m_class->hasMember(name)) {
		Compiler::errorf(node->getLocation(),
			"Cannot redeclare attribute `%S'.", name);
	}

	Value* val = new Value();
	val->setConst(node->isConst());

	if (node->hasValue()) {
		node->getValue()->accept(*this);
	}

	m_class->addProperty(name, val, node->getVisibility());

	node->setScope(m_scope);
}

void Resolver::visit(For* node)
{
	node->setScope(m_scope);

	if (node->hasCondition()) {
		node->getCondition()->accept(*this);
	}

	node->getBlock()->accept(*this);

	if (node->hasUpdate()) {
		Visitor::visit(static_cast<NodeArray*>(node->getUpdate()));
	}
}

}} // clever::ast
