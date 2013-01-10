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
#include "core/value.h"
#include "core/environment.h"

namespace clever {

class Value;
class Scope;

typedef std::vector<Type*> TypePool;
typedef std::vector<Value*> ValuePool;

/// Symbol representation
struct Symbol {
	Symbol() {}

	Symbol(const CString *name_, Scope *scope_ = NULL)
		: name(name_), scope(scope_) {}

	~Symbol() {}

	const CString* name;
	ValueOffset voffset;
	const Scope *scope;

private:
	DISALLOW_COPY_AND_ASSIGN(Symbol);
};

/// Scope representation
class Scope {
public:
	typedef std::vector<Scope*> ScopeVector;
	typedef std::vector<Symbol*> SymbolMap;
	typedef std::tr1::unordered_map<const CString*, size_t> SymbolTable;
	typedef SymbolTable::value_type SymbolEntry;

	Scope()
		: m_parent(NULL), m_children(), m_symbols(), m_size(0), m_id(0),
		  m_value_id(0), m_value_pool(), m_environment(NULL) {}

	explicit Scope(Scope* parent)
		: m_parent(parent), m_children(), m_symbols(), m_size(0), m_id(0),
		  m_value_id(0), m_value_pool(), m_environment(NULL) {}

	~Scope();

	Symbol* pushValue(const CString* name, Value* value) {
		Symbol* sym = new Symbol(name, this);

		m_symbols.push_back(sym);
		m_symbol_table.insert(SymbolEntry(name, m_size++));
		m_value_pool.push_back(value);

		return sym;
	}

	Value* getValue(const ValueOffset& offset) const { return m_environment->getValue(offset); }

	Symbol& at(size_t idx) const { return *m_symbols[idx]; }

	void setId(size_t id) { m_id = id; }

	size_t getId() const { return m_id; }

	size_t size() const { return m_size; }

	void copy(const Scope* s) {
		for (size_t id = 0; id < s->m_value_pool.size(); ++id) {
			const Value* u = s->m_value_pool[id];
			Value* v = new Value;

			m_value_pool.push_back(v);
			v->copy(u);
		}
	}

	Scope* enter() {
		Scope* s = new Scope(this);
		m_children.push_back(s);
		return s;
	}

	Scope* leave() {
		return m_parent;
	}

	std::vector<Scope*> flatten();

	Scope* getParent() const { return m_parent; }

	Symbol* getLocal(const CString*);
	Symbol* getAny(const CString*);

	Environment* getEnvironment() const { return m_environment; }
	void setEnvironment(Environment* e) {
		CLEVER_SAFE_DELREF(m_environment);
		m_environment = e;
		CLEVER_SAFE_ADDREF(m_environment);
	}

	std::pair<size_t, size_t> getOffset(Symbol* sym) const;

	const ScopeVector& getChildren() const { return m_children; }
private:
	Scope* m_parent;
	ScopeVector m_children;
	SymbolMap m_symbols;
	SymbolTable m_symbol_table;
	size_t m_size;
	size_t m_id;
	size_t m_value_id;

	ValuePool m_value_pool;

	Environment* m_environment;

	DISALLOW_COPY_AND_ASSIGN(Scope);
};



} // clever

#endif // CLEVER_SCOPE_H
