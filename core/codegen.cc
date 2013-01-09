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

Codegen::Codegen(IRVector& ir, Compiler* compiler, Environment* init_glbenv)
	: m_ir(ir), m_compiler(compiler), m_init_glbenv(init_glbenv),
	  m_thread_ids() {

	m_const_env = new Environment(m_init_glbenv);
	m_temp_env  = new Environment(m_init_glbenv);

	// Add 'null', true and false to the constant pool
	m_const_env->pushValue(new Value());
	m_const_env->pushValue(new Value(true));
	m_const_env->pushValue(new Value(false));
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
		m_ir.push_back(IR(OP_SEND_VAL));
		_prepare_operand(m_ir.back().op1, args[i]);
	}
}

void Codegen::visit(NullLit* node)
{
	node->setVOffset(ValueOffset(0,0));
}

void Codegen::visit(TrueLit* node)
{
	node->setVOffset(ValueOffset(0,1));
}

void Codegen::visit(FalseLit* node)
{
	node->setVOffset(ValueOffset(0,2));
}

void Codegen::visit(IntLit* node)
{
	node->setVOffset(m_const_env->pushValue(new Value(node->getValue())));
}

void Codegen::visit(DoubleLit* node)
{
	node->setVOffset(m_const_env->pushValue(new Value(node->getValue())));
}

void Codegen::visit(StringLit* node)
{
	node->setVOffset(m_const_env->pushValue(new Value(node->getValue())));
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
	m_ir.push_back(IR(OP_LOCK));

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_UNLOCK));
}


void Codegen::visit(Wait* node)
{
	m_ir.push_back(IR(OP_WAIT,
					  Operand(FETCH_VAR, node->getName()->getVOffset())
					  ));
}

void Codegen::visit(ThreadBlock* node)
{
	enable_threads();

	if (node->getSize() != NULL) {
		Node* size = node->getSize();
		size->accept(*this);
	}

	size_t bg = m_ir.size();
	Symbol* sym = node->getName()->getSymbol();
	Value* threadval = sym->scope->getValue(node->getName()->getVOffset());
	Thread* thread = static_cast<Thread*>(threadval->getObj());
	thread->setAddr(bg);


	size_t m_thread_id = m_thread_ids.size() + 1;
	m_thread_ids[thread] = m_thread_id;
	thread->setID(m_thread_id);

	node->getName()->accept(*this);

	m_ir.push_back(IR(OP_BTHREAD,
					  Operand(JMP_ADDR, bg),
					  Operand(FETCH_VAR, node->getName()->getVOffset())));

	if (node->getSize() != NULL) {
		Node* size = node->getSize();
		_prepare_operand(m_ir[bg].result, size);
	}

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_ETHREAD));

	m_ir[bg].op1 = Operand(JMP_ADDR, m_ir.size());
}

void Codegen::visit(VariableDecl* node)
{
	node->getAssignment()->accept(*this);
}

void Codegen::visit(Assignment* node)
{
	Node* rhs = node->getRhs();

	if (node->isConditional()) {
		m_ir.push_back(IR(OP_JMPNZ,
			Operand(FETCH_VAR, node->getLhs()->getVOffset()),
			Operand(JMP_ADDR, m_ir.size() + 2)));
	}

	if (rhs) {
		rhs->accept(*this);
	}
	m_ir.push_back(IR(OP_ASSIGN,
			Operand(FETCH_VAR, node->getLhs()->getVOffset())));

	if (!rhs) {
		m_ir.back().op2 = Operand(FETCH_CONST, 0); // null
	} else {
		_prepare_operand(m_ir.back().op2, rhs);
	}
}

void Codegen::visit(MethodCall* node)
{
	if (node->isStaticCall()) {
		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_ir.push_back(IR(OP_SMCALL,
					Operand(FETCH_VAR, static_cast<Ident*>(node->getCallee())->getVOffset()),
					Operand(FETCH_CONST,
						 m_const_env->pushValue(new Value(node->getMethod()->getName())))));
	} else {
		node->getCallee()->accept(*this);

		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_ir.push_back(IR(OP_MCALL));

		_prepare_operand(m_ir.back().op1, node->getCallee());

		m_ir.back().op2 = Operand(FETCH_CONST,
					m_const_env->pushValue(new Value(node->getMethod()->getName())));
	}

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(FunctionCall* node)
{
	if (node->getCallee()->isEvaluable()) {
		node->getCallee()->accept(*this);

		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_ir.push_back(IR(OP_FCALL));
		_prepare_operand(m_ir.back().op1, node->getCallee());
	} else {
		Symbol* sym = static_cast<Ident*>(node->getCallee())->getSymbol();
		clever_assert_not_null(sym);

		if (node->hasArgs()) {
			sendArgs(node->getArgs());
		}

		m_ir.push_back(IR(OP_FCALL,
			Operand(FETCH_VAR, node->getCallee()->getVOffset())));
	}

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(FunctionDecl* node)
{
	size_t start_func = m_ir.size();

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, 0)));

	Symbol* sym = node->getIdent()->getSymbol();
	Value* funcval = sym->scope->getValue(node->getIdent()->getVOffset());
	Function* func = static_cast<Function*>(funcval->getObj());
	func->setAddr(m_ir.size());

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_LEAVE));

	m_ir[start_func].op1.jmp_addr = m_ir.size();

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

		m_ir.push_back(IR(OP_RET));

		_prepare_operand(m_ir.back().op1, value);
	} else {
		m_ir.push_back(IR(OP_RET));
	}
}

