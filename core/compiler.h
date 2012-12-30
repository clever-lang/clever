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
    Compiler()
        : m_ir(), m_scope(NULL), m_scope_pool(10),
          m_type_pool(15), m_scope_id(0), m_type_id(0), m_tmp_vals() {}

    ~Compiler() {}

    // Starts the compilation phase
    void init();

    void emitAST(ast::Block*);

    // Shutdown the compiler freeing all resources
    void shutdown();

    IRVector& getIR() { return m_ir; }

    ScopePool* getSymbolTable() { return &m_scope_pool; }

	const PkgManager& getPkgManager() const { return m_pkg; }

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
