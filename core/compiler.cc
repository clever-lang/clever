/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/cstring.h"
#include "core/compiler.h"
#include "core/scope.h"
#include "core/value.h"
#include "core/location.hh"
#include "core/astdump.h"
#include "core/codegen.h"
#include "core/evaluator.h"
#include "core/resolver.h"

namespace clever {

// Declaration of namespace global type ptrs for Clever native types
DECLARE_CLEVER_NATIVE_TYPES();

/// Compiler initialization phase
void Compiler::init()
{
	m_pkg.init();
}

/// Frees all resource used by the compiler
void Compiler::shutdown()
{
	m_pkg.shutdown();

	CLEVER_SAFE_DELETE(g_cstring_tbl);

	//CLEVER_SAFE_DELREF(m_const_env);
	//CLEVER_SAFE_DELREF(m_temp_env);

	if (m_scope_pool.size()) {
		CLEVER_SAFE_DELETE(m_scope_pool[0]);
	}
}

/// Displays an error message and exits
void Compiler::error(const char* msg)
{
	std::cerr << "Compile error: " << msg << std::endl;
	CLEVER_EXIT_FATAL();
}

/// Displays an error message
void Compiler::error(const std::string& message, const location& loc)
{
	if (loc.begin.filename) {
		std::cerr << "Compile error: " << message << " on "
			<< *loc.begin.filename << " line " << loc.begin.line << "\n";
	} else {
		std::cerr << "Compile error: " << message << " on line "
			<< loc.begin.line << "\n";
	}
	CLEVER_EXIT_FATAL();
}

/// Displays a formatted error message and abort the compilation
void Compiler::errorf(const location& loc, const char* format, ...)
{
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	error(out.str(), loc);
}

void Compiler::emitAST(ast::Node* tree)
{
	if (tree) {
		if (m_flags & USE_OPTIMIZER) {
			ast::Evaluator evaluator;
			tree = tree->accept(evaluator);
		}
		if (m_flags & DUMP_AST) {
			ast::Dumper astdump;
			tree->accept(astdump);
		}

		ast::Resolver resolver(this);
		tree->accept(resolver);

		m_scope_pool = resolver.getSymTable()->flatten();

		for (size_t i = 0; i < m_scope_pool.size(); i++) {
			m_scope_pool[i]->setId(i);
		}

		m_global_env = resolver.getGlobalEnv();

		ast::Codegen codegen(m_ir, this, m_global_env);
		tree->accept(codegen);

		m_const_env = codegen.getConstEnv();
		m_temp_env  = codegen.getTempEnv();

		m_ir.push_back(IR(OP_HALT));

		delete tree;
	}
}

} // clever
