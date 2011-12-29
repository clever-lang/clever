/**
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
#include "types/typeutils.h"
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

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	lhs->addRef();
	rhs->addRef();
	
	switch (expr->getOp()) {
		case PLUS:  emit(OP_PLUS,   &VM::plus_handler,   lhs, rhs, expr->getValue()); break;
		case DIV:   emit(OP_DIV,    &VM::div_handler,    lhs, rhs, expr->getValue()); break;
		case MULT:  emit(OP_MULT,   &VM::mult_handler,   lhs, rhs, expr->getValue()); break;
		case MINUS: emit(OP_MINUS,  &VM::minus_handler,  lhs, rhs, expr->getValue()); break;
		case XOR:   emit(OP_BW_XOR, &VM::bw_xor_handler, lhs, rhs, expr->getValue()); break;
		case OR:    emit(OP_BW_OR,  &VM::bw_or_handler,  lhs, rhs, expr->getValue()); break;
		case AND:   emit(OP_BW_AND, &VM::bw_and_handler, lhs, rhs, expr->getValue()); break;
		case MOD:   emit(OP_MOD,    &VM::mod_handler,    lhs, rhs, expr->getValue()); break;
	}
}


/**
 * Generates the variable declaration opcode
 */
AST_VISITOR(CodeGenVisitor, VariableDecl) {
	Identifier* var_expr = expr->getVariable();
	Value* initval = expr->getInitialValue();
	Value* variable = var_expr->getValue();
	
	/* Check if the declaration contains initialization */
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
		variable->initialize();

		emit(OP_VAR_DECL, &VM::var_decl_handler, variable);
	}
}

/**
 * Generates the pre increment opcode
 */
AST_VISITOR(CodeGenVisitor, PreIncrement) {
	Value* value = expr->getVar();

	value->addRef();

	emit(OP_PRE_INC, &VM::pre_inc_handler, value, NULL, expr->getValue());
}

/**
 * Generates the pos increment opcode
 */
AST_VISITOR(CodeGenVisitor, PosIncrement) {
	Value* value = expr->getVar();

	value->addRef();

	emit(OP_POS_INC, &VM::pos_inc_handler, value, NULL, expr->getValue());
}

/**
 * Generates the pre decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PreDecrement) {
	Value* value = expr->getVar();

	value->addRef();

	emit(OP_PRE_DEC, &VM::pre_dec_handler, value, NULL, expr->getValue());
}

/**
 * Generates the pos decrement opcode
 */
AST_VISITOR(CodeGenVisitor, PosDecrement) {
	Value* value = expr->getVar();

	value->addRef();

	emit(OP_POS_DEC, &VM::pos_dec_handler, value, NULL, expr->getValue());
}

/**
 * Generates the opcode for the IF-ELSEIF-ELSE expression
 */
AST_VISITOR(CodeGenVisitor, IfExpr) {
	Value* value;
	Opcode* jmp_if;
	Opcode* jmp_else;
	Opcode* jmp_elseif;
	OpcodeList jmp_ops;

	expr->getCondition()->accept(*this);

	value = expr->getCondition()->getValue();
	value->addRef();

	jmp_if = emit(OP_JMPZ, &VM::jmpz_handler);
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

			jmp_elseif = emit(OP_JMPZ, &VM::jmpz_handler, cond);

			jmp_ops.push_back(jmp_elseif);

			if (elseif->hasBlock()) {
				elseif->getBlock()->accept(*this);
			}

			last_jmp = jmp_elseif;
			++it;
		}
	}

	if (expr->hasElseBlock()) {
		jmp_else = emit(OP_JMP, &VM::jmp_handler);

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
		OpcodeList::iterator it = jmp_ops.begin(), end = jmp_ops.end();

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
	Value* value;
	Opcode* jmpz;
	Opcode* jmp;
	unsigned int start_pos = 0;

	start_pos = getOpNum();

	expr->getCondition()->accept(*this);

	value = expr->getCondition()->getValue();
	value->addRef();

	jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);

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

	jmp = emit(OP_JMP, &VM::jmp_handler);
	jmp->setJmpAddr2(start_pos);

	jmpz->setJmpAddr1(getOpNum());
}

/**
 * Generates the opcode for FOR expression
 */
AST_VISITOR(CodeGenVisitor, ForExpr) {
	Value* value;
	Opcode* jmpz;
	Opcode* jmp;
	unsigned int start_pos = 0;

	if (!expr->isIteratorMode()) {
		
		if (expr->getVarDecl() != NULL) {
			expr->getVarDecl()->accept(*this);
		}
		
		start_pos = getOpNum();
		
		if (expr->getCondition()) {
			expr->getCondition()->accept(*this);
			
			value = expr->getCondition()->getValue();
			value->addRef();
		}
		else {
			value = new Value(true);
		}
		
		jmpz = emit(OP_JMPZ, &VM::jmpz_handler, value);
		
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
		
		jmp = emit(OP_JMP, &VM::jmp_handler);
		jmp->setJmpAddr2(start_pos);

		jmpz->setJmpAddr1(getOpNum());
	}
}


/**
 * Generates opcode for logic expression which weren't optimized
 */
AST_VISITOR(CodeGenVisitor, LogicExpr) {
	Opcode* opcode;
	Value* lhs = expr->getLhs()->getValue();
	Value* rhs = expr->getRhs()->getValue();

	lhs->addRef();
	rhs->addRef();

	switch (expr->getOp()) {
		case GREATER:       emit(OP_GREATER,       &VM::greater_handler,       lhs, rhs, expr->getValue()); break;
		case LESS:          emit(OP_LESS,          &VM::less_handler,          lhs, rhs, expr->getValue()); break;
		case GREATER_EQUAL: emit(OP_GREATER_EQUAL, &VM::greater_equal_handler, lhs, rhs, expr->getValue()); break;
		case LESS_EQUAL:    emit(OP_LESS_EQUAL,    &VM::less_equal_handler,    lhs, rhs, expr->getValue()); break;
		case EQUAL:         emit(OP_EQUAL,         &VM::equal_handler,         lhs, rhs, expr->getValue()); break;
		case NOT_EQUAL:     emit(OP_NOT_EQUAL,     &VM::not_equal_handler,     lhs, rhs, expr->getValue()); break;
		case AND:
			opcode = emit(OP_JMPNZ, &VM::jmpz_handler, lhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum()+1);
			opcode = emit(OP_JMPZ, &VM::jmpz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			break;
		case OR:
			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, lhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum()+1);
			opcode = emit(OP_JMPNZ, &VM::jmpnz_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			break;
	}
}

/**
 * Generates opcode for break statement
 */
AST_VISITOR(CodeGenVisitor, BreakNode) {
	Opcode* opcode = emit(OP_BREAK, &VM::break_handler);

	/**
	 * Pushes the break opcode to a stack which in the end
	 * sets its jump addr to end of repeat block
	 */
	m_brks.top().push(opcode);
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
			arg_values = NULL;
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
	Opcode* jmp;

	jmp = emit(OP_JMP, &VM::jmp_handler);

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
