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

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include <tr1/unordered_map>
#include <vector>
#include <stack>
#include <sstream>
#include "core/clever.h"
#include "core/scope.h"
#include "core/pkgmanager.h"
#include "core/ir.h"

namespace clever {

class Type;
class Value;
class location;

typedef std::vector<Scope*> ScopePool;
typedef std::vector<Type*> TypePool;

typedef std::vector<const CString*> ArgDeclList;
typedef std::vector<std::pair<size_t, size_t> > ArgCallList;

enum NodeType {
	SYMBOL, // For symbol name
	VALUE,  // For Value ptr
	TEMP    // For temporary Value ptr
};

struct Node {
	union NodeData {
		Value* val;
		const CString* str;
	} data;

	NodeType type;
};

/// Compiler representation
class Compiler {
public:
	Compiler()
		: m_ir(), m_scope(NULL), m_scope_pool(10),
			m_type_pool(15), m_scope_id(0), m_type_id(0),
			m_curr_func(0), m_tmp_vals() {}

	~Compiler() {}

	// Starts the compilation phase
	void init();

	// Ends the compilation phase
	void end();

	// Shutdown the compiler freeing all resources
	void shutdown();

	IRVector& getIR() { return m_ir; }

	ScopePool* getSymbolTable() { return &m_scope_pool; }

	void error(const char*) const;
	void error(const std::string&, const location&) const;
	void errorf(const location&, const char*, ...) const;

	Value* getValue(Node&, Symbol**, const location&) const;

	// Compilation methods
	void varDeclaration(Node&, Node*, const location&);
	void newScope();
	void endScope();
	void assignment(Node&, Node&, const location&);
	void binOp(Opcode, Node&, Node&, Node&, const location&);
	void funcDecl(Node&, ArgDeclList*, const location&);
	void funcEndDecl(bool);
	void funcCall(Node&, ArgCallList*, Node&, const location&);
    void threadCall(Node&, ArgCallList*, Node&, const location&);
	ArgDeclList* newArgDeclList(const CString*) const;
	ArgCallList* addArgCall(ArgCallList*, Node&, const location&);
	void retStmt(Node*, const location&);
	void importStmt(Node&);
	void importStmt(Node&, Node&);
	void whileLoop(Node&, const location&);
	void endWhileLoop();
	void incDec(Opcode, Node&, Node&, const location&);
private:
	// Package manager
	PkgManager m_pkg;

	// Vector of instructions to be passed to VM
	IRVector m_ir;

	// Scope handling
	Scope* m_scope;

	// Compiler pools, which got passed to VM after compiling
	ScopePool m_scope_pool;
	TypePool m_type_pool;

	// Indexes for pools
	size_t m_scope_id;
	size_t m_value_id;
	size_t m_type_id;

	// Used to point the instruction index on m_ir related to JMP created
	// just before the current func declaration to skip his internal opcodes
	size_t m_curr_func;

	// Used to store temporary computation Value ptr
	ValuePool m_tmp_vals;

	std::stack<std::vector<size_t> > m_jmps;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