void Codegen::visit(While* node)
{
	Node* cond = node->getCondition();
	size_t start_while = m_ir.size();

	cond->accept(*this);

	size_t jmp_addr = m_ir.size();

	m_ir.push_back(IR(OP_JMPZ));

	_prepare_operand(m_ir.back().op1, cond);

	node->getBlock()->accept(*this);

	m_ir.push_back(IR(OP_JMP, Operand(JMP_ADDR, start_while)));

	m_ir[jmp_addr].op2 = Operand(JMP_ADDR, m_ir.size());
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

	m_ir.push_back(IR(op,
		Operand(FETCH_VAR, node->getVar()->getVOffset())));

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

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

	m_ir.push_back(IR(op));

	_prepare_operand(m_ir.back().op1, lhs);
	_prepare_operand(m_ir.back().op2, rhs);

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

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

	m_ir.push_back(IR(op));

	_prepare_operand(m_ir.back().op1, lhs);
	_prepare_operand(m_ir.back().op2, rhs);

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

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

	size_t jmp_ir = m_ir.size();
	ValueOffset res_id = m_temp_env->pushValue(new Value());

	node->setVOffset(res_id);

	m_ir.push_back(IR(op));
	_prepare_operand(m_ir.back().op1, lhs);
	m_ir.back().result = Operand(FETCH_TMP, res_id);

	rhs->accept(*this);

	m_ir.push_back(IR(op));
	_prepare_operand(m_ir.back().op1, rhs);
	m_ir.back().result = Operand(FETCH_TMP, res_id);

	m_ir.back().op2 = m_ir[jmp_ir].op2 = Operand(JMP_ADDR, m_ir.size());
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

	size_t jmp_ir = m_ir.size();
	ValueOffset res_id = m_temp_env->pushValue(new Value());

	node->setVOffset(res_id);

	m_ir.push_back(IR(op));
	_prepare_operand(m_ir.back().op1, lhs);
	m_ir.back().result = Operand(FETCH_TMP, res_id);

	rhs->accept(*this);

	m_ir.push_back(IR(op));
	_prepare_operand(m_ir.back().op1, rhs);
	m_ir.back().result = Operand(FETCH_TMP, res_id);

	m_ir.back().op2 = m_ir[jmp_ir].op2 = Operand(JMP_ADDR, m_ir.size());
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

void Codegen::visit(Instantiation* node)
{
	if (node->hasArgs()) {
		sendArgs(node->getArgs());
	}

	m_ir.push_back(IR(OP_NEW, Operand(FETCH_VAR, node->getType()->getVOffset())));

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Property* node)
{
	node->getObject()->accept(*this);

	m_ir.push_back(IR(OP_PROP_ACC));

	_prepare_operand(m_ir.back().op1, node->getObject());

	m_ir.back().op2 = Operand(FETCH_CONST,
			m_const_env->pushValue(new Value(node->getProperty()->getName())));

	ValueOffset tmp_id = m_temp_env->pushValue(new Value());

	m_ir.back().result = Operand(FETCH_TMP, tmp_id);

	node->setVOffset(tmp_id);
}

void Codegen::visit(Try* node)
{
	size_t try_id = m_ir.size();
	size_t try_jmp;

	m_ir.push_back(OP_TRY);

	node->getBlock()->accept(*this);

	try_jmp = m_ir.size();
	m_ir.push_back(OP_JMP); // It's all ok, jump to finally block

	NodeList& catches = node->getCatches()->getNodes();
	NodeList::const_iterator it(catches.begin()), end(catches.end());

	m_ir[try_id].op1 = Operand(JMP_ADDR, m_ir.size());

	while (it != end) {
		size_t catch_id = m_ir.size();
		m_ir.push_back(OP_CATCH);

		(*it)->accept(*this);

		_prepare_operand(m_ir[catch_id].op1, static_cast<Catch*>(*it)->getVar());
		++it;
	}

	m_ir[try_jmp].op1 = Operand(JMP_ADDR, m_ir.size());

	if (node->hasFinally()) {
		node->getFinally()->accept(*this);
	}

	m_ir.push_back(IR(OP_ETRY));
}

void Codegen::visit(Throw* node)
{
	node->getExpr()->accept(*this);

	m_ir.push_back(IR(OP_THROW));

	_prepare_operand(m_ir.back().op1, node->getExpr());
}

}} // clever::ast


