/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ENVIRONMENT_H
#define CLEVER_ENVIRONMENT_H

#include "core/value.h"
#include <stack>

namespace clever {

class Environment;

/// @brief a pair specifying how many environments to `escape` and what value to fetch.
typedef std::pair<size_t, size_t> ValueOffset;
typedef std::stack<Environment*> CallStack;

/**
 * @brief the environment class.
 */
class Environment: public RefCounted {
public:
	explicit Environment(Environment* outer_)
		: RefCounted(), m_outer(outer_), m_data(), m_activated(false) {
		CLEVER_SAFE_ADDREF(m_outer);
	}

	~Environment() {
		CLEVER_SAFE_DELREF(m_outer);

		for (size_t i = 0, size = m_data.size(); i < size; i++) {
			CLEVER_SAFE_DELREF(m_data.at(i));
		}
		m_data.clear();
	}

	/**
	 * @brief pushes a value into the environment.
	 * @param value
	 * @return the index of the newly pushed value.
	 */
	ValueOffset pushValue(Value* value);

	/**
	 * @brief get the value specified by `offset`.
	 *
	 * @note
	 * This function may introduce performance issues when searching for global
	 * values due to the chain-like nature of environments.
	 *
	 * @param offset
	 * @return
	 */
	Value* getValue(const ValueOffset& offset);

	/**
	 * @brief ativates the current environment.
	 *
	 * This method should be used to create new stack frames within the virtual
	 * machine. Usually, this method will be called on a Function's initial
	 * environment.
	 *
	 * @param outer the environment where the current instance is contained in
	 * @return an "activated" copy of the current environment
	 */
	Environment* activate(Environment* outer);

	size_t getRetAddr() const { return m_ret_addr; }
	void setRetAddr(size_t ret_addr) { m_ret_addr = ret_addr; }

private:
	Environment* m_outer;
	std::vector<Value*> m_data;
	size_t m_ret_addr;
	bool m_activated;

	DISALLOW_COPY_AND_ASSIGN(Environment);
};

inline ValueOffset Environment::pushValue(Value* value) {
	m_data.push_back(value);
	return ValueOffset(0, m_data.size()-1);
}

inline Value* Environment::getValue(const ValueOffset& offset) {
	if (offset.first == 0) { // local

		clever_assert(offset.second < m_data.size(),
					  "`offset.second` must be within `m_data` limits.");

		return m_data.at(offset.second);
	}

	size_t depth = offset.first;
	Environment* e = m_outer;

	while (e && --depth) {
		e = e->m_outer;
	}

	clever_assert(depth == 0,
				  "`depth` must be zero, otherwise we failed to find the environment.");
	clever_assert(offset.second < e->m_data.size(),
				  "`offset.second` must be within `m_data` bounds.");
	clever_assert_not_null(e);

	return e->m_data.at(offset.second);
}

inline Environment* Environment::activate(Environment* outer) {
	Environment* e = new Environment(outer);
	e->m_activated = true;

	for (size_t i = 0, size = m_data.size(); i < size; i++) {
		Value* v = new Value();
		v->copy(m_data[i]);
		e->pushValue(v);
	}

	return e;
}

} // clever

#endif // CLEVER_ENVIRONMENT_H
