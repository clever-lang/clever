/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_SCOPE_H
#define CLEVER_SCOPE_H

#ifdef CLEVER_MSVC
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif
#include <vector>
#include <algorithm>
#include "core/environment.h"
#include "core/cstring.h"

namespace clever {

class Scope;
class Value;

/// Symbol representation
struct Symbol {
	Symbol()
		: name(NULL), voffset(0,0), scope(NULL) {}

	Symbol(const CString *name_, Scope *scope_ = NULL)
		: name(name_), voffset(0,0), scope(scope_) {}

	~Symbol() {}

	const CString* name;
	ValueOffset voffset;
	const Scope* scope;

private:
	DISALLOW_COPY_AND_ASSIGN(Symbol);
};

/// Scope representation
class Scope {
public:
	typedef std::vector<Scope*> ScopeVector;
	typedef std::vector<Symbol*> SymbolMap;
	typedef std::tr1::unordered_map<const CString*, size_t> SymbolTable;

	Scope()
		: m_parent(NULL), m_environment(NULL) {}

	explicit Scope(Scope* parent)
		: m_parent(parent), m_environment(NULL) {}

	~Scope();

	void pushValue(const CString* name, Value* value) {
		Symbol* sym = new Symbol(name, this);

		m_symbols.push_back(sym);
		m_symbol_table.insert(SymbolTable::value_type(name, m_symbol_table.size()));

		clever_assert_not_null(m_environment);

		sym->voffset = m_environment->pushValue(value);
	}

	Value* getValue(const ValueOffset& offset) const {
		return m_environment->getValue(offset);
	}

	Scope* enter() {
		Scope* s = new Scope(this);
		m_children.push_back(s);
		return s;
	}

	Scope* leave() const { return m_parent; }

	std::vector<Scope*> flatten();

	Scope* getParent() const { return m_parent; }

	Symbol* getLocal(const CString*);
	Symbol* getAny(const CString*);

	Environment* getEnvironment() const { return m_environment; }
	void setEnvironment(Environment* env) {	m_environment = env; }

	std::pair<size_t, size_t> getOffset(const Symbol* sym) const;

	const ScopeVector& getChildren() const { return m_children; }
private:
	Scope* m_parent;
	ScopeVector m_children;
	SymbolMap m_symbols;
	SymbolTable m_symbol_table;

	Environment* m_environment;

	DISALLOW_COPY_AND_ASSIGN(Scope);
};

} // clever

#endif // CLEVER_SCOPE_H
