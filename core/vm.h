/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_VM_H
#define CLEVER_VM_H

#include <vector>
#include <stack>
#include <map>
#include "core/ir.h"
#include "core/cthread.h"
#include "core/codegen.h"

namespace clever {

// Helper macro for opcode handler declaration
#define VM_HANDLER_ARG IR& op
#define VM_HANDLER(name) CLEVER_FORCE_INLINE void VM::vm_##name(VM_HANDLER_ARG)
#define VM_HANDLER_D(name) void vm_##name(VM_HANDLER_ARG)

#define CLEVER_THROW(val) const_cast<VM*>(vm)->setException(val)

class Scope;
class Value;

typedef std::vector<std::pair<size_t, Value*> > FuncVars;

/// Stackframe representation
struct StackFrame {
	size_t ret_addr;     // Return address
	Value* ret_val;      // Return value
	Scope* arg_vars;     // Function arguments

	StackFrame()
		: ret_addr(0), ret_val(NULL), arg_vars(NULL) {}
};

class VM;

struct Thread {
	VM* vm_handler;
	CThread t_handler;
};

/// VM representation
class VM {
public:
	enum ErrorLevel {
		ERROR,
		WARNING
	};

	typedef std::vector<std::vector<Thread*> > ThreadPool;

	VM(IRVector& inst)
		: m_pc(0), m_is_main_thread(true), m_inst(inst), m_scope_pool(NULL),
		  m_const_pool(NULL), m_tmp_pool(NULL),
		  m_call_stack(), m_call_args(),
		  m_thread_pool(), m_mutex(), f_mutex(NULL), m_exception(NULL) {}
	~VM() {
		CLEVER_SAFE_DELETE(m_exception);
	}

	void error(ErrorLevel, const char*) const;

	/// Sets the symbol table to used by the VM to fetch the symbol names
	void setSymbolTable(ScopePool* scope) { m_scope_pool = scope; }

	void setConstantPool(ValuePool* consts) { m_const_pool = consts; }

	void setTemporaryPool(ValuePool* temps) { m_tmp_pool = temps; }

	void copy(const VM*);

	void setChild() { m_is_main_thread = false; }

	bool isChild() const { return !m_is_main_thread; }

	bool isMain() const { return m_is_main_thread; }

	size_t getPC() const { return m_pc; }

	void nextPC() { ++m_pc; }

	/// Exception handling methods
	void setException(Value*);
	void setException(const char*);

	IRVector& getInst() const { return m_inst; }

	/// Helper to retrive a Value* from TypePool
	const Type* getType(Operand&) const;

	/// Helper to retrive a Value* from ValuePool
	Value* getValue(size_t, size_t) const;
	Value* getValue(Operand&) const;

	Mutex* getMutex() {
		return isChild() ? f_mutex : &m_mutex;
	}
	/// Start the VM execution
	void run();

	/// Wait threads
	void wait();

	/// Methods for dumping opcodes
#ifdef CLEVER_DEBUG
	void dumpOperand(Operand&) const;
	void dumpOpcodes() const;
#endif
private:
	/// VM program counter
	size_t m_pc;

	bool m_is_main_thread;

	/// Vector of instruction
	IRVector& m_inst;

	/// Scope pool
	ScopePool* m_scope_pool;

	/// Constant pool
	ValuePool* m_const_pool;

	/// Temporaries pool
	ValuePool* m_tmp_pool;

	/// Stack frame
	std::stack<StackFrame> m_call_stack;

	/// Call arguments
	std::vector<Value*> m_call_args;

	ThreadPool m_thread_pool;

	Mutex m_mutex;
	Mutex* f_mutex;

	std::stack<size_t> m_try_stack;

	Value* m_exception;

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
