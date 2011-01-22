#ifndef CLEVER_ASTVISITOR_H
#define CLEVER_ASTVISITOR_H

#include "vm.h"
#include "ssa.h"
#include "compiler.h"

namespace clever { namespace ast {

class Expression;
class BinaryExpression;
class VariableDecl;
class PosIncrement;
class PosDecrement;
class PreIncrement;
class PreDecrement;
class IfExpression;
class ElseIfExpression;
class ElseExpression;
class WhileExpression;
class EndWhileExpression;
class StartExpr;
class LogicExpression;
class FunctionCall;
class MethodCall;
class Assignment;
class Import;
class NewBlock;
class EndBlock;
class EndIfExpression;
class BreakExpression;

typedef std::vector<Expression*> Arguments;

#define AST_VISITOR(type) void ASTVisitor::visit(type* expr) throw()
#define AST_VISITOR_DECL(type) void visit(type* expr) throw()

class ASTVisitor {
public:
	typedef std::stack<Opcode*> Jmp;
	typedef std::stack<Jmp> JmpStack;

	ASTVisitor() { }

	void init() throw() {
		m_ssa.newBlock();
		m_opcodes.reserve(10);
	}

	void shutdown() throw() {
		m_ssa.endBlock();
	}

	~ASTVisitor() { }
	/**
	 * Builds the function arguments vector
	 */
	ValueVector* functionArgs(const ast::Arguments*) throw();
	/**
	 * Returns the Value pointer according with value type
	 */
	Value* getValue(ast::Expression*) throw();
	/**
	 * Displays the error message and exits the program
	 */
	void error(std::string) throw();
	/**
	 * Checks if two operands has compatible types to perform some operation
	 */
	bool checkCompatibleTypes(Value*, Value*) throw();
	/**
	 * Performs the constant folding and constant propagation optimization
	 */
	ConstantValue* constantFolding(int, Value*, Value*) throw();
	/**
	 * Returns the opcode list
	 */
	OpcodeList& get_opcodes() throw() {	return m_opcodes; }
	/**
	 * Returns the opcode number
	 */
	unsigned int getOpNum() const throw() {	return m_opcodes.size()-1; }
	/**
	 * Pushes the opcode to list
	 */
	void pushOpcode(Opcode* opcode) throw() {
		m_opcodes.push_back(opcode);
		/**
		 * Sets the opcode number, which is used by JMP opcodes
		 */
		opcode->set_op_num(getOpNum());
	}

	AST_VISITOR_DECL(BinaryExpression);
	AST_VISITOR_DECL(VariableDecl);
	AST_VISITOR_DECL(PreIncrement);
	AST_VISITOR_DECL(PosIncrement);
	AST_VISITOR_DECL(PreDecrement);
	AST_VISITOR_DECL(PosDecrement);
	AST_VISITOR_DECL(NewBlock);
	AST_VISITOR_DECL(EndBlock);
	AST_VISITOR_DECL(IfExpression);
	AST_VISITOR_DECL(ElseIfExpression);
	AST_VISITOR_DECL(ElseExpression);
	AST_VISITOR_DECL(EndIfExpression);
	AST_VISITOR_DECL(WhileExpression);
	AST_VISITOR_DECL(EndWhileExpression);
	AST_VISITOR_DECL(StartExpr);
	AST_VISITOR_DECL(LogicExpression);
	AST_VISITOR_DECL(BreakExpression);
	AST_VISITOR_DECL(FunctionCall);
	AST_VISITOR_DECL(MethodCall);
	AST_VISITOR_DECL(Assignment);
	AST_VISITOR_DECL(Import);
private:
	OpcodeList m_opcodes;
	SSA m_ssa;
	JmpStack m_jmps;
	JmpStack m_brks;
};

}} // clever::ast

#endif // CLEVER_ASTVISITOR_H