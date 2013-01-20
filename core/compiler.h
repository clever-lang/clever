/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>
#include <stack>
#include <sstream>
#include "core/pkgmanager.h"
#include "core/codegen.h"
#include "core/scope.h"

namespace clever {

class Type;
class Value;
class location;
class Scope;

/// Compiler representation
class Compiler {
public:
	enum CompilerFlag {
		DUMP_AST       = 1 << 1,
		USE_OPTIMIZER  = 1 << 2,
		PARSER_ONLY    = 1 << 3,
		INTERACTIVE    = 1 << 4
	};

	Compiler()
		: m_pkg(), m_ir(),
		  m_scope_pool(), m_const_env(),m_temp_env(), m_global_env(),
		  m_flags(0), m_scope_id(0), m_const_id(0), m_tmp_id(0) {}

	~Compiler() {}

	void init();
	void shutdown();

	void emitAST(ast::Node*);

	void setFlags(size_t flags) { m_flags = flags; }

	IRVector& getIR() { return m_ir; }

	ScopePool* getSymbolTable() { return &m_scope_pool; }

	Environment* getGlobalEnv() const { return m_global_env; }
	Environment* getConstEnv() const { return m_const_env; }
	Environment* getTempEnv() const { return m_temp_env; }

	static void error(const char*) CLEVER_NO_RETURN;
	static void error(const std::string&, const location&) CLEVER_NO_RETURN;
	static void errorf(const location&, const char*, ...) CLEVER_NO_RETURN;
private:
	// Package manager
	PkgManager m_pkg;

	// Vector of instructions to be passed to VM
	IRVector m_ir;

	// Compiler pools, which got passed to VM after compiling
	ScopePool m_scope_pool;
	Environment* m_const_env;
	Environment* m_temp_env;
	Environment* m_global_env;

	// Compiler flag
	size_t m_flags;

	// Indexes for pools
	size_t m_scope_id;
	size_t m_const_id;
	size_t m_tmp_id;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
