/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <stack>
#include <vector>
#include "core/ir.h"
#include "core/codegen.h"
#include "core/cthread.h"
#include "core/cexception.h"
#include "core/clever.h"
#include "core/user.h"

namespace clever {

class ValueObject;
class Value;
class Function;
class VM;

struct VMThread {
	CThread t_handler;
	VM* vm_handler;
};

/// VM representation
class VM {
public:
	VM()
		: m_pc(0), f_mutex(NULL), m_const_env(NULL), m_global_env(NULL), m_main(true) {}

	VM(const IRVector& inst)
		: m_pc(0), f_mutex(NULL), m_const_env(NULL), m_global_env(NULL), m_main(true) {
		m_inst.resize(inst.size());
		std::copy(inst.begin(), inst.end(), m_inst.begin());
	}

	~VM() {}

	void setGlobalEnv(Environment* globals) { m_global_env = globals; }
	void setConstEnv(Environment* consts) { m_const_env = consts; }

	void copy(const VM*, bool);

	void setChild() { m_main = false; }
	bool isChild() const { return !m_main; }
	bool isMain() const { return m_main; }

	void setPC(size_t pc) { m_pc = pc; }
	size_t getPC() const { return m_pc; }
	void nextPC() { ++m_pc; }

	CallStack getCallStack() const { return m_call_stack; }

	/// Helper to retrive a Value* from ValuePool
	Value* getValue(const Operand&) const;

	/// Helper to change a temporary value pointer
	Value* setTempValue(const Operand&, Value*) const;

	CallStack& getCallStack() { return m_call_stack; }

	CMutex* getMutex() { return isChild() ? f_mutex : &m_mutex; }

	void prepareCall(const Function*, Environment* = NULL);
	void createInstance(const Type*, Value*);
	void binOp(const IR&);
	void logicOp(const IR&);

	/// Start the VM execution
	void run();
	Value* runFunction(const Function*, std::vector<Value*>*);


	/// Methods for dumping opcodes
#ifdef CLEVER_DEBUG
	static void dumpOperand(const Operand&);
	void dumpOpcodes() const;
#endif

	static void error(const location&, const char*, ...) CLEVER_NO_RETURN;
private:
	/// VM program counter
	size_t m_pc;
	CMutex* f_mutex;

	/// Constant
	Environment* m_const_env;

	/// Globals
	Environment* m_global_env;

	CException m_exception;

	CMutex m_mutex;

	/// Stack frame
	CallStack m_call_stack;

	std::stack<std::pair<size_t, size_t> > m_try_stack;

	/// Vector of instruction
	std::vector<IR> m_inst;

	/// Call arguments
	std::vector<Value*> m_call_args;
	std::vector<Environment*> m_obj_store;


	bool m_main;
	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
