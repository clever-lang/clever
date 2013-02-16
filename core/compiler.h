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
#include "core/modmanager.h"
#include "core/codegen.h"
#include "core/irbuilder.h"

namespace clever {

class Driver;
class location;

/// Compiler representation
class Compiler {
public:
	enum CompilerFlag {
		NO_FLAGS       = 0,
		INITIALIZED    = 1 << 0,
		DUMP_AST       = 1 << 1,
		USE_OPTIMIZER  = 1 << 2,
		PARSER_ONLY    = 1 << 3,
		INTERACTIVE    = 1 << 4
	};

	Compiler(Driver* driver)
		: m_tree(NULL), m_pkg(driver), m_builder(NULL), m_global_env(), m_flags(0) {}

	~Compiler() {}

	void init(const CString*);
	void shutdown();

	void setFlags(size_t flags) { m_flags |= flags; }

	void setAST(ast::Node* tree) { m_tree = tree; }
	ast::Node* getAST() { return m_tree; }

	void genCode();
	const IRVector& getIR() { return m_builder->getIR(); }

	Environment* getGlobalEnv() const { return m_global_env; }
	Environment* getConstEnv() const { return m_builder->getConstEnv(); }
	Environment* getTempEnv() const { return m_builder->getTempEnv(); }

	void setNamespace(const std::string& ns_name) { m_ns_name = ns_name; }
	const std::string& getNamespace() const { return m_ns_name; }

	static void error(const char*) CLEVER_NO_RETURN;
	static void error(const std::string&, const location&) CLEVER_NO_RETURN;
	static void errorf(const location&, const char*, ...) CLEVER_NO_RETURN;

private:
	// AST tree
	ast::Node* m_tree;

	// Module manager
	ModManager m_pkg;

	// Vector of instructions to be passed to VM
	IRBuilder* m_builder;

	// Compiler pools, which got passed to VM after compiling
	Environment* m_global_env;

	// Compiler flag
	size_t m_flags;

	std::string m_ns_name;

	DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
