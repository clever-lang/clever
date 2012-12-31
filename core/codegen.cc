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

void Codegen::visit(Ident* node)
{
	Symbol* sym = m_scope->getAny(node->getName());

	if (!sym) {
		Compiler::errorf(node->getLocation(),
			"Variable `%S' not found!", node->getName());
	}

	node->setValueId(sym->value_id);
	node->setScopeId(sym->scope->getId());
}

void Codegen::visit(Import* node)
{
	if (node->getModule()) {
		m_compiler->getPkgManager().importModule(m_scope,
			node->getPackage()->getName(), node->getModule()->getName());
	} else {
		m_compiler->getPkgManager().importPackage(m_scope,
			node->getPackage()->getName());
	}
}

void Codegen::visit(Block* node)
{
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(m_scope_id);
	m_scope_pool[m_scope_id++] = m_scope;

	Visitor::visit(static_cast<NodeArray*>(node));

	m_scope = m_scope->getParent();
}

void Codegen::visit(VariableDecl* node)
{
	m_scope->pushValue(node->getIdent()->getName(), new Value());
	node->getAssignment()->accept(*this);
}

void Codegen::visit(Assignment* node)
{
	// TODO: allow assignment of any possible left hand side.
	Ident* ident = static_cast<Ident*>(node->getLhs());
	Symbol* sym = m_scope->getLocal(ident->getName());
	Node* rhs = node->getRhs();

	clever_assert_not_null(sym);

	if (node->isConditional()) {
		m_ir.push_back(IR(OP_JMPNZ,
			Operand(FETCH_VAR, sym->value_id, sym->scope->getId()),
			Operand(JMP_ADDR, m_ir.size() + 2)));
	}

	m_ir.push_back(IR(OP_ASSIGN,
		Operand(FETCH_VAR, sym->value_id, sym->scope->getId())));

	if (!rhs) {
		m_ir.back().op2 = Operand(FETCH_TMP, m_compiler->getTempValue());
	} else {
		rhs->accept(*this);

		if (rhs->isLiteral()) {
			m_ir.back().op2 = Operand(FETCH_CONST,
				static_cast<Literal*>(rhs)->getConstId());
		} else {
			m_ir.back().op2 = Operand(FETCH_VAR,
				rhs->getValueId(), rhs->getScopeId());
		}
	}
}

void Codegen::visit(FunctionCall* node)
{
	Ident* ident = static_cast<Ident*>(node->getCallee());
	Symbol* sym = m_scope->getAny(ident->getName());

	if (!sym) {
		Compiler::errorf(node->getLocation(),
			"Function `%S' not found!", ident->getName());
	}

	if (node->hasArgs()) {
		NodeList& args = node->getArgs()->getNodes();
		NodeList::const_iterator it = args.begin(), end = args.end();

		while (it != end) {
			Operand operand;

			(*it)->accept(*this);

			if ((*it)->isLiteral()) {
				operand.op_type = FETCH_CONST;
				operand.value_id = static_cast<Literal*>(*it)->getConstId();
			} else {
				operand.op_type = (*it)->isEvaluable() ? FETCH_TMP : FETCH_VAR;
				operand.value_id = (*it)->getValueId();
				operand.scope_id = (*it)->getScopeId();
			}
			m_ir.push_back(IR(OP_SEND_VAL, operand));
			++it;
		}
	}

	m_ir.push_back(IR(OP_FCALL,
		Operand(FETCH_VAR, sym->value_id, sym->scope->getId())));
}

void Codegen::visit(FunctionDecl* node)
{
	const CString* name = node->getIdent()->getName();
	Symbol* sym = m_scope->getLocal(name);
	size_t start_func;

	if (sym) {
		Compiler::errorf(node->getLocation(),
			"Function `%S' already defined in the scope!", name);
	}

	Function* func = static_cast<Function*>(CLEVER_FUNC_TYPE->allocData());

	func->setName(*name);
	func->setUserDefined();
	func->setAddr(m_ir.size()+1);

	Value* fval = new Value();
	fval->setType(CLEVER_FUNC_TYPE);
	fval->setObj(func);

	m_scope->pushValue(name, fval);

	start_func = m_ir.size();

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, 0)));

	// TODO: find a cleaner way to enter and leave scopes
	m_scope = m_scope->newLexicalScope();
	m_scope->setId(m_scope_id);
	m_scope_pool[m_scope_id++] = m_scope;

	if (node->hasArgs()) {
		for (size_t i = 0; i < node->numArgs(); ++i) {
			static_cast<VariableDecl*>(node->getArg(i))->getAssignment()->setConditional(true);
		}

		node->getArgs()->accept(*this);

		func->setArgVars(m_scope);
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
	Node* cond = node->getCondition();

	cond->accept(*this);

	if (cond->isLiteral()) {
		m_ir.push_back(IR(OP_JMPZ,
			Operand(FETCH_CONST, static_cast<Literal*>(cond)->getConstId())));
	} else {
		m_ir.push_back(IR(OP_JMPZ,
			Operand(FETCH_VAR, cond->getValueId(), cond->getScopeId())));
	}

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, start_while)));

	m_ir[start_while].op2.value_id = m_ir.size();
}

void Codegen::visit(IncDec* node)
{
	Opcode op;

	node->getVar()->accept(*this);

	switch (node->getOperator()) {
		case IncDec::PRE_INC: op = OP_PRE_INC; break;
		case IncDec::PRE_DEC: op = OP_PRE_DEC; break;
		case IncDec::POS_INC: op = OP_POS_INC; break;
		case IncDec::POS_DEC: op = OP_POS_DEC; break;
	}

	m_ir.push_back(IR(op,
		Operand(FETCH_VAR, node->getVar()->getValueId(),
			node->getVar()->getScopeId())));

	size_t tmp_id = m_compiler->getTempValue();

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setValueId(tmp_id);
}

}} // clever::ast
