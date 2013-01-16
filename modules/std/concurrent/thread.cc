/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/concurrent/module.h"
#include "modules/std/concurrent/thread.h"
#include "types/function.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

static inline void ThreadHandler(void* ThreadArgument){
	
}

void Thread::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void Thread::dump(const void* data, ::std::ostream& out) const
{
	Value::DataValue* dvalue =
		static_cast<Value::DataValue*>(const_cast<void*>(data));
	if (dvalue) {
		
	}
}

void* Thread::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ThreadData* intern = new ThreadData;
	if (intern) {	
		if (args->size()) {
			if (args->at(0)->getType() == CLEVER_FUNC_TYPE) {
				intern->entry = static_cast<Function*>(args->at(0)->getObj());
			}
		}
		intern->thread = new pthread_t;
	}
	return intern;
}

void Thread::deallocData(void* data)
{
	ThreadData* intern = static_cast<ThreadData*>(data);
	if (intern) {
		delete intern->thread;
		delete intern;
	}
}

CLEVER_METHOD(Thread::start)
{
	ThreadData* intern = CLEVER_GET_OBJECT(ThreadData*, CLEVER_THIS());
	
	if (!intern) {
		//CLEVER_THROW(eventually)
		return;
	}
	
	if (intern->entry) {
		::std::cout << "GOT ENTRY POINT" << ::std::endl;
	}
}

CLEVER_TYPE_INIT(Thread::init)
{
	addMethod(new Function("start",    (MethodPtr)&Thread::start));
}

}}} // clever::packages::std
