/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_ENVIRONMENT_H
#define CLEVER_ENVIRONMENT_H

#include <algorithm>
#include <vector>
#include "core/refcounted.h"

namespace clever {

class Value;
class Environment;

/// @brief a pair specifying how many environments to `escape` and what value to fetch.
typedef std::pair<size_t, size_t> ValueOffset;

/**
 * @brief the environment class.
 *
 * Environment instances are the *activation records* used on the VM's call
 * stack. They are used to store local variables and return values/addresses of
 * the current running function. Environments also hold pointers to their
 * enclosing environment so as to allow access to values external to the
 * environment.
 *
 * During the code compilation and interpretation stages, some non-activated
 * environments are created to be used as blueprints for the virtual machine.
 * The later takes those environments and *activate* them upon user function
 * call or thread creation.
 *
 */
class Environment: public RefCounted {
public:
	Environment()
		: m_outer(NULL), m_temp(NULL), m_ret_val(NULL),
		m_ret_addr(0), m_scoped(true) {}

	explicit Environment(Environment* outer_, bool is_scoped = true)
		: m_outer(outer_), m_temp(NULL), m_ret_val(NULL),
		m_ret_addr(0), m_scoped(is_scoped) {
		clever_addref(m_outer);
	}

	~Environment() {
		clever_delref(m_outer);

		if (!m_scoped) {
			clever_delref(m_temp);
		}

		std::for_each(m_data.begin(), m_data.end(), clever_delref);
	}

	/**
	 * @brief pushes a value into the environment.
	 * @param value
	 * @return the index of the newly pushed value.
	 */
	ValueOffset pushValue(Value* value) {
		m_data.push_back(value);
		return ValueOffset(0, m_data.size()-1);
	}

	/**
	 * @brief get the value specified by `offset`.
	 *
	 * @note This function may introduce performance issues when searching for
	 *       global values due to the chain-like nature of environments.
	 *
	 * @param offset
	 * @return
	 */
	Value* getValue(const ValueOffset&) const;

	/**
	 * @brief ativates the current environment.
	 *
	 * This method should be used to create new stack frames within the virtual
	 * machine. Usually, this method will be called on a Function's initial
	 * environment.
	 *
	 * @param optional outer the environment where the current instance is contained in
	 * @return an "activated" copy of the current environment
	 */
	Environment* activate(Environment* = NULL);

	size_t getRetAddr() const { return m_ret_addr; }
	void setRetAddr(size_t ret_addr) { m_ret_addr = ret_addr; }

	Value* getRetVal() const { return m_ret_val; }
	void setRetVal(Value* ret_val) { m_ret_val = ret_val; }

	Environment* getOuter() const { return m_outer; }
	void setOuter(Environment* outer) {
		clever_delref(m_outer);
		m_outer = outer;
		clever_addref(outer);
	}

	void setData(size_t pos, Value* value) { m_data[pos] = value; }
	std::vector<Value*>& getData() { return m_data; }

	void setTempEnv(Environment* env) { m_temp = env; }
	Environment* getTempEnv() const { return m_temp; }

private:
	Environment* m_outer;
	Environment* m_temp;
	std::vector<Value*> m_data;
	Value* m_ret_val;
	size_t m_ret_addr;
	bool m_scoped;

	Environment* clone();

	DISALLOW_COPY_AND_ASSIGN(Environment);
};

} // clever

#endif // CLEVER_ENVIRONMENT_H
