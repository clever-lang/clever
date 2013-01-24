/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <map>
#include <stack>
#include <vector>
#include "core/ir.h"
#include "core/codegen.h"
#include "core/cthread.h"
#include "core/cexception.h"

namespace clever {

class Value;
class Function;
class VM;

struct VMThread {
	VM* vm_handler;
	CThread t_handler;
};

/// VM representation
class VM {
public:
	enum ErrorLevel {
		VM_ERROR,
		VM_WARNING
	};

	typedef std::vector<std::vector<VMThread*> > ThreadPool;

	VM(const IRVector& inst)
		: m_pc(0), m_main(true), m_inst(inst),
		  m_const_env(NULL), m_temp_env(NULL), m_global_env(NULL),
		  m_call_stack(), m_call_args(),
		  m_thread_pool(), m_mutex(), f_mutex(NULL), m_try_stack() {}

	~VM() {}

	void setGlobalEnv(Environment* globals) { m_global_env = globals; }

	void setConstEnv(Environment* consts) { m_const_env = consts; }

	void setTempEnv(Environment* temps) { m_temp_env = temps; }

	void copy(const VM*, bool);

	void setChild() { m_main = false; }

	bool isChild() const { return !m_main; }

	bool isMain() const { return m_main; }

	void setPC(size_t pc) { m_pc = pc; }

	size_t getPC() const { return m_pc; }

	void nextPC() { ++m_pc; }

	const IRVector& getInst() const { return m_inst; }

	CallStack getCallStack() const { return m_call_stack; }

	/// Helper to retrive a Value* from ValuePool
	Value* getValue(const Operand&) const;
	Value* getValueExt(const Operand& operand) const { return getValue(operand); }

	ThreadPool& getThreadPool() { return m_thread_pool; }

	CallStack& getCallStack() { return m_call_stack; }

	CMutex* getMutex() { return isChild() ? f_mutex : &m_mutex; }

	void prepareCall(const Function*);

	/// Start the VM execution
	void run();
	Value* runFunction(const Function*, std::vector<Value*>*);

	/// Wait threads
	void wait();

	/// Methods for dumping opcodes
#ifdef CLEVER_DEBUG
	static void dumpOperand(const Operand&);
	void dumpOpcodes() const;
#endif

	static void error(ErrorLevel, const char*, ...);
private:
	/// VM program counter
	size_t m_pc;

	bool m_main;

	/// Vector of instruction
	const IRVector& m_inst;

	/// Constant
	Environment* m_const_env;

	/// Temporaries
	Environment* m_temp_env;

	/// Globals
	Environment* m_global_env;

	/// Stack frame
	CallStack m_call_stack;

	/// Call arguments
	std::vector<Value*> m_call_args;

	ThreadPool m_thread_pool;

	CMutex m_mutex;
	CMutex* f_mutex;

	std::stack<std::pair<size_t, size_t> > m_try_stack;

	CException m_exception;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
