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

#include "core/cstring.h"
#include "core/compiler.h"
#include "core/scope.h"
#include "core/value.h"
#include "core/location.hh"
#include "types/native_types.h"

namespace clever {

// Declaration of namespace global type ptrs for Clever native types
DECLARE_CLEVER_NATIVE_TYPES();

/// Compiler initialization phase
void Compiler::init()
{
	m_scope = new Scope;

	m_ir.reserve(20);
	m_tmp_vals.reserve(15);
	m_scope_pool.reserve(10);
	m_type_pool.reserve(15);

	m_scope_pool[m_scope_id++] = m_scope;

	// Native type allocation
	m_type_pool[m_type_id++] = CLEVER_INT_TYPE    = new IntType;
	m_type_pool[m_type_id++] = CLEVER_DOUBLE_TYPE = new DoubleType;
	m_type_pool[m_type_id++] = CLEVER_STR_TYPE    = new StrType;
	m_type_pool[m_type_id++] = CLEVER_FUNC_TYPE   = new FuncType;

	m_pkg.init();
}

/// Frees all resource used by the compiler
void Compiler::shutdown()
{
	m_pkg.shutdown();

	CLEVER_SAFE_DELETE(g_cstring_tbl);
	CLEVER_SAFE_DELETE(m_scope);

	TypePool::const_iterator it = m_type_pool.begin(),
		end = m_type_pool.end();

	while (it != end) {
		delete *it;
		++it;
	}

	ValuePool::const_iterator it2 = m_tmp_vals.begin(),
		end2 = m_tmp_vals.end();

	while (it2 != end2) {
		(*it2)->delRef();
		++it2;
	}
}

// Compiler termination phase
void Compiler::end()
{
}

/// Displays an error message and exits
void Compiler::error(const char* msg) const
{
	std::cerr << "Compile error: " << msg << std::endl;
	CLEVER_EXIT_FATAL();
}

/// Displays an error message
void Compiler::error(const std::string& message, const location& loc) const
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
void Compiler::errorf(const location& loc, const char* format, ...) const
{
	std::ostringstream out;
	va_list args;

	va_start(args, format);

	vsprintf(out, format, args);

	va_end(args);

	error(out.str(), loc);
}

} // clever
