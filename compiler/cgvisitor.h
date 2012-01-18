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

#ifndef CLEVER_CGVISITOR_H
#define CLEVER_CGVISITOR_H

#include "compiler/symboltable.h"
#include "vm/opcode.h"
#include "interpreter/astvisitor.h"

namespace clever { namespace ast {

/**
 * CodeGen Visitor
 */
class CodeGenVisitor : public ASTVisitor {
public:
	typedef std::stack<Opcode*> OpcodeStack;
	typedef std::stack<OpcodeStack> JmpStack;

	CodeGenVisitor()
		: m_interactive(false), m_opcode_dump(false) {
		//g_symtable.beginScope();
	}
	~CodeGenVisitor() {
		//g_symtable.endScope();
	}

	void init() {
		m_opcodes.clear();
		m_opcodes.reserve(10);
	}

	void shutdown() { }

	/**
	 * Set the interactive mode
	 */
	void setInteractive() { m_interactive = true; }
	/**
	 * Returns the interactive mode state
	 */
	bool isInteractive() { return m_interactive; }
	/**
	 * Set the opcode dumper
	 */
	void setOpcodeDump() { m_opcode_dump = true; }
	/**
	 * Returns the opcode dump state
	 */
	bool isOpcodeDump() { return m_opcode_dump; }
	/**
	 * Returns the opcode list
	 */
	OpcodeList& getOpcodes() { return m_opcodes; }

	AST_VISITOR_DECLARATION(AST_VISITOR_DECL);

private:
	bool m_interactive, m_opcode_dump;
	OpcodeList m_opcodes;
	JmpStack m_brks;

	/**
	 * Output an opcode.
	 */
	Opcode* emit(Opcodes type, VM::opcode_handler handler, Value* op1 = NULL, Value* op2 = NULL, Value* result = NULL) {
		Opcode* opcode = new Opcode(type, handler, op1, op2, result);
		m_opcodes.push_back(opcode);
		/**
		 * Sets the opcode number, which is used by JMP opcodes
		 */
		opcode->setOpNum(getOpNum());

		return opcode;
	}

	/**
	 * Returns the opcode number
	 */
	size_t getOpNum() const { return !m_opcodes.size() ? 0 : m_opcodes.size()-1; }

	DISALLOW_COPY_AND_ASSIGN(CodeGenVisitor);
};

}} // clever::ast

#endif /* CLEVER_CGVSITIOR_H */
