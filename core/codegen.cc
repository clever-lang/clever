/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include <cstdio>

#include "core/codegen.h"
#include "core/compiler.h"
#include "core/cthread.h"
#include "types/thread.h"

namespace clever { namespace ast {

static CLEVER_FORCE_INLINE void _prepare_operand(Operand& op, Node* node)
{
	if (node->isLiteral()) {
		op = Operand(FETCH_CONST, node->getVOffset());
	} else if (node->getScope()) {
		op = Operand(FETCH_VAR, node->getVOffset());
	} else {
		op = Operand(FETCH_TMP, node->getVOffset());
	}
}

Codegen::Codegen(Compiler* compiler, IRBuilder *builder)
	: m_compiler(compiler), m_builder(builder),
	  m_jmps(), m_thread_ids()
{
}

void Codegen::sendArgs(NodeArray* node)
{
	NodeList& args = node->getNodes();

	// First generate code for each argument
	for (size_t i = 0, j = args.size(); i < j; ++i) {
		args[i]->accept(*this);
	}

	// Then send them to the proper call
	for (size_t i = 0, j = args.size(); i < j; ++i) {
		_prepare_operand(m_builder->push(OP_SEND_VAL).op1, args[i]);
	}
}

void Codegen::visit(NullLit* node)
{
	node->setVOffset(m_builder->getNull());
}

void Codegen::visit(TrueLit* node)
{
	node->setVOffset(m_builder->getTrue());
}

void Codegen::visit(FalseLit* node)
{
	node->setVOffset(m_builder->getFalse());
}

void Codegen::visit(IntLit* node)
{
	node->setVOffset(m_builder->getInt(node->getValue()));
}

void Codegen::visit(DoubleLit* node)
{
	node->setVOffset(m_builder->getDouble(node->getValue()));
}

void Codegen::visit(StringLit* node)
{
	node->setVOffset(m_builder->getString(node->getValue()));
}

void Codegen::visit(Ident* node)
{
}

void Codegen::visit(Block* node)
{
	Visitor::visit(static_cast<NodeArray*>(node));
}

void Codegen::visit(CriticalBlock* node)
{
	m_builder->push(OP_LOCK);

	node->getBlock()->accept(*this);

	m_builder->push(OP_UNLOCK);
}

void Codegen::visit(ThreadBlock* node)
{
	if (node->getSize() != NULL) {
		Node* size = node->getSize();
		size->accept(*this);
	}

	size_t bg = m_builder->getSize();
	Symbol* sym = node->getName()->getSymbol();
	Value* threadval = sym->scope->getValue(node->getName()->getVOffset());
	Thread* thread = static_cast<Thread*>(threadval->getObj());
	thread->setAddr(bg);

	size_t m_thread_id = m_thread_ids.size() + 1;
	m_thread_ids[thread] = m_thread_id;
	thread->setID(m_thread_id);

	node->getName()->accept(*this);

	m_builder->push(OP_BTHREAD,
		Operand(JMP_ADDR, bg),
		Operand(FETCH_VAR, node->getName()->getVOffset()));

	if (node->getSize() != NULL) {
		Node* size = node->getSize();
		_prepare_operand(m_builder->getAt(bg).result, size);
	}

	node->getBlock()->accept(*this);

	m_builder->push(OP_ETHREAD);

	m_builder->getAt(bg).op1 = Operand(JMP_ADDR, m_builder->getSize());
}

void Codegen::visit(VariableDecl* node)
{
	node->getAssignment()->accept(*this);
}

void Codegen::visit(Assignment* node)
{
	Node* rhs = node->getRhs();

	if (node->isConditional()) {
		m_builder->push(OP_JMPNZ,
			Operand(FETCH_VAR, node->getLhs()->getVOffset()),
			Operand(JMP_ADDR, m_builder->getSize() + 2));
	}

	if (rhs) {
		rhs->accept(*this);
	}

	IR& assign = m_builder->push(OP_ASSIGN,
		Operand(FETCH_VAR, node->getLhs()->getVOffset()));

	if (!rhs) {
		assign.op2 = Operand(FETCH_CONST, ValueOffset(0, 0)); // null
	} else {
		_prepare_operand(assign.op2, rhs);
	}
}

void Codegen::visit(MethodCall* node)
{
	if (node->isStaticCall()) {
		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_builder->push(OP_SMCALL,
			Operand(FETCH_VAR, static_cast<Ident*>(node->getCallee())->getVOffset()),
			Operand(FETCH_CONST, m_builder->getString(node->getMethod()->getName())));
	} else {
		node->getCallee()->accept(*this);

		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		IR& mcall = m_builder->push(OP_MCALL);

		_prepare_operand(mcall.op1, node->getCallee());

		mcall.op2 = Operand(FETCH_CONST,
			m_builder->getString(node->getMethod()->getName()));
	}

	ValueOffset tmp_id = m_builder->getTemp();

	m_builder->getLast().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(FunctionCall* node)
{
	if (node->getCallee()->isEvaluable()) {
		node->getCallee()->accept(*this);

		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		_prepare_operand(m_builder->push(OP_FCALL).op1, node->getCallee());
	} else {
		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_builder->push(OP_FCALL,
			Operand(FETCH_VAR, node->getCallee()->getVOffset()));
	}

	ValueOffset tmp_id = m_builder->getTemp();

	m_builder->getLast().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(FunctionDecl* node)
{
	IR& start_func = m_builder->push(OP_JMP, Operand(JMP_ADDR, 0));

	Symbol* sym = node->getIdent()->getSymbol();
	Value* funcval = sym->scope->getValue(node->getIdent()->getVOffset());
	Function* func = static_cast<Function*>(funcval->getObj());
	func->setAddr(m_builder->getSize());

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}
	if (node->hasVarArg()) {
		node->getVarArg()->accept(*this);
	}

	node->getBlock()->accept(*this);

	m_builder->push(OP_LEAVE);

	start_func.op1.jmp_addr = m_builder->getSize();

	if (node->isAnonymous()) {
		node->setVOffset(sym->voffset);
		node->setScope(sym->scope);
	}
}

void Codegen::visit(Return* node)
{
	if (node->hasValue()) {
		Node* value = node->getValue();

		value->accept(*this);

		_prepare_operand(m_builder->push(OP_RET).op1, value);
	} else {
		m_builder->push(OP_RET);
	}
}

void Codegen::visit(While* node)
{
	Node* cond = node->getCondition();
	size_t start_while = m_builder->getSize();

	cond->accept(*this);

	IR& jmpz = m_builder->push(OP_JMPZ);

	_prepare_operand(jmpz.op1, cond);

	m_brks.push(AddrVector());
	m_brks.top().push_back(start_while);

	node->getBlock()->accept(*this);

	if (m_brks.top().size() > 1) {
		// Set the break statements jmp address
		for (size_t i = 0, j = m_brks.top().size(); i < j; ++i) {
			m_builder->getAt(m_brks.top()[i]).op1.jmp_addr = m_builder->getSize() + 1;
		}
	}

	m_brks.pop();

	m_builder->push(OP_JMP, Operand(JMP_ADDR, start_while));

	jmpz.op2 = Operand(JMP_ADDR, m_builder->getSize());
}

void Codegen::visit(IncDec* node)
{
	Opcode op = OP_PRE_INC;

	node->getVar()->accept(*this);

	switch (node->getOperator()) {
		case IncDec::PRE_INC: op = OP_PRE_INC; break;
		case IncDec::PRE_DEC: op = OP_PRE_DEC; break;
		case IncDec::POS_INC: op = OP_POS_INC; break;
		case IncDec::POS_DEC: op = OP_POS_DEC; break;
	}

	IR& incdec = m_builder->push(op, Operand(FETCH_VAR, node->getVar()->getVOffset()));

	ValueOffset tmp_id = m_builder->getTemp();

	incdec.result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Arithmetic* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_ADD;

	switch (node->getOperator()) {
		case Arithmetic::MOP_ADD: op = OP_ADD; break;
		case Arithmetic::MOP_SUB: op = OP_SUB; break;
		case Arithmetic::MOP_MUL: op = OP_MUL; break;
		case Arithmetic::MOP_DIV: op = OP_DIV; break;
		case Arithmetic::MOP_MOD: op = OP_MOD; break;
	}

	lhs->accept(*this);
	rhs->accept(*this);

	IR& arith = m_builder->push(op);

	_prepare_operand(arith.op1, lhs);
	_prepare_operand(arith.op2, rhs);

	ValueOffset tmp_id = m_builder->getTemp();

	arith.result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Comparison* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_ADD;

	switch (node->getOperator()) {
		case Comparison::COP_EQUAL:   op = OP_EQUAL;   break;
		case Comparison::COP_NEQUAL:  op = OP_NEQUAL;  break;
		case Comparison::COP_GREATER: op = OP_GREATER; break;
		case Comparison::COP_GEQUAL:  op = OP_GEQUAL;  break;
		case Comparison::COP_LESS:    op = OP_LESS;    break;
		case Comparison::COP_LEQUAL:  op = OP_LEQUAL;  break;
	}

	lhs->accept(*this);
	rhs->accept(*this);

	IR& comp = m_builder->push(op);

	_prepare_operand(comp.op1, lhs);
	_prepare_operand(comp.op2, rhs);

	ValueOffset tmp_id = m_builder->getTemp();

	comp.result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Logic* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_EQUAL;

	switch (node->getOperator()) {
		case Logic::LOP_AND: op = OP_AND; break;
		case Logic::LOP_OR:  op = OP_OR;  break;
	}

	lhs->accept(*this);

	size_t jmp_ir = m_builder->getSize();
	ValueOffset res_id = m_builder->getTemp();

	node->setVOffset(res_id);

	_prepare_operand(m_builder->push(op).op1, lhs);
	m_builder->getLast().result = Operand(FETCH_TMP, res_id);

	rhs->accept(*this);

	_prepare_operand(m_builder->push(op).op1, rhs);
	m_builder->getLast().result = Operand(FETCH_TMP, res_id);

	m_builder->getLast().op2 = m_builder->getAt(jmp_ir).op2 = Operand(JMP_ADDR, m_builder->getSize());
}

void Codegen::visit(Boolean* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_JMPZ;

	switch (node->getOperator()) {
		case Boolean::BOP_AND: op = OP_JMPZ;  break;
		case Boolean::BOP_OR:  op = OP_JMPNZ; break;
	}

	lhs->accept(*this);

	size_t jmp_ir = m_builder->getSize();
	ValueOffset res_id = m_builder->getTemp();

	node->setVOffset(res_id);

	_prepare_operand(m_builder->push(op).op1, lhs);
	m_builder->getLast().result = Operand(FETCH_TMP, res_id);

	rhs->accept(*this);

	_prepare_operand(m_builder->push(op).op1, rhs);
	m_builder->getLast().result = Operand(FETCH_TMP, res_id);

	m_builder->getLast().op2 = m_builder->getAt(jmp_ir).op2 = Operand(JMP_ADDR, m_builder->getSize());
}

void Codegen::visit(If* node)
{

	std::vector<std::pair<Node*, Node*> >& branches = node->getConditionals();
	std::vector<std::pair<Node*, Node*> >::const_iterator it(branches.begin()),
		end(branches.end());

	m_jmps.push(AddrVector());

	while (it != end) {
		Node* cond  = (*it).first;
		Node* block = (*it).second;

		cond->accept(*this);

		IR& last_jmpz = m_builder->push(OP_JMPZ);

		_prepare_operand(last_jmpz.op1, cond);

		block->accept(*this);

		m_jmps.top().push_back(m_builder->getSize());
		m_builder->push(OP_JMP); // JMP to outside if-elseif-else

		last_jmpz.op2 = Operand(JMP_ADDR, m_builder->getSize());

		++it;
	}

	if (node->getElseNode()) {
		node->getElseNode()->accept(*this);
	}

	AddrVector& vec = m_jmps.top();
	for (size_t i = 0, j = vec.size(); i < j; ++i) {
		m_builder->getAt(vec[i]).op1 = Operand(JMP_ADDR, m_builder->getSize());
	}

	m_jmps.pop();
}

void Codegen::visit(Instantiation* node)
{
	if (node->hasArgs()) {
		sendArgs(node->getArgs());
	}

	IR& inst = m_builder->push(OP_NEW, Operand(FETCH_VAR, node->getType()->getVOffset()));

	ValueOffset tmp_id = m_builder->getTemp();

	inst.result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Property* node)
{
	node->getCallee()->accept(*this);

	IR& acc = m_builder->push(OP_PROP_ACC);

	_prepare_operand(acc.op1, node->getCallee());

	acc.op2 = Operand(FETCH_CONST, m_builder->getString(node->getProperty()->getName()));

	ValueOffset tmp_id = m_builder->getTemp();

	acc.result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Try* node)
{
	IR& try_start = m_builder->push(OP_TRY);

	node->getBlock()->accept(*this);

	IR& try_jmp = m_builder->push(OP_JMP); // It's all ok, jump to finally block

	NodeList& catches = node->getCatches()->getNodes();
	NodeList::const_iterator it(catches.begin()), end(catches.end());

	try_start.op1 = Operand(JMP_ADDR, m_builder->getSize());

	while (it != end) {
		IR& catch_start = m_builder->push(OP_CATCH);

		(*it)->accept(*this);

		_prepare_operand(catch_start.op1, static_cast<Catch*>(*it)->getVar());
		++it;
	}

	try_jmp.op1 = Operand(JMP_ADDR, m_builder->getSize());

	if (node->hasFinally()) {
		node->getFinally()->accept(*this);
	}

	m_builder->push(OP_ETRY);
}

void Codegen::visit(Throw* node)
{
	node->getExpr()->accept(*this);

	IR& thr = m_builder->push(OP_THROW);

	_prepare_operand(thr.op1, node->getExpr());
}

void Codegen::visit(Continue* node)
{
	m_builder->push(OP_JMP, Operand(JMP_ADDR, m_brks.top().front()));
}

void Codegen::visit(Break* node)
{
	m_brks.top().push_back(m_builder->getSize());
	m_builder->push(OP_JMP, Operand(JMP_ADDR, 0));
}

void Codegen::visit(ClassDef* node)
{
	if (node->hasMethods()) {
		node->getMethods()->accept(*this);
	}
}

}} // clever::ast
