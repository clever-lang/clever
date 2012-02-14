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

namespace clever { 

/**
 * Prepares the node to generate an opcode which will make a method call
 */
static CallableValue* _make_method_call(const Type* type, Value* var,
	const CString* mname, ast::ASTNode* expr, const Value* arg_values) {

	clever_assert_not_null(type);
	clever_assert_not_null(var);
	clever_assert_not_null(mname);

	TypeVector args_types;

	if (arg_values != NULL) {
		const ValueVector* vv = arg_values->getVector();

		for (size_t i = 0; i < vv->size(); ++i) {
			args_types.push_back(vv->at(i)->getTypePtr());
		}
	}

	const Method* method = type->getMethod(mname, &args_types);
	var->setTypePtr(type);

	CallableValue* call = new CallableValue(mname, type);
	call->setHandler(method);
	call->setContext(var);
	var->addRef();

	// Set the return type as the declared in the method
	Value* result = expr->getValue();

	if (result) {
		result->setTypePtr(method->getReturnType());
	}

	return call;
}	

namespace ast {

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
	Value* var = expr->getIdentifier()->getValue();
	
	expr->setCallValue(_make_method_call(var->getTypePtr(), var,
		CLEVER_OPERATOR_AT_PTR, expr, expr->getArgsValue()));

	expr->getCallValue()->addRef();
	
