/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
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
#include "core/ast.h"
#include "core/codegen.h"

namespace clever {

class Type;
class Value;
class location;

typedef std::vector<Type*> TypePool;

typedef std::vector<const CString*> ArgDeclList;
typedef std::vector<std::pair<size_t, size_t> > ArgCallList;

/// Compiler representation
class Compiler {
public:
	enum CompilerFlag {
		DUMP_AST = 1,
		USE_OPTIMIZER,
		INTERACTIVE
	};

	Compiler()
		: m_ir(), m_scope(NULL), m_flags(0),
			m_scope_pool(10), m_type_pool(15), m_const_pool(15),m_tmp_pool(15),
			m_scope_id(0), m_const_id(0), m_type_id(0), m_tmp_id(0) {}

	~Compiler() {}

	void init();
	void shutdown();

	void emitAST(ast::Node *tree);

	void setFlags(size_t flags) { m_flags = flags; }

	IRVector& getIR() { return m_ir; }

	ScopePool* getSymbolTable() { return &m_scope_pool; }

	ValuePool* getConstantPool() { return &m_const_pool; }

	ValuePool* getTemporaryPool() { return &m_tmp_pool; }

    size_t getTempValue();

	const PkgManager& getPkgManager() const { return m_pkg; }

	size_t addConstant(Value*);

	static void error(const char*);
	static void error(const std::string&, const location&);
	static void errorf(const location&, const char*, ...);
private:
	// Package manager
	PkgManager m_pkg;

	// Vector of instructions to be passed to VM
	IRVector m_ir;

	// Scope handling
	Scope* m_scope;

	// Compiler flag
	size_t m_flags;

	// Compiler pools, which got passed to VM after compiling
	ScopePool m_scope_pool;
	TypePool m_type_pool;
	ValuePool m_const_pool;
	ValuePool m_tmp_pool;

	// Indexes for pools
	size_t m_scope_id;
	size_t m_const_id;
	size_t m_type_id;
	size_t m_tmp_id;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
