/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_IRBUILDER_H
#define CLEVER_IRBUILDER_H

#include "core/scope.h"
#include "core/environment.h"
#include "core/ir.h"

namespace clever {

/**
 * @brief Covenience class to create CleverVM instructions.
 */
class IRBuilder {
public:
    IRBuilder(Environment* init_glbenv, Scope* global_scope)
		: m_global_scope(global_scope) {
        m_const_env = new Environment(init_glbenv, false);
        m_temp_env  = new Environment(init_glbenv, false);

        // null, true and false
        m_const_env->pushValue(new Value());
        m_const_env->pushValue(new Value(true));
        m_const_env->pushValue(new Value(false));
    }

    ~IRBuilder() {
		clever_delref(m_const_env);
		clever_delref(m_temp_env);
		clever_delete(m_global_scope);
	}

    /// @brief push an instruction to the IR vector
	IR& push(const IR& ir) {
        m_ir.push_back(ir);
        return m_ir.back();
    }

    /// @brief construct and push an instruction to the IR vector
    IR& push(const Opcode& op) {
		return push(IR(op));
    }

    /// @brief construct and push an instruction to the IR vector
    IR& push(const Opcode& op, const Operand& a) {
		return push(IR(op, a));
    }

    /// @brief construct and push an instruction to the IR vector
    IR& push(const Opcode& op, const Operand& a, const Operand& b) {
		return push(IR(op, a, b));
    }

    Environment* getConstEnv() const { return m_const_env; }
    Environment* getTempEnv() const { return m_temp_env; }

    const IRVector& getIR() const { return m_ir; }

    size_t getSize() const { return m_ir.size(); }

    IR& getLast() { return m_ir.back(); }

    IR& getAt(size_t index) {
        return m_ir.at(index);
    }

    /// @brief get a constant offset for the `c` value
    ValueOffset getInt(long c) {
        return m_const_env->pushValue(new Value(c, true));
    }

    /// @brief get a constant offset for the `c` value
    ValueOffset getDouble(double c) {
        return m_const_env->pushValue(new Value(c, true));
    }

    /// @brief get a constant offset for the `c` value
    ValueOffset getString(const CString* c) {
        return m_const_env->pushValue(new Value(c, true));
    }

    /// @brief get a constant offset for the `null` value
    ValueOffset getNull() const {
        return ValueOffset(0, 0);
    }

    /// @brief get a constant offset for the `true` value
    ValueOffset getTrue() const {
        return ValueOffset(0, 1);
    }

    /// @brief get a constant offset for the `false` value
    ValueOffset getFalse() const {
        return ValueOffset(0, 2);
    }

    /// @brief get a constant offset for a temporary value
    ValueOffset getTemp() {
        return m_temp_env->pushValue(new Value());
    }

private:
	Scope* m_global_scope;
	Environment* m_const_env;
	Environment* m_temp_env;

	IRVector m_ir;
};

} // clever

#endif // CLEVER_IRBUILDER_H
