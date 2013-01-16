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

static inline void* ThreadHandler(void* ThreadArgument){
	::std::cout << "Hello From ThreadHandler" << ::std::endl;
	
	return NULL;
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

		intern->thread = new pthread_t;
		intern->lock = new pthread_mutex_t;

		if (intern->lock) {
			pthread_mutex_init(intern->lock, NULL);
		}

		if (args->size()) {
			if (args->at(0)->getType() == CLEVER_FUNC_TYPE) {
				intern->entry = static_cast<Function*>(args->at(0)->getObj());
			} else {
				clever_error("Thread.new was expecting a Function");
			}
		}
	}
	return intern;
}

void Thread::deallocData(void* data)
{
	ThreadData* intern = static_cast<ThreadData*>(data);
	if (intern) {

		if (intern->lock) {
			pthread_mutex_destroy(intern->lock);
			delete intern->lock;
		}
		
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
		/** @TODO(krakjoe) pthread attributes **/
		result->setBool((pthread_create(intern->thread, NULL, ThreadHandler, intern) == 0));
	} else result->setBool(false);
}

CLEVER_TYPE_INIT(Thread::init)
{
	addMethod(new Function("start",    (MethodPtr)&Thread::start));
}

}}} // clever::packages::std
