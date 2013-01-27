/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/environment.h"
#include "core/value.h"

namespace clever {

Environment* Environment::activate(Environment* outer) const
{
	Environment* env = new Environment(outer, false);
	env->m_active = true;

	for (size_t i = 0, size = m_data.size(); i < size; ++i) {
		env->pushValue(m_data[i]->clone());
	}

	return env;
}

Value* Environment::getValue(const ValueOffset& offset) const
{
	if (offset.first == 0) { // local
		clever_assert(offset.second < m_data.size(),
				"`offset.second` must be within `m_data` limits.");

		return m_data.at(offset.second);
	}

	size_t depth = offset.first;
	Environment* env = m_outer;

    while (env && --depth) {
        env = env->m_outer;
    }

	clever_assert(depth == 0,
			"`depth` must be zero, otherwise we failed to find the environment.");
	clever_assert(offset.second < env->m_data.size(),
			"`offset.second` must be within `m_data` bounds.");
	clever_assert_not_null(env);

	return env->m_data.at(offset.second);
}

void Environment::copy(const Environment* _env)
{
	Environment* _this = this;

	while (_env != NULL) {
		const Environment* env = _env;

		_this->m_active = env->m_active;
		_this->m_ret_addr = env->m_ret_addr;

		if (env->m_ret_val != NULL) {
			_this->m_ret_val = env->m_ret_val->clone();
		} else {
			_this->m_ret_val = NULL;
		}

		for (size_t i = 0, size = env->m_data.size(); i < size; ++i) {
			_this->pushValue(env->m_data[i]->clone());
		}

		if (env->m_outer != NULL) {
			_this->m_outer = new Environment(NULL, false);
			_env = env->m_outer;
			_this = _this->m_outer;
		} else {
			_this->m_outer = NULL;
			_env = NULL;
		}
	}
}

} // clever
