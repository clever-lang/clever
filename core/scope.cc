/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/scope.h"

namespace clever {

Scope::~Scope() {
    ValuePool::const_iterator itv = m_value_pool.begin(),
        endv = m_value_pool.end();

    CLEVER_SAFE_DELREF(m_environment);

    while (itv != endv) {
        CLEVER_SAFE_DELREF(*itv);
        ++itv;
    }

    ScopeVector::const_iterator it = m_children.begin(),
        end = m_children.end();

    while (it != end) {
        delete *it;
        ++it;
    }

    SymbolMap::const_iterator its = m_symbols.begin(),
        ends = m_symbols.end();

    while (its != ends) {
        delete *its;
        ++its;
    }

    TypePool::const_iterator itt = m_type_pool.begin(),
        endt = m_type_pool.end();

    while (itt != endt) {
        delete *itt;
        ++itt;
    }
}

std::vector<Scope*> Scope::flatten() {
    std::vector<Scope*> scopes;
    std::vector<Scope*>::iterator it(m_children.begin()), end(m_children.end());

    scopes.push_back(this);

    for (; it != end; it++) {
        std::vector<Scope*> flattened = (*it)->flatten();
        scopes.insert(scopes.end(), flattened.begin(), flattened.end());
    }

    return scopes;
}

Symbol* Scope::getLocal(const CString* name) {
    SymbolTable::iterator it = m_symbol_table.find(name);

    if (it == m_symbol_table.end()) {
        return NULL;
    }
    return m_symbols[it->second];
}

/// Resolve a symbol name recursively
Symbol* Scope::getAny(const CString* name) {
    Symbol* sym = getLocal(name);

    if (sym != NULL) {
        return sym;
    }

    Scope* v = m_parent;
    while (v != NULL) {
        sym = v->getLocal(name);

        if (sym != NULL) {
            return sym;
        }

        v = v->m_parent;
    }

    return sym;
}

ValueOffset Scope::getDepth(Symbol* sym) {
    size_t depth = 0;
    size_t value = 0;
    SymbolMap::iterator it = std::find(m_symbols.begin(), m_symbols.end(), sym);

    if (it != m_symbols.end()) {
        value = std::distance(m_symbols.begin(), it);
    } else {
        for (Scope* parent = m_parent; parent != NULL; parent = parent->m_parent) {
            if (parent->m_environment != m_environment) {
                depth++;
            }

            it = std::find(parent->m_symbols.begin(), parent-> m_symbols.end(), sym);

            if (it != parent->m_symbols.end()) {
                value = std::distance(parent->m_symbols.begin(), it);
            }
            break;
        }
    }

    return ValueOffset(depth, value);
}

} // clever
