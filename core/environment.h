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
    Environment(Environment* outer_)
        : RefCounted(0), m_outer(outer_), m_data(), m_activated(false) {
        CLEVER_SAFE_ADDREF(m_outer);
    }

    ~Environment() {
        CLEVER_SAFE_DELREF(m_outer);
    }

    /**
     * @brief pushes a value into the environment.
     * @param value
     * @return the index of the newly pushed value.
     */
    size_t pushValue(Value* value);

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

private:
    Environment* m_outer;
    std::vector<Value*> m_data;
    bool m_activated;

    DISALLOW_COPY_AND_ASSIGN(Environment);

};

inline size_t Environment::pushValue(Value* value) {
    m_data.push_back(value);
    return m_data.size()-1;
}

inline Value* Environment::getValue(const ValueOffset& offset) {
    if (offset.first == 0) { // local

		clever_assert(offset.second < m_data.size(),
					  "`offset.second` must be within `m_data` bounds.");

        return m_data.at(offset.second);
    }

    size_t depth = offset.second;
    Environment* e = m_outer;

    while (e && depth--) {
        e = e->m_outer;
    }

	clever_assert(depth == 0,
				  "`depth` must be zero, otherwise we failed to find the environment.");
	clever_assert(offset.second < m_data.size(),
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
