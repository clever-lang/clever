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

/// Compiler initialization phase
void Compiler::init()
{
	m_pkg.init();
}

/// Frees all resource used by the compiler
void Compiler::shutdown()
{
	if (m_const_env) {
		m_const_env->clear();
		clever_delref(m_const_env);
	}

	if (m_temp_env) {
		m_temp_env->clear();
		clever_delref(m_temp_env);
	}

	if (m_scope_pool.size()) {
		clever_delete_var(m_scope_pool[0]);
	}

	m_pkg.shutdown();

	clever_delete_var(g_cstring_tbl);
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
	if (!tree) {
		return;
	}

	if (m_flags & USE_OPTIMIZER) {
		ast::Evaluator evaluator;
		tree = tree->accept(evaluator);
	}
	if (m_flags & DUMP_AST) {
		ast::Dumper astdump;
		tree->accept(astdump);
	}

	ast::Resolver resolver(m_pkg);
	tree->accept(resolver);

	if (!(m_flags & PARSER_ONLY)) {
		m_scope_pool = resolver.getSymTable()->flatten();

		m_global_env = resolver.getGlobalEnv();

		ast::Codegen codegen(m_ir, this, m_global_env);
		tree->accept(codegen);

		m_const_env = codegen.getConstEnv();
		m_temp_env  = codegen.getTempEnv();

		m_ir.push_back(IR(OP_HALT));
	}

	clever_delete_var(tree);
}

} // clever
