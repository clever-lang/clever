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

AST_VISITOR(CodeGenVisitor, Subscript) {
}

/**
 * Generates opcode for regex syntax
 */
AST_VISITOR(CodeGenVisitor, RegexPattern) {
	emit(OP_REGEX, &VM::mcall_handler,
		expr->getMethodValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for unary expression
 */
AST_VISITOR(CodeGenVisitor, UnaryExpr) {
	Opcodes opcode;

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
	emit(opcode, &VM::mcall_handler, expr->getMethod(), NULL, expr->getValue());
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	expr->getLhs()->acceptVisitor(*this);

	Value* rhs;
	Value* lhs = expr->getLhs()->getValue();
	Opcodes opval;

	/**
	 * Treat the jump for logical expression
	 */
	switch (expr->getOp()) {
		case AND: {
			Opcode* opcode = emit(OP_JMPNZ, &VM::jmpz_handler, lhs, NULL, expr->getValue());

			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr1(getOpNum()+1);

			opcode = emit(OP_JMPZ, &VM::jmpz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		case OR: {
			Opcode* opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, lhs, NULL, expr->getValue());

			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr1(getOpNum()+1);

			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		case PLUS:          opval = OP_PLUS;
		case DIV:           opval = OP_DIV;
		case MULT:          opval = OP_MULT;
		case MINUS:         opval = OP_MINUS;
		case MOD:           opval = OP_MOD;
		case XOR:           opval = OP_XOR;
		case BW_OR:         opval = OP_BW_OR;
		case BW_AND:        opval = OP_BW_AND;
		case GREATER:       opval = OP_GREATER;
		case LESS:          opval = OP_LESS;
		case GREATER_EQUAL: opval = OP_GE;
		case LESS_EQUAL:    opval = OP_LE;
		case EQUAL:         opval = OP_EQUAL;
		case NOT_EQUAL:     opval = OP_NE;
		case LSHIFT:        opval = OP_LSHIFT;
		case RSHIFT:        opval = OP_RSHIFT;
			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			emit(opval, &VM::mcall_handler, expr->getMethod(),
				expr->getMethodArgs(), expr->getValue());
			break;
		default:
			Compiler::error("Unknown op type!");
			break;
	}

	lhs->addRef();
	rhs->addRef();
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	/**
	 * Check if the declaration contains initialization,
	 * non initialized declaration doesn't emit opcode
	 */
	if (expr->getInitialValue() == NULL) {
		return;
	}

	emit(OP_ASSIGN, &VM::mcall_handler, expr->getMethodValue(),
		expr->getMethodArgs());
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(CodeGenVisitor, IfExpr) {
	OpcodeList jmp_ops;

	expr->getCondition()->acceptVisitor(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmp_if = emit(OP_JMPZ, &VM::jmpz_handler);
	jmp_if->setOp1(value);

	jmp_ops.push_back(jmp_if);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();
		Opcode* last_jmp = jmp_if;

		while (it != end) {
			Value* cond;
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			last_jmp->setJmpAddr1(getOpNum());

			elseif->getCondition()->acceptVisitor(*this);

			cond = elseif->getCondition()->getValue();
			cond->addRef();

			Opcode* jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->getBlock()->acceptVisitor(*this);
			}

			last_jmp = jmp_elseif;
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		Opcode* jmp_else = emit(OP_JMP, &VM::jmp_handler);

		if (jmp_ops.size() == 1) {
			jmp_if->setJmpAddr1(getOpNum());
		}

		jmp_ops.push_back(jmp_else);

		expr->getElse()->acceptVisitor(*this);
	}

	if (jmp_ops.size() == 1) {
		jmp_if->setJmpAddr1(getOpNum());
		jmp_if->setJmpAddr2(getOpNum());
	} else {
		OpcodeList::const_iterator it = jmp_ops.begin(), end = jmp_ops.end();

		while (it != end) {
			(*it)->setJmpAddr2(getOpNum());
			++it;
		}
	}
}

/**
 * Call the acceptVisitor method of each block node
 */
AST_VISITOR(CodeGenVisitor, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	/**
	 * Iterates statements inside the block
	 */
	while (it != end) {
		(*it)->acceptVisitor(*this);
		++it;
	}
}

/**
 * Generates the JMPZ opcode for WHILE expression
 */
AST_VISITOR(CodeGenVisitor, WhileExpr) {
	unsigned int start_pos = 0;
	start_pos = getOpNum();

	expr->getCondition()->acceptVisitor(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

	if (expr->hasBlock()) {
		m_brks.push(OpcodeStack());

		expr->getBlock()->acceptVisitor(*this);

		/**
		 * Points break statements to out of WHILE block
		 */
		while (!m_brks.top().empty()) {
			m_brks.top().top()->setJmpAddr1(getOpNum()+1);
			m_brks.top().pop();
		}
		m_brks.pop();
	}

	Opcode* jmp = emit(OP_JMP, &VM::jmp_handler);
	jmp->setJmpAddr2(start_pos);

	jmpz->setJmpAddr1(getOpNum());
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

		unsigned int start_pos = getOpNum();

		if (expr->getCondition()) {
			expr->getCondition()->acceptVisitor(*this);

			value = expr->getCondition()->getValue();
			value->addRef();
		}
		else {
			value = new Value(true);
		}

		Opcode* jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

		// If the expression has increment we must jump 2 opcodes
		unsigned int offset = (expr->getIncrement() ? 2 : 1);
		if (expr->hasBlock()) {
			m_brks.push(OpcodeStack());

			expr->getBlock()->acceptVisitor(*this);

			/**
			 * Points break statements to out of FOR block
			 */
			while (!m_brks.top().empty()) {
				m_brks.top().top()->setJmpAddr1(getOpNum() + offset);
				m_brks.top().pop();
			}

			m_brks.pop();
		}

		if (expr->getIncrement() != NULL) {
			expr->getIncrement()->acceptVisitor(*this);
		}

		Opcode* jmp = emit(OP_JMP, &VM::jmp_handler);
		jmp->setJmpAddr2(start_pos);

		jmpz->setJmpAddr1(getOpNum());
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
	m_brks.top().push(emit(OP_BREAK, &VM::break_handler));
}

/**
 * Generates opcode for function call
 */
AST_VISITOR(CodeGenVisitor, FunctionCall) {
	CallableValue* fvalue = expr->getFuncValue();
	Function* func = fvalue->getFunction();
	Value* arg_values = expr->getArgsValue();

	if (arg_values) {
		expr->getArgs()->acceptVisitor(*this);

		/**
		 * User-defined function needs an extra opcode passing the parameters
		 * to be assigned to respective var names used in the func declaration
		 */
		if (func->isUserDefined()) {
			emit(OP_RECV, &VM::arg_recv_handler, func->getVars(), arg_values);
			arg_values->addRef();
		}
	}

	fvalue->addRef();
	emit(OP_FCALL, &VM::fcall_handler, fvalue, arg_values, expr->getValue());
}

/**
 * Generates opcode for method call
 */
AST_VISITOR(CodeGenVisitor, MethodCall) {
	CallableValue* call = expr->getFuncValue();
	Value* arg_values = expr->getArgsValue();

	if (arg_values) {
		expr->getArgs()->acceptVisitor(*this);
	}

	call->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->getValue());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignExpr) {
	Value* rvalue = expr->getMethodArgs();

	rvalue->addRef();

	emit(OP_ASSIGN, &VM::mcall_handler, expr->getMethodValue(), rvalue);
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
	Function* user_func = func->getFunction();
	Opcode* jmp = emit(OP_JMP, &VM::jmp_handler);

	user_func->setOffset(getOpNum());

	expr->getBlock()->acceptVisitor(*this);

	emit(OP_JMP, &VM::end_func_handler);

	jmp->setJmpAddr2(getOpNum());
}

/**
 * Generates opcode for return statement
 */
AST_VISITOR(CodeGenVisitor, ReturnStmt) {
	Value* expr_value = expr->getExprValue();

	if (expr_value) {
		expr_value->addRef();
	}

	emit(OP_RETURN, &VM::return_handler, expr_value);
}

/**
 * Generates opcodes for class declaration
 */
AST_VISITOR(CodeGenVisitor, ClassDeclaration) {
}

AST_VISITOR(CodeGenVisitor, TypeCreation) {
	CallableValue* call = expr->getFuncValue();
	Value* arg_values = expr->getArgsValue();

	call->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->getValue());
}

}} // clever::ast
