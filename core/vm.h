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
#include "core/cthread.h"
#include "core/cexception.h"
#include "core/clever.h"
#include "core/value.h"

namespace clever {

class Function;
class VM;
class Environment;
class location;

struct CallStackEntry {
	Environment* env;
	const Function* func;
	const location* loc;

	explicit CallStackEntry(Environment* env_,
		const Function* func_ = NULL, const location* loc_ = NULL)
		: env(env_), func(func_), loc(loc_) {}
};

typedef std::stack<CallStackEntry> CallStack;

/// VM representation
class VM {
public:
	VM()
		: m_pc(0), m_const_env(NULL), m_global_env(NULL), m_mutex(NULL), m_main(true) {}

	explicit VM(const IRVector& inst)
		: m_pc(0), m_const_env(NULL), m_global_env(NULL), m_mutex(NULL), m_main(true) {
		m_inst.resize(inst.size());
		std::copy(inst.begin(), inst.end(), m_inst.begin());
	}

	VM(const VM& vm) {
		m_mutex      = vm.m_mutex;
		m_main       = false;
		m_pc         = vm.m_pc;
		m_inst       = vm.m_inst;
		m_try_stack  = vm.m_try_stack;
		m_global_env = vm.m_global_env;
		m_call_stack = vm.m_call_stack;
		m_const_env  = vm.m_const_env;
	}

	~VM() {
		if (m_main && m_mutex) {
			delete m_mutex;
		}
	}

	void setGlobalEnv(Environment* globals) { m_global_env = globals; }
	void setConstEnv(Environment* consts) { m_const_env = consts; }

	void setChild() { m_main = false; }
	bool isChild() const { return !m_main; }
	bool isMain() const { return m_main; }

	void setPC(size_t pc) { m_pc = pc; }
	size_t getPC() const { return m_pc; }
	void nextPC() { ++m_pc; }

	CMutex* getMutex() {
		if (!m_mutex) {
			m_mutex = new CMutex;
		}
		return m_mutex;
	}

	/// Start the VM execution
	void run();

	/// Executes an specific function
	Value* runFunction(const Function*, const ValueVector&);

	/// Methods for dumping opcodes
#ifdef CLEVER_DEBUG
	static void dumpOperand(const Operand&);
	void dumpOpcodes() const;
#endif
private:
	CallStack& getCallStack() { return m_call_stack; }

	/// Helper to fetch the current environment according to the operand type
	Environment* getCurrentEnvironment(OperandType) const;

	/// Helper to retrive a Value* from environment
	Value* getValue(const Operand&) const;

	/// Helper to change a value pointer on environment
	void setValue(const Operand&, Value*) const;

	/// Helper to prepare a function/method call
	void prepareCall(const Function*, Environment* = NULL);

	/// Helper to check member context access
	bool checkContext(const MemberData&) const;

	/// Helper to create a new instance
	void createInstance(const Type*, Value*);

	/// Helper for common operations
	void binOp(const IR&);
	void logicOp(const IR&);

	/// Dumps the stack trace
	void dumpStackTrace(std::ostringstream&);

	/// Error reporting
	void throwUncaughtException(const IR&) CLEVER_NO_RETURN;
	static void error(const location&, const char*, ...) CLEVER_NO_RETURN;

	/// VM program counter
	size_t m_pc;

	/// Vector of instruction
	std::vector<IR> m_inst;

	/// Constant
	Environment* m_const_env;

	/// Globals
	Environment* m_global_env;

	/// Call arguments
	ValueVector m_call_args;

	/// Exception handling
	CException m_exception;

	/// Stack frame
	CallStack m_call_stack;

	/// Try-catch block tracking
	std::stack<std::pair<size_t, size_t> > m_try_stack;

	/// User object instance vector
	std::stack<std::vector<Environment*> > m_obj_store;

	CMutex* m_mutex;

	bool m_main;
};

} // clever

#endif // CLEVER_VM_H
