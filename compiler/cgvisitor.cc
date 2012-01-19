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
#include "cgvisitor.h"
#include "compiler/compiler.h"
#include "compiler/typechecker.h"

namespace clever { namespace ast {

/**
 * Creates a vector with the current value from a Value* pointers
 */
AST_VISITOR(CodeGenVisitor, ArgumentList) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	while (it != end) {
		(*it)->accept(*this);
		++it;
	}
}

AST_VISITOR(CodeGenVisitor, Identifier) {
}

AST_VISITOR(CodeGenVisitor, Constant) {
}

AST_VISITOR(CodeGenVisitor, AliasStmt) {
}

/**
 * Generates opcode for regex syntax
 */
AST_VISITOR(CodeGenVisitor, RegexPattern) {
	emit(OP_MCALL, &VM::mcall_handler,
		expr->getMethodValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for unary expression
 */
AST_VISITOR(CodeGenVisitor, UnaryExpr) {
	Value* value = expr->getExprValue();

	value->addRef();

	switch (expr->getOp()) {
		case PRE_INC:
		case POS_INC:
		case PRE_DEC:
		case POS_DEC:
		case NOT:
		case BW_NOT:
			emit(OP_MCALL, &VM::mcall_handler, expr->getMethod(), NULL, expr->getValue());
			break;
	}
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	Value* rhs;

	expr->getLhs()->accept(*this);

	Value* lhs = expr->getLhs()->getValue();

	/**
	 * Treat the jump for logical expression
	 */
	switch (expr->getOp()) {
		case AND: {
			Opcode* opcode = emit(OP_JMPNZ, &VM::jmpz_handler, lhs, NULL, expr->getValue());

			expr->getRhs()->accept(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr1(getOpNum()+1);

			opcode = emit(OP_JMPZ, &VM::jmpz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		case OR: {
			Opcode* opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, lhs, NULL, expr->getValue());

			expr->getRhs()->accept(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr1(getOpNum()+1);

			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		default:
			expr->getRhs()->accept(*this);
			rhs = expr->getRhs()->getValue();
			emit(OP_MCALL, &VM::mcall_handler, expr->getMethod(), expr->getMethodArgs(), expr->getValue());
	}

	lhs->addRef();
	rhs->addRef();
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	Identifier* var_expr = expr->getVariable();
	Value* initval = expr->getInitialValue();
	Value* variable = var_expr->getValue();

	/**
	 * Check if the declaration contains initialization
	 */
	if (initval) {
		if (initval->isPrimitive()) {
			if (initval->getTypePtr() == variable->getTypePtr()) {
				variable->copy(initval);
			}
			else if (variable->getTypePtr() == CLEVER_INT) {
				variable->setInteger(initval->getDouble());
			}
			else {
				variable->setDouble(initval->getInteger());
			}
		}

		variable->addRef();
		initval->addRef();

		emit(OP_VAR_DECL, &VM::var_decl_handler, variable, initval);
	} else {
		variable->addRef();

		emit(OP_VAR_DECL, &VM::var_decl_handler, variable);
	}
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(CodeGenVisitor, IfExpr) {
	OpcodeList jmp_ops;

	expr->getCondition()->accept(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmp_if = emit(OP_JMPZ, &VM::jmpz_handler);
	jmp_if->setOp1(value);

	jmp_ops.push_back(jmp_if);

	if (expr->hasBlock()) {
		expr->getBlock()->accept(*this);
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();
		Opcode* last_jmp = jmp_if;

		while (it != end) {
			Value* cond;
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			last_jmp->setJmpAddr1(getOpNum());

			elseif->getCondition()->accept(*this);

			cond = elseif->getCondition()->getValue();
			cond->addRef();

			Opcode* jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->getBlock()->accept(*this);
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

		expr->getElse()->accept(*this);
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
 * Call the accept method of each block node
 */
AST_VISITOR(CodeGenVisitor, BlockNode) {
	const NodeList& nodes = expr->getNodes();
	NodeList::const_iterator it = nodes.begin(), end = nodes.end();

	/**
	 * Iterates statements inside the block
	 */
	while (it != end) {
		(*it)->accept(*this);
		++it;
	}
}

/**
 * Generates the JMPZ opcode for WHILE expression
 */
AST_VISITOR(CodeGenVisitor, WhileExpr) {
	unsigned int start_pos = 0;
	start_pos = getOpNum();

	expr->getCondition()->accept(*this);

	Value* value = expr->getCondition()->getValue();
	value->addRef();

	Opcode* jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

	if (expr->hasBlock()) {
		m_brks.push(OpcodeStack());

		expr->getBlock()->accept(*this);

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
			expr->getVarDecl()->accept(*this);
		}

		unsigned int start_pos = getOpNum();

		if (expr->getCondition()) {
			expr->getCondition()->accept(*this);

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

			expr->getBlock()->accept(*this);

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
			expr->getIncrement()->accept(*this);
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
		expr->getArgs()->accept(*this);

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
		expr->getArgs()->accept(*this);
	}

	call->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->getValue());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignExpr) {
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	lhs->addRef();
	rhs->addRef();

	emit(OP_ASSIGN, &VM::assign_handler, lhs, rhs);
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

	expr->getBlock()->accept(*this);

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