	emit(OP_AT, &VM::mcall_handler,
		expr->getCallValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for regex syntax
 */
AST_VISITOR(CodeGenVisitor, RegexPattern) {
	// The Pcre constructor CallableValue
	expr->setCallValue(_make_method_call(expr->getValue()->getTypePtr(), expr->getValue(),
		CSTRING(CLEVER_CTOR_NAME), expr, expr->getArgsValue()));

	expr->getCallValue()->addRef();
		
	emit(OP_REGEX, &VM::mcall_handler,
		expr->getCallValue(), expr->getArgsValue(), expr->getValue());
}

/**
 * Generates opcode for unary expression
 */
AST_VISITOR(CodeGenVisitor, UnaryExpr) {
	Opcodes opcode;
	Value* var = expr->getExpr()->getValue();
	const CString* method_name = NULL;

	switch (expr->getOp()) {
		case PRE_INC:
			opcode = OP_PRE_INC; 
			method_name = CLEVER_OPERATOR_PRE_INC_PTR;
		break;
		case POS_INC: 
			opcode = OP_POS_INC;
			method_name = CLEVER_OPERATOR_POS_INC_PTR;
		break;
		case PRE_DEC: 
			opcode = OP_PRE_DEC;
			method_name = CLEVER_OPERATOR_PRE_DEC_PTR;
		break;
		case POS_DEC: 
			opcode = OP_POS_DEC; 
			method_name = CLEVER_OPERATOR_POS_DEC_PTR;
		break;
		case NOT:     
			opcode = OP_NOT;
			method_name = CLEVER_OPERATOR_NOT_PTR;
		break;
		case BW_NOT:
			opcode = OP_BW_NOT;
			method_name = CLEVER_OPERATOR_BW_NOT_PTR;
		break;
		default:
			Compiler::error("Unknown op type!");
			break;
	}
	
	clever_assert_not_null(method_name);
	
	expr->setCallValue(_make_method_call(var->getTypePtr(), var, method_name,
			expr, NULL));

	expr->getCallValue()->addRef();
	
	emit(opcode, &VM::mcall_handler, expr->getCallValue(), NULL, expr->getValue());
}

/**
 * Generates opcode for binary expression
 */
AST_VISITOR(CodeGenVisitor, BinaryExpr) {
	expr->getLhs()->acceptVisitor(*this);
	
	const CString* method_name = NULL;
	Value* rhs;
	Value* lhs = expr->getLhs()->getValue();
	Opcodes opval;
	int op = expr->getOp();

	// Treat the jump for logical expression
	switch (op) {
		case AND:
		case OR: {
			opval = op == AND ? OP_JMPZ : OP_JMPNZ;

			VM::opcode_handler op_handler = opval == OP_JMPZ ?
				&VM::jmpz_handler : &VM::jmpnz_handler;

			Opcode* opcode = emit(opval, op_handler, lhs, NULL, expr->getValue());

			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();

			opcode->setJmpAddr1(getOpNum()+1);

			opcode = emit(opval, op_handler, rhs, NULL, expr->getValue());
			opcode->setJmpAddr1(getOpNum());
			expr->getValue()->addRef();
			}
			break;
		default:
			switch (op) {
				case PLUS:          
					opval = OP_PLUS; 
					method_name = CLEVER_OPERATOR_PLUS_PTR;
				break;
				case DIV:
					opval = OP_DIV;
					method_name = CLEVER_OPERATOR_DIV_PTR;
				break;
				case MULT:
					opval = OP_MULT;
					method_name = CLEVER_OPERATOR_MULT_PTR;
				break;
				case MINUS:
					opval = OP_MINUS;
					method_name = CLEVER_OPERATOR_MINUS_PTR;
				break;
				case MOD:
					opval = OP_MOD;
					method_name = CLEVER_OPERATOR_MOD_PTR;
				break;
				case XOR:
					opval = OP_XOR;
					method_name = CLEVER_OPERATOR_BW_XOR_PTR;
				break;
				case BW_OR:
					opval = OP_BW_OR;
					method_name = CLEVER_OPERATOR_BW_OR_PTR;
				break;
				case BW_AND:
					opval = OP_BW_AND;
					method_name = CLEVER_OPERATOR_BW_AND_PTR;
				break;
				case GREATER:
					opval = OP_GREATER;
					method_name = CLEVER_OPERATOR_GREATER_PTR;
				break;
				case LESS:
					opval = OP_LESS;
					method_name = CLEVER_OPERATOR_LESS_PTR;
				break;
				case GREATER_EQUAL:
					opval = OP_GE;
					method_name = CLEVER_OPERATOR_GE_PTR;
				break;
				case LESS_EQUAL:
					opval = OP_LE;
					method_name = CLEVER_OPERATOR_LE_PTR;
				break;
				case EQUAL:
					opval = OP_EQUAL;
					method_name = CLEVER_OPERATOR_EQUAL_PTR;
				break;
				case NOT_EQUAL:
					opval = OP_NE;
					method_name = CLEVER_OPERATOR_NE_PTR;
				break;
				case LSHIFT:
					opval = OP_LSHIFT;
					method_name = CLEVER_OPERATOR_LSHIFT_PTR;
				break;
				case RSHIFT:
					opval = OP_RSHIFT;
					method_name = CLEVER_OPERATOR_RSHIFT_PTR;
				break;
				default:
					Compiler::error("Unknown op type!");
			}
			
			clever_assert_not_null(method_name);
			
			expr->setCallValue(_make_method_call(lhs->getTypePtr(), 
				lhs, method_name,
				expr, expr->getArgsValue()));
			
			expr->getRhs()->acceptVisitor(*this);
			rhs = expr->getRhs()->getValue();
			expr->getCallValue()->addRef();

			emit(opval, &VM::mcall_handler, expr->getCallValue(),
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
		expr->getArgsValue()->addRef();
		
		expr->setCallValue(_make_method_call(expr->getInitialValue()->getTypePtr(), 
			expr->getValue(),
			CLEVER_OPERATOR_ASSIGN_PTR, expr, expr->getArgsValue())
		);
		
		expr->getCallValue()->addRef();
		
		emit(OP_ASSIGN, &VM::mcall_handler, expr->getCallValue(),
			expr->getArgsValue());
	}
	else if (expr->getConstructorArgs()) {
		clever_assert_not_null(expr->getInitialValue());
		
		Value* arg_values = expr->getArgsValue();

		arg_values->addRef();
		expr->getInitialValue()->addRef();
		
		expr->setCallValue(_make_method_call(expr->getInitialValue()->getTypePtr(), 
			expr->getValue(),
			CSTRING(CLEVER_CTOR_NAME), expr, expr->getArgsValue())
		);
		
		expr->getCallValue()->addRef();

		emit(OP_MCALL, &VM::mcall_handler, expr->getCallValue(),
			arg_values, expr->getInitialValue());
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

	jmp_ops.push_back(jmp_if);

	if (expr->hasBlock()) {
		expr->getBlock()->acceptVisitor(*this);
	}

	if (expr->hasElseIf()) {
		const NodeList& elseif_nodes = expr->getNodes();
		NodeList::const_iterator it = elseif_nodes.begin(), end = elseif_nodes.end();
		Opcode* last_jmp = jmp_if;

		while (it != end) {
			ElseIfExpr* elseif = static_cast<ElseIfExpr*>(*it);

			last_jmp->setJmpAddr1(getOpNum());

			elseif->getCondition()->acceptVisitor(*this);

			Value* cond = elseif->getCondition()->getValue();
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
	Value* arg_values = expr->getArgsValue();

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
	Value* arg_values = expr->getArgsValue();
	Value* variable = expr->getVariable()->getValue();
	const CString* const name = expr->getMethodName();

	expr->setCallValue(_make_method_call(variable->getTypePtr(), variable,
			name, expr, arg_values));

	CallableValue* call = expr->getCallValue();
	call->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, expr->getValue());
}

/**
 * Generates opcode for variable assignment
 */
AST_VISITOR(CodeGenVisitor, AssignExpr) {
	Value* lhs = expr->getLhs()->getValue();
	
	expr->setCallValue(_make_method_call(lhs->getTypePtr(), lhs,
			CLEVER_OPERATOR_ASSIGN_PTR, expr, expr->getArgsValue()));
	
	expr->getCallValue()->addRef();
	
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
	CallableValue* call = expr->getCallValue();
	Value* arg_values = expr->getArgsValue();

	call->addRef();
	expr->getValue()->addRef();

	emit(OP_MCALL, &VM::mcall_handler, call, arg_values, call->getValue());
}

}} // clever::ast
