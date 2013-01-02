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
#include "core/cthread.h"
#include "core/clever.h"
#include "core/compiler.h"
#include "core/ir.h"
#include "core/opcode.h"

namespace clever {

#define OPCODE m_inst[m_pc]
#define VM_EXIT() goto exit

#if CLEVER_GCC_VERSION > 0
# define OP(name)    name
# define OPCODES    const static void* labels[] = { OP_LABELS };\
	if (m_inst.size())\
		goto *labels[m_inst[m_pc].opcode];\
	else return;
# define DISPATCH    ++m_pc; goto *labels[m_inst[m_pc].opcode]
# define END_OPCODES
# define VM_GOTO(n)  m_pc = n; goto *labels[m_inst[m_pc].opcode]
#else
# define OP(name)    case name
# define OPCODES     while (m_inst.size()) { switch (m_inst[m_pc].opcode) {
# define DISPATCH    ++m_pc; break
# define END_OPCODES EMPTY_SWITCH_DEFAULT_CASE(); } }
# define VM_GOTO(n)  m_pc = n; break
#endif

// Helper macros to be used to change the VM program counter
#define VM_NEXT() ++m_pc


// Helper macro for opcode handler declaration
#define VM_HANDLER_ARG IR& op
#define VM_HANDLER(name) CLEVER_FORCE_INLINE void VM::vm_##name(VM_HANDLER_ARG)
#define VM_HANDLER_D(name) void vm_##name(VM_HANDLER_ARG)

class Scope;
class Value;

typedef std::vector<std::pair<size_t, Value*> > FuncVars;

/// Stackframe representation
struct StackFrame {
	size_t ret_addr;     // Return address
	Value* ret_val;      // Return value
	Scope* arg_vars;     // Function arguments
	Scope* local_vars;   // Local variables
	FuncVars vars;       // Arg and local vars storage

	StackFrame()
		: ret_addr(0), ret_val(NULL), arg_vars(NULL), local_vars(NULL), vars() {}
};

class VM;

struct Thread {
	VM* vm_handler;
	pthread_t t_handler;
	pthread_mutex_t m_handler;
};

/// VM representation
class VM {
public:
	enum ErrorLevel {
		ERROR,
		WARNING
	};

	typedef void (VM::*OpHandler)(VM_HANDLER_ARG);

	typedef std::vector<Thread*> ThreadPool;

	VM(IRVector& inst)
		: m_pc(0), m_is_main_thread(true), m_inst(inst), m_scope_pool(NULL),
		  m_const_pool(NULL), m_tmp_pool(NULL), m_mutex(), f_mutex(NULL) {}
	~VM() {}

	void error(ErrorLevel, const char*) const;

	/// Sets the symbol table to used by the VM to fetch the symbol names
	void setSymbolTable(ScopePool* scope) { m_scope_pool = scope; }

	void setConstantPool(ValuePool* consts) { m_const_pool = consts; }

	void setTemporaryPool(ValuePool* temps) { m_tmp_pool = temps; }

	void copy(VM*);

	void setChild() { m_is_main_thread = false; }

	bool isChild() const { return !m_is_main_thread; }

	bool isMain() const { return !m_is_main_thread; }

	size_t getPC() const { return m_pc; }

	void nextPC() { ++m_pc; }

	IRVector& getInst() const { return m_inst; }

	/// Helper to retrive a Value* from ValuePool
	Value* getValue(size_t, size_t) const;
	Value* getValue(Operand&) const;

	/// Save function variables on recursion
	void saveVars();
	void restoreVars() const;

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

	void increment(IR&);
	void decrement(IR&);
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

	/// VM opcode handlers
	OpHandler m_handlers[NUM_OPCODES];

	/// Stack frame
	std::stack<StackFrame> m_call_stack;

	/// Call arguments
	std::vector<Value*> m_call_args;

	ThreadPool m_thread_pool;

	Mutex m_mutex;
	Mutex* f_mutex;

//	void* m_labels[NUM_OPCODES];

	DISALLOW_COPY_AND_ASSIGN(VM);
};

} // clever

#endif // CLEVER_VM_H
