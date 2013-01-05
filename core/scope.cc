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

} // clever
