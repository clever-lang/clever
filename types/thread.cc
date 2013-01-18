/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <sstream>
#include "core/value.h"
#include "core/vm.h"
#include "types/thread.h"
#include "modules/std/core/function.h"

namespace clever {

CLEVER_METHOD(ThreadType::toString)
{
	std::ostringstream str;

	const Thread* thread = CLEVER_GET_OBJECT(Thread*, CLEVER_THIS());

	str << thread->getID();

	result->setStr(CSTRING(str.str()));
}

CLEVER_METHOD(ThreadType::wait)
{
	Thread* thread = (CLEVER_GET_OBJECT(Thread*, CLEVER_THIS()));

	VM* m_vm = const_cast<VM*>(vm);
	VM::ThreadPool& m_thread_pool = m_vm->getThreadPool();
	std::vector<VMThread*>& thread_list = m_thread_pool.at(thread->getID());

	for (size_t i = 0, j = thread_list.size(); i < j; ++i) {
		delete_thread();

		VMThread* t = thread_list.at(i);
		t->t_handler.wait();
		clever_delete_var(t->vm_handler);
		clever_delete_var(t);
	}

	if (n_threads() == 0) {
		disenable_threads();
	}
	thread_list.clear();
}

CLEVER_METHOD(ThreadType::run)
{
	Thread* tdata = (CLEVER_GET_OBJECT(Thread*, CLEVER_THIS()));

	VM* m_vm = const_cast<VM*>(vm);
	VM::ThreadPool& m_thread_pool = m_vm->getThreadPool();

	m_vm->getMutex()->lock();

	if (m_thread_pool.size() <= tdata->getID()) {
		m_thread_pool.resize(tdata->getID() + 1);
	}

	size_t thread_addr = tdata->getAddr();
	size_t n_threads = tdata->getNThreads();

	for (size_t i = 0; i < n_threads; ++i) {
		VMThread* thread = new VMThread;
		new_thread();

		thread->vm_handler = new VM(m_vm->getInst());
		thread->vm_handler->copy(m_vm);
		thread->vm_handler->setChild();

		Environment* tenv = tdata->getEnvironment()->activate(m_vm->getCallStack().top());
		thread->vm_handler->getCallStack().push(tenv);

		if (m_thread_pool.size() <= tdata->getID()) {
			m_thread_pool.resize(tdata->getID() + 1);
		}
		m_thread_pool[tdata->getID()].push_back(thread);
		thread->vm_handler->setPC(thread_addr);
		thread->t_handler.create(_thread_control, static_cast<void*>(thread));
	}

	m_vm->getMutex()->unlock();
}

CLEVER_TYPE_INIT(ThreadType::init)
{
	// Methods
	addMethod(new Function("toString", (MethodPtr) &ThreadType::toString));
	addMethod(new Function("wait",     (MethodPtr) &ThreadType::wait));
	addMethod(new Function("run",      (MethodPtr) &ThreadType::run));
}

} // clever
