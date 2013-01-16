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

	Thread* thread = (CLEVER_GET_OBJECT(Thread*, CLEVER_THIS()));

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

CLEVER_TYPE_INIT(ThreadType::init)
{
	// Methods
	addMethod(new Function("toString", (MethodPtr) &ThreadType::toString));
	addMethod(new Function("wait", (MethodPtr) &ThreadType::wait));
}

} // clever
