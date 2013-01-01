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

static inline void _prepare_operand(Operand& op, Node* node)
{
	if (node->isLiteral()) {
		op = Operand(FETCH_CONST, static_cast<Literal*>(node)->getConstId());
	} else if (node->getScope()) {
		op = Operand(FETCH_VAR, node->getValueId(),	node->getScope()->getId());
	} else {
		op = Operand(FETCH_TMP, node->getValueId());
	}
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
	node->setScope(sym->scope);
}

void Codegen::visit(Block* node)
{
	m_scope = node->getScope();

	Visitor::visit(static_cast<NodeArray*>(node));

	m_scope = m_scope->getParent();
}

void Codegen::visit(VariableDecl* node)
{
	node->getAssignment()->accept(*this);
}

void Codegen::visit(Assignment* node)
{
	// TODO: allow assignment of any possible left hand side.
	Symbol* sym = static_cast<Ident*>(node->getLhs())->getSymbol();
	Node* rhs = node->getRhs();

	clever_assert_not_null(sym);

	if (node->isConditional()) {
		m_ir.push_back(IR(OP_JMPNZ,
			Operand(FETCH_VAR, sym->value_id, sym->scope->getId()),
			Operand(JMP_ADDR, m_ir.size() + 2)));
	}

	if (rhs) {
		rhs->accept(*this);
	}
	m_ir.push_back(IR(OP_ASSIGN,
			Operand(FETCH_VAR, sym->value_id, sym->scope->getId())));

	if (!rhs) {
		m_ir.back().op2 = Operand(FETCH_TMP, m_compiler->getTempValue());
	} else {
		_prepare_operand(m_ir.back().op2, rhs);
	}
}

void Codegen::visit(FunctionCall* node)
{
	// TODO: allow call for any possible callee
	Symbol* sym = static_cast<Ident*>(node->getCallee())->getSymbol();

	clever_assert_not_null(sym);

	if (node->hasArgs()) {
		NodeList& args = node->getArgs()->getNodes();
		NodeList::const_iterator it = args.begin(), end = args.end();

		while (it != end) {
			(*it)->accept(*this);

			m_ir.push_back(IR(OP_SEND_VAL));

			_prepare_operand(m_ir.back().op1, *it);
			++it;
		}
	}

	m_ir.push_back(IR(OP_FCALL,
		Operand(FETCH_VAR, sym->value_id, sym->scope->getId())));

	size_t tmp_id = m_compiler->getTempValue();

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setValueId(tmp_id);
}

void Codegen::visit(FunctionDecl* node)
{
	size_t start_func = m_ir.size();

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, 0)));

	Symbol* sym = node->getIdent()->getSymbol();
	Value* funcval = sym->scope->getValue(sym->value_id);
	Function* func = static_cast<Function*>(funcval->getObj());
	func->setAddr(m_ir.size());

	m_scope = node->getScope();

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}

	node->getBlock()->accept(*this);

	m_scope = m_scope->getParent();

	m_ir.push_back(IR(OP_LEAVE));

	m_ir[start_func].op1.value_id = m_ir.size();

	if (node->isAnonymous()) {
		node->setValueId(sym->value_id);
		node->setScope(sym->scope);
	}
}

void Codegen::visit(Return* node)
{
	if (node->hasValue()) {
		Node* value = node->getValue();

		value->accept(*this);

		m_ir.push_back(IR(OP_RET));

		_prepare_operand(m_ir.back().op1, value);
	} else {
		m_ir.push_back(IR(OP_RET));
	}
}

void Codegen::visit(While* node)
{
	size_t start_while = m_ir.size();
	Node* cond = node->getCondition();

	cond->accept(*this);

	m_ir.push_back(IR(OP_JMPZ));

	_prepare_operand(m_ir.back().op1, cond);

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
			node->getVar()->getScope()->getId())));

	size_t tmp_id = m_compiler->getTempValue();

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setValueId(tmp_id);
}

void Codegen::visit(Arithmetic* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op;

	switch (node->getOperator()) {
		case Arithmetic::MOP_ADD: op = OP_ADD; break;
		case Arithmetic::MOP_SUB: op = OP_SUB; break;
		case Arithmetic::MOP_MUL: op = OP_MUL; break;
		case Arithmetic::MOP_DIV: op = OP_DIV; break;
		case Arithmetic::MOP_MOD: op = OP_MOD; break;
	}

	lhs->accept(*this);
	rhs->accept(*this);

	m_ir.push_back(IR(op));

	_prepare_operand(m_ir.back().op1, lhs);
	_prepare_operand(m_ir.back().op2, rhs);

	size_t tmp_id = m_compiler->getTempValue();

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setValueId(tmp_id);
}

void Codegen::visit(Logic* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op;

	switch (node->getOperator()) {
		case Logic::LOP_EQUALS: op = OP_EQUAL; break;
		case Logic::LOP_AND:    op = OP_AND;   break;
		case Logic::LOP_OR:     op = OP_OR;    break;
	}

	lhs->accept(*this);
	rhs->accept(*this);

	m_ir.push_back(IR(op));

	_prepare_operand(m_ir.back().op1, lhs);
	_prepare_operand(m_ir.back().op2, rhs);

	size_t tmp_id = m_compiler->getTempValue();

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setValueId(tmp_id);
}

void Codegen::visit(If* node)
{
	size_t last_jmpz = 0;
	std::vector<std::pair<Node*, Node*> >& branches = node->getConditionals();
	std::vector<std::pair<Node*, Node*> >::const_iterator it(branches.begin()),
		end(branches.end());

	m_jmps.push(AddrVector());

	while (it != end) {
		Node* cond  = (*it).first;
		Node* block = (*it).second;

		cond->accept(*this);

		last_jmpz = m_ir.size();
		m_ir.push_back(IR(OP_JMPZ));

		_prepare_operand(m_ir.back().op1, cond);

		block->accept(*this);

		m_jmps.top().push_back(m_ir.size());
		m_ir.push_back(IR(OP_JMP)); // JMP to outside if-elseif-else

		m_ir[last_jmpz].op2 = Operand(JMP_ADDR, m_ir.size());

		++it;
	}

	if (node->getElseNode()) {
		node->getElseNode()->accept(*this);
	}

	AddrVector& vec = m_jmps.top();
	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		m_ir[vec[i]].op1 = Operand(JMP_ADDR, m_ir.size());
	}

	m_jmps.pop();
}

}} // clever::ast
