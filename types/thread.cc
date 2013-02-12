/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <sstream>
#include "core/value.h"
#include "core/vm.h"
#include "core/cthread.h"
#include "types/thread.h"
#include "modules/std/core/function.h"

namespace clever {

CLEVER_THREAD_FUNC(_thread_control)
{
	VM* vm_handler = static_cast<VMThread*>(arg)->vm_handler;

	vm_handler->nextPC();
	vm_handler->run();

	return NULL;
}

// Thread.wait()
void Thread::wait()
{
	VMThreads& thread_list = getThreadPool();

	for (size_t i = 0, j = thread_list.size(); i < j; ++i) {
		VMThread* t = thread_list.at(i);
		if (t != 0) {
			t->t_handler.wait();
			clever_delete_var(t->vm_handler);
			clever_delete_var(t);
			t = 0;
		}
	}

	thread_list.clear();
}


// Thread.toString()
CLEVER_METHOD(ThreadType::toString)
{
	if (!clever_check_no_args()) {
		return;
	}

	std::ostringstream str;

	//const Thread* thread = CLEVER_GET_OBJECT(Thread*, CLEVER_THIS());

	//str << thread->getID();

	result->setStr(CSTRING(str.str()));
}

// Thread.wait()
CLEVER_METHOD(ThreadType::wait)
{
	if (!clever_check_no_args()) {
		return;
	}

	CLEVER_GET_OBJECT(Thread*, CLEVER_THIS())->wait();
}

// Thread.run()
CLEVER_METHOD(ThreadType::run)
{
	Thread* tdata = CLEVER_GET_OBJECT(Thread*, CLEVER_THIS());

	VM* m_vm = const_cast<VM*>(vm);

	m_vm->getMutex()->lock();

	VMThreads& m_thread_pool = tdata->getThreadPool();


	size_t thread_addr = tdata->getAddr();
	size_t n_threads = tdata->getNThreads();
	size_t bg = m_thread_pool.size();
	size_t size =  bg + n_threads;

	m_thread_pool.resize(size);
	for (size_t i = bg; i < size; ++i) {

		VMThread* thread = new VMThread;

		thread->vm_handler = new VM(m_vm->getInst());
		thread->vm_handler->copy(m_vm, true);
		thread->vm_handler->setChild();

		Environment* tenv = tdata->getEnvironment()->activate(m_vm->getCallStack().top());
		thread->vm_handler->getCallStack().push(tenv);

		m_thread_pool[i] = thread;

		thread->vm_handler->setPC(thread_addr);
		thread->t_handler.create(_thread_control, static_cast<void*>(thread));
	}
	m_vm->getMutex()->unlock();
}

// Thread type initialization
CLEVER_TYPE_INIT(ThreadType::init)
{
	// Methods
	addMethod(new Function("toString", (MethodPtr) &ThreadType::toString));
	addMethod(new Function("wait",     (MethodPtr) &ThreadType::wait));
	addMethod(new Function("run",      (MethodPtr) &ThreadType::run));
}

} // clever
