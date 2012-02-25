/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include "interpreter/ast.h"
#include "compiler/cgvisitor.h"
#include "compiler/compiler.h"
#include "compiler/typechecker.h"
#include "vm/opcode.h"

namespace clever { namespace ast {

AST_VISITOR(CodeGenVisitor, Identifier) {
}

AST_VISITOR(CodeGenVisitor, Constant) {
}

AST_VISITOR(CodeGenVisitor, AliasStmt) {
}

/**
 * Creates a vector with the current value from a Value* pointers
 */
AST_VISITOR(CodeGenVisitor, ArgumentList) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

/**
 * Genearates opcode for the subscript operator
 */
AST_VISITOR(CodeGenVisitor, Subscript) {
	emit(OP_AT, &VM::mcall_handler,
		expr->getCallValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for regex syntax
 */
AST_VISITOR(CodeGenVisitor, RegexPattern) {
	emit(OP_REGEX, &VM::mcall_handler,
		expr->getCallValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for unary expression
 */
AST_VISITOR(CodeGenVisitor, UnaryExpr) {
	OpcodeType opcode;

	switch (expr->getOp()) {
		case PRE_INC: opcode = OP_PRE_INC; break;
		case POS_INC: opcode = OP_POS_INC; break;
		case PRE_DEC: opcode = OP_PRE_DEC; break;
		case POS_DEC: opcode = OP_POS_DEC; break;
		case NOT:     opcode = OP_NOT;     break;
		case BW_NOT:  opcode = OP_BW_NOT;  break;
		default:
			Compiler::error("Unknown op type!");
			break;
	}
	emit(opcode, Opcode::getHandlerByType(opcode), expr->getCallValue())
		->setResult(expr->getValue());
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	expr->getLhs()->acceptVisitor(*this);

	Value* rhs;
	Value* lhs = expr->getLhs()->getValue();
	OpcodeType opval;
	int op = expr->getOp();

	// Treat the jump for logical expression
	switch (op) {
		case AND:
		case OR: {
			opval = op == AND ? OP_JMPZ : OP_JMPNZ;

			VM::opcode_handler op_handler = opval == OP_JMPZ ?
				&VM::jmpz_handler : &VM::jmpnz_handler;

			Opcode* opcode = emit(opval, op_handler, lhs);
			opcode->setResult(expr->getValue());

			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr2(getOpNum()+1);

			opcode = emit(opval, op_handler, rhs);
			opcode->setResult(expr->getValue());
			opcode->setJmpAddr2(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		default:
			switch (op) {
				case PLUS:          opval = OP_PLUS;    break;
				case MINUS:         opval = OP_MINUS;   break;
				case DIV:           opval = OP_DIV;     break;
				case MULT:          opval = OP_MULT;    break;
				case MOD:           opval = OP_MOD;     break;
				case XOR:           opval = OP_XOR;     break;
				case BW_OR:         opval = OP_BW_OR;   break;
				case BW_AND:        opval = OP_BW_AND;  break;
				case GREATER:       opval = OP_GREATER; break;
				case LESS:          opval = OP_LESS;    break;
				case GREATER_EQUAL: opval = OP_GE;      break;
				case LESS_EQUAL:    opval = OP_LE;      break;
				case EQUAL:         opval = OP_EQUAL;   break;
				case NOT_EQUAL:     opval = OP_NE;      break;
				case LSHIFT:        opval = OP_LSHIFT;  break;
				case RSHIFT:        opval = OP_RSHIFT;  break;
				default:
					Compiler::error("Unknown operation!");
			}
			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			emit(opval, Opcode::getHandlerByType(opval), expr->getCallValue(),
				expr->getArgsValue(), expr->getValue());
			break;
	}

	lhs->addRef();
	rhs->addRef();
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	if (!expr->getConstructorArgs() && expr->getInitialValue()) {
		expr->getCallValue()->addRef();
		//expr->getArgsValue()->addRef();

		emit(OP_ASSIGN, &VM::mcall_handler, expr->getCallValue(),
			expr->getArgsValue());
	}
	else if (expr->getConstructorArgs()) {
		clever_assert_not_null(expr->getInitialValue());

		CallableValue* call = expr->getCallValue();

		call->addRef();
		expr->getInitialValue()->addRef();

		emit(OP_MCALL, &VM::mcall_handler, call, expr->getArgsValue(),
			expr->getInitialValue());
	}
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(CodeGenVisitor, IfExpr) {
	OpcodeList jmp_ops;

	expr->getCondition()->acceptVisitor(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmp_if = emit(OP_JMPZ, &VM::jmpz_handler, value);
	jmp_if->setResult(NULL);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}

	Opcode* last_jmpz = jmp_if;

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it(elseif_nodes.begin()), end(elseif_nodes.end());

		while (it != end) {
			jmp_ops.push_back(emit(OP_JMP, &VM::jmp_handler));

			// If the last expression is false, jumps to the next condition
			last_jmpz->setJmpAddr2(getOpNum());

			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			elseif->getCondition()->acceptVisitor(*this);

			Value* cond = elseif->getCondition()->getValue();
			cond->addRef();

			Opcode* jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);
			jmp_elseif->setResult(NULL);

			if (elseif->hasBlock()) {
				elseif->getBlock()->acceptVisitor(*this);
			}
			last_jmpz = jmp_elseif;
			++it;
		}
	}

	jmp_ops.push_back(emit(OP_JMP, &VM::jmp_handler));

	// If the last expression has failed, it jumps to the last block
	last_jmpz->setJmpAddr2(getOpNum());

	if (expr->hasElseBlock()) {
		expr->getElse()->acceptVisitor(*this);
	}

	OpcodeList::const_iterator it(jmp_ops.begin()), end(jmp_ops.end());

	// Set the JMP addr to out of the control structure
	while (it != end) {
		(*it)->setJmpAddr1(getOpNum());
		++it;
	}
}

/**
 * Call the acceptVisitor method of each block node
 */
AST_VISITOR(CodeGenVisitor, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Iterates statements inside the block
	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

/**
 * Call the acceptVisitor method of each block node without creating scope
 */
AST_VISITOR(CodeGenVisitor, UnscopedBlockNode) {
	const NodeList& nodes = expr->getBlock()->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Iterates statements inside the block
	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

AST_VISITOR(CodeGenVisitor, VarDecls) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	// Iterates statements inside the block
	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

/**
 * Generates the JMPZ opcode for WHILE expression
 */
AST_VISITOR(CodeGenVisitor, WhileExpr) {
	size_t start_pos = getOpNum();

	expr->getCondition()->acceptVisitor(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);
	jmpz->setResult(NULL);

	if (expr->hasBlock()) {
		m_brks.push(OpcodeStack());

		expr->getBlock()->acceptVisitor(*this);

		// Points break statements to out of WHILE block
		while (!m_brks.top().empty()) {
			m_brks.top().top()->setJmpAddr1(getOpNum()+1);
			m_brks.top().pop();
		}
		m_brks.pop();
	}

	emit(OP_JMP, &VM::jmp_handler, start_pos);

	jmpz->setJmpAddr2(getOpNum());
}

/**
 * Generates the opcode for FOR expression
 */
AST_VISITOR(CodeGenVisitor, ForExpr) {
	if (!expr->isIteratorMode()) {
		Value* value;

		if (expr->getVarDecl() != NULL) {
			expr->getVarDecl()->acceptVisitor(*this);
		}

		size_t start_pos = getOpNum();

		if (expr->getCondition()) {
			expr->getCondition()->acceptVisitor(*this);

			value = expr->getCondition()->getValue();
			value->addRef();
		}
		else {
			value = new Value(true);
		}

		Opcode* jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);
		jmpz->setResult(NULL);

		// If the expression has increment we must jump 2 opcodes
		unsigned int offset = (expr->getIncrement() ? 2 : 1);
		if (expr->hasBlock()) {
			m_brks.push(OpcodeStack());

			expr->getBlock()->acceptVisitor(*this);

			// Points break statements to out of FOR block
			while (!m_brks.top().empty()) {
				m_brks.top().top()->setJmpAddr1(getOpNum() + offset);
				m_brks.top().pop();
			}

			m_brks.pop();
		}

		if (expr->getIncrement() != NULL) {
			expr->getIncrement()->acceptVisitor(*this);
		}

		emit(OP_JMP, &VM::jmp_handler, start_pos);

		jmpz->setJmpAddr2(getOpNum());
	}
}

/**
 * Generates opcode for break statement
 */
AST_VISITOR(CodeGenVisitor, BreakNode) {
	/**
	 * Pushes the break opcode to a stack which in the end
	 * sets its jump addr to end of repeat block
	 */
	m_brks.top().push(emit(OP_BREAK, &VM::jmp_handler));
}

/**
 * Generates opcode for function call
 */
AST_VISITOR(CodeGenVisitor, FunctionCall) {
	CallableValue* fvalue = expr->getFuncValue();
	ValueVector* arg_values = expr->getArgsValue();

	clever_assert_not_null(fvalue);

	if (arg_values) {
		expr->getArgs()->acceptVisitor(*this);
	}

	fvalue->addRef();
	emit(OP_FCALL, &VM::fcall_handler, fvalue, arg_values, expr->getValue());
}

/**
 * Generates opcode for method call
 */
AST_VISITOR(CodeGenVisitor, MethodCall) {
	CallableValue* call = expr->getCallValue();

	call->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, expr->getArgsValue(),
		expr->getValue());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignExpr) {
	emit(OP_ASSIGN, &VM::mcall_handler, expr->getCallValue(),
		expr->getArgsValue());
}

/**
 * Import statement
 */
AST_VISITOR(CodeGenVisitor, ImportStmt) {

}

/**
 * Function declaration
 */
AST_VISITOR(CodeGenVisitor, FuncDeclaration) {
	CallableValue* func = expr->getFunc();
	const Function* user_func = func->getFunction();
	Opcode* jmp = emit(OP_JMP, &VM::jmp_handler);

	const_cast<Function*>(user_func)->setOffset(getOpNum());

	expr->getBlock()->acceptVisitor(*this);

	emit(OP_JMP, &VM::end_func_handler);

	jmp->setJmpAddr1(getOpNum());
}

/**
 * Generates opcode for return statement
 */
AST_VISITOR(CodeGenVisitor, ReturnStmt) {
	Value* expr_value = expr->getExprValue();

	CLEVER_SAFE_ADDREF(expr_value);

	emit(OP_RETURN, &VM::return_handler, expr_value);
}

/**
 * Generates opcodes for class declaration
 */
AST_VISITOR(CodeGenVisitor, ClassDeclaration) {
}

AST_VISITOR(CodeGenVisitor, TypeCreation) {
	CallableValue* call = expr->getCallValue();

	call->addRef();
	expr->getValue()->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, expr->getArgsValue(),
		call->getValue());
}

AST_VISITOR(CodeGenVisitor, ArrayList) {
}

AST_VISITOR(CodeGenVisitor, MapList) {
}

}} // clever::ast
