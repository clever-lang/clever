/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include <cstdio>

#include "core/compiler.h"
#include "core/codegen.h"
#include "core/irbuilder.h"
#include "modules/std/core/function.h"

namespace clever { namespace ast {

static CLEVER_FORCE_INLINE void _prepare_operand(Operand& op, Node* node)
{
	op = Operand(node->isLiteral() ? FETCH_CONST :
		(node->getScope() ? FETCH_VAR : FETCH_TMP),
		node->getVOffset());
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

	node->getLhs()->accept(*this);

	if (rhs) {
		rhs->accept(*this);
	}

	IR& assign = m_builder->push(OP_ASSIGN);

	assign.loc = node->getLocation();

	_prepare_operand(assign.op1, node->getLhs());

	if (!rhs) {
		assign.op2 = Operand(FETCH_CONST, ValueOffset(0, 0)); // null
	} else {
		_prepare_operand(assign.op2, rhs);
	}

	if (node->hasResult()) {
		ValueOffset tmp_id = m_builder->getTemp();
		assign.result = Operand(FETCH_TMP, tmp_id);
		node->setVOffset(tmp_id);
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
	m_builder->getLast().loc = node->getLocation();

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
	m_builder->getLast().loc = node->getLocation();

	node->setVOffset(tmp_id);
}

void Codegen::visit(FunctionDecl* node)
{
	IR& start_func = m_builder->push(OP_JMP, Operand(JMP_ADDR, 0));
	Symbol* sym = NULL;
	Function* func;

	if (node->isMethod()) {
		func = node->getMethod();
	} else {
		sym = node->getIdent()->getSymbol();

		const ValueOffset& offset = node->getIdent()->getVOffset();

		Value* funcval = sym->scope->getValue(offset);
		func = static_cast<Function*>(funcval->getObj());
	}
	func->setAddr(m_builder->getSize());

	Environment* save_temp = m_builder->getTempEnv();
	Environment* temp_env  = m_builder->getNewTempEnv();

	func->getEnvironment()->setTempEnv(temp_env);

	if (node->hasArgs()) {
		node->getArgs()->accept(*this);
	}
	if (node->hasVarArg()) {
		node->getVarArg()->accept(*this);
	}

	node->getBlock()->accept(*this);

	m_builder->push(OP_LEAVE);

	start_func.op1.jmp_addr = m_builder->getSize();

	if (sym && node->isAnonymous()) {
		node->setVOffset(sym->voffset);
		node->setScope(sym->scope);
	}

	m_builder->setTempEnv(save_temp);
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

void Codegen::visit(For* node)
{
	bool is_foreach = node->hasVar();

	if (is_foreach) {
		node->getVar()->accept(*this);
		node->getExpr()->accept(*this);
		node->getBlock()->accept(*this);
	} else {
		if (node->hasInitializer()) {
			node->getInitializer()->accept(*this);
		}

		size_t start_while = m_builder->getSize();

		Node* condition = node->getCondition();
		IR* jmpz = NULL;

		if (condition) {
			condition->accept(*this);

			jmpz = &m_builder->push(OP_JMPZ);

			_prepare_operand(jmpz->op1, condition);
		}

		m_cont.push(AddrVector());
		m_brks.push(AddrVector());
		m_brks.top().push_back(start_while);

		node->getBlock()->accept(*this);

		if (!m_cont.top().empty()) {
			// Set the continue statements jmp address
			for (size_t i = 0, j = m_cont.top().size(); i < j; ++i) {
				m_builder->getAt(m_cont.top()[i]).op1.jmp_addr = m_builder->getSize();
			}
		}
		m_cont.pop();

		if (node->hasUpdate()) {
			node->getUpdate()->accept(*this);
		}

		m_builder->push(OP_JMP, Operand(JMP_ADDR, start_while));

		if (condition) {
			jmpz->op2 = Operand(JMP_ADDR, m_builder->getSize());
		}

		if (!m_brks.top().empty()) {
			// Set the break statements jmp address
			for (size_t i = 0, j = m_brks.top().size(); i < j; ++i) {
				m_builder->getAt(m_brks.top()[i]).op1.jmp_addr = m_builder->getSize();
			}
		}
		m_brks.pop();
	}
}

void Codegen::visit(While* node)
{
	Node* cond = node->getCondition();
	size_t start_while = m_builder->getSize();

	cond->accept(*this);

	IR& jmpz = m_builder->push(OP_JMPZ);

	_prepare_operand(jmpz.op1, cond);

	m_cont.push(AddrVector());
	m_brks.push(AddrVector());
	m_brks.top().push_back(start_while);

	node->getBlock()->accept(*this);

	if (!m_brks.top().empty()) {
		// Set the break statements jmp address
		for (size_t i = 0, j = m_brks.top().size(); i < j; ++i) {
			m_builder->getAt(m_brks.top()[i]).op1.jmp_addr = m_builder->getSize() + 1;
		}
	}

	m_cont.pop();
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

	IR& incdec = m_builder->push(op);

	_prepare_operand(incdec.op1, node->getVar());

	ValueOffset tmp_id = m_builder->getTemp();

	incdec.result = Operand(FETCH_TMP, tmp_id);
	incdec.loc = node->getLocation();

	node->setVOffset(tmp_id);
}

void Codegen::visit(Bitwise* node)
{
	Node* lhs = node->getLhs();
	Node* rhs = node->getRhs();
	Opcode op = OP_ADD;

	switch (node->getOperator()) {
		case Bitwise::BOP_AND:    op = OP_BW_AND; break;
		case Bitwise::BOP_OR:     op = OP_BW_OR;  break;
		case Bitwise::BOP_XOR:    op = OP_BW_XOR; break;
		case Bitwise::BOP_NOT:    op = OP_BW_NOT; break;
		case Bitwise::BOP_LSHIFT: op = OP_BW_LS;  break;
		case Bitwise::BOP_RSHIFT: op = OP_BW_RS;  break;
	}

	lhs->accept(*this);
	if (rhs) {
		rhs->accept(*this);
	}

	IR& arith = m_builder->push(op);

	_prepare_operand(arith.op1, lhs);

	if (rhs) {
		_prepare_operand(arith.op2, rhs);

		if (node->isAugmented()) {
			_prepare_operand(arith.result, lhs);

			node->setVOffset(lhs->getVOffset());
			node->setScope(lhs->getScope());

			return;
		}
	}

	ValueOffset tmp_id = m_builder->getTemp();

	arith.result = Operand(FETCH_TMP, tmp_id);
	arith.loc = node->getLocation();

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

	if (node->isAugmented()) {
		_prepare_operand(arith.result, lhs);

		node->setVOffset(lhs->getVOffset());
		node->setScope(lhs->getScope());
	} else {
		ValueOffset tmp_id = m_builder->getTemp();

		arith.result = Operand(FETCH_TMP, tmp_id);
		arith.loc = node->getLocation();

		node->setVOffset(tmp_id);
	}
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
	comp.loc = node->getLocation();

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
		case Boolean::BOP_NOT: op = OP_NOT;   break;
	}

	lhs->accept(*this);

	size_t jmp_ir = m_builder->getSize();
	ValueOffset res_id = m_builder->getTemp();

	node->setVOffset(res_id);

	_prepare_operand(m_builder->push(op).op1, lhs);
	m_builder->getLast().result = Operand(FETCH_TMP, res_id);

	if (rhs) {
		rhs->accept(*this);

		_prepare_operand(m_builder->push(op).op1, rhs);
		m_builder->getLast().result = Operand(FETCH_TMP, res_id);

		m_builder->getLast().op2 = m_builder->getAt(jmp_ir).op2 = Operand(JMP_ADDR, m_builder->getSize());
	}
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
	inst.loc = node->getLocation();

	node->setVOffset(tmp_id);
}

void Codegen::visit(Property* node)
{
	node->getCallee()->accept(*this);
	Opcode op;

	if (node->isStatic()) {
		op = node->getMode() == Property::WRITE ? OP_SPROP_W : OP_SPROP_R;
	} else {
		op = node->getMode() == Property::WRITE ? OP_PROP_W : OP_PROP_R;
	}

	IR& acc = m_builder->push(op);

	_prepare_operand(acc.op1, node->getCallee());

	acc.op2 = Operand(FETCH_CONST, m_builder->getString(node->getProperty()->getName()));

	ValueOffset tmp_id = m_builder->getTemp();

	acc.result = Operand(FETCH_TMP, tmp_id);
	acc.loc = node->getLocation();

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

	thr.loc = node->getLocation();
}

void Codegen::visit(Continue* node)
{
	m_cont.top().push_back(m_builder->getSize());
	m_builder->push(OP_JMP, Operand(JMP_ADDR, m_brks.top().front()));
}

void Codegen::visit(Break* node)
{
	m_brks.top().push_back(m_builder->getSize());
	m_builder->push(OP_JMP, Operand(JMP_ADDR, 0));
}

void Codegen::visit(ClassDef* node)
{
	Environment* save_temp = m_builder->getTempEnv();
	Environment* temp_env = m_builder->getNewTempEnv();

	node->getScope()->getEnvironment()->setTempEnv(temp_env);

	if (node->hasMembers()) {
		node->getMembers()->accept(*this);
	}

	m_builder->setTempEnv(save_temp);
}

void Codegen::visit(Import* node)
{
	if (node->hasModuleTree()) {
		Visitor::visit(static_cast<NodeArray*>(node->getModuleTree()));
	}
}

void Codegen::visit(Subscript* node)
{
	node->getVar()->accept(*this);
	node->getIndex()->accept(*this);

	IR& subscript = m_builder->push(OP_SUBSCRIPT);

	_prepare_operand(subscript.op1, node->getVar());
	_prepare_operand(subscript.op2, node->getIndex());

	ValueOffset tmp_id = m_builder->getTemp();

	subscript.result = Operand(FETCH_TMP, tmp_id);
	subscript.loc = node->getLocation();

	node->setVOffset(tmp_id);
}

void Codegen::visit(Switch* node)
{
	node->getExpr()->accept(*this);

	std::vector<std::pair<Node*, Node*> >& cases = node->getCases();
	std::vector<std::pair<Node*, Node*> >::const_iterator it(cases.begin()),
		end(cases.end());

	size_t default_addr = 0, ncases = cases.size();
	IR* last_jmp  = NULL;
	IR* last_jmpz = NULL;

	m_brks.push(AddrVector());

	for (; it != end; ++it) {
		if (it->first) {
			it->first->accept(*this);

			IR& kase = m_builder->push(OP_EQUAL);

			_prepare_operand(kase.op1, node->getExpr());
			_prepare_operand(kase.op2, it->first);

			kase.loc = it->first->getLocation();

			ValueOffset tmp_id = m_builder->getTemp();
			kase.result = Operand(FETCH_TMP, tmp_id);

			last_jmpz = &m_builder->push(OP_JMPZ);
			last_jmpz->op1 = Operand(FETCH_TMP, tmp_id);

			if (last_jmp) {
				last_jmp->op1 = Operand(JMP_ADDR, m_builder->getSize());
			}

			it->second->accept(*this);

			last_jmp = &m_builder->push(OP_JMP);

			last_jmpz->op2 = Operand(JMP_ADDR, m_builder->getSize());
		} else {
			if (default_addr) {
				Compiler::errorf(node->getLocation(),
					"Cannot have more than one default!");
			}
			if (ncases == 1) {
				it->second->accept(*this);
			} else {
				IR& jmp = m_builder->push(OP_JMP);

				default_addr = m_builder->getSize();

				if (last_jmp) {
					last_jmp->op1 = Operand(JMP_ADDR, default_addr);
				}

				it->second->accept(*this);

				last_jmp = &m_builder->push(OP_JMP);

				jmp.op1 = Operand(JMP_ADDR, m_builder->getSize());
			}
		}
	}
	if (last_jmp) {
		last_jmp->op1 = Operand(JMP_ADDR, m_builder->getSize());
	}
	if (default_addr && last_jmpz) {
		last_jmpz->op2.jmp_addr = default_addr;
	}

	if (!m_brks.top().empty()) {
		// Set the break statements jmp address
		for (size_t i = 0, j = m_brks.top().size(); i < j; ++i) {
			m_builder->getAt(m_brks.top()[i]).op1.jmp_addr = m_builder->getSize();
		}
	}

	m_brks.pop();
}

}} // clever::ast
