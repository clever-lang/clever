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

/// Compiler representation
class Compiler {
public:
    Compiler()
        : m_ir(), m_scope(NULL), m_scope_pool(10),
          m_type_pool(15), m_scope_id(0), m_type_id(0), m_tmp_vals() {}

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

    // Used to store temporary computation Value ptr
    ValuePool m_tmp_vals;

    DISALLOW_COPY_AND_ASSIGN(Compiler);
};

} // clever

#endif // CLEVER_COMPILER_H
