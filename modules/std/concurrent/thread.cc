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
#include "modules/std/core/function.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

static inline void* ThreadHandler(void* ThreadArgument)
{
	ThreadData* intern = static_cast<ThreadData*>(ThreadArgument);

	if (intern->vm) {
		::std::vector<Value*> args;

		Value* result = (const_cast<VM*>(intern->vm))->runFunction(
			intern->entry, &args
		);

		result->delRef();
	}

	return intern;
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
	
	intern->thread = new pthread_t;
	intern->lock = new pthread_mutex_t;
	intern->entry = NULL;
	intern->vm = NULL;
	intern->joined = false;
	
	if (intern->lock) {
		if (pthread_mutex_init(intern->lock, NULL) != 0) {
			clever_error("Thread.new failed to initialize a lock for the Thread");
		}
	}

	if (args->size()) {
		Value* point = args->at(0);

		if (point->getType() == CLEVER_FUNC_TYPE) {
			intern->entry = static_cast<Function*>(point->getObj());
		} else {
			clever_debug("Thread.new was expecting a Function and got something else at %@", point);
		}
	} else {
		clever_error("Thread.new was expecting a Function entry point and recieved no arguments");
	}

	return intern;
}

void Thread::deallocData(void* data)
{
	ThreadData* intern = static_cast<ThreadData*>(data);

	if (!intern) {
		return;
	}

	if (intern->lock) {
		if (pthread_mutex_destroy(intern->lock) != 0) {
			clever_error("Thread.delete experienced an error destroying the Thread's lock");
		}
		delete intern->lock;
	}


	delete intern->thread;
	delete intern;
}

// Bool Thread.start()
// Starts executing the Thread object
CLEVER_METHOD(Thread::start)
{
	ThreadData* intern = CLEVER_GET_OBJECT(ThreadData*, CLEVER_THIS());

	if (!intern) {
		//CLEVER_THROW(eventually)
		return;
	}

	if (intern->entry != NULL) {
		/** @TODO(krakjoe) pthread attributes **/
		if (pthread_mutex_lock(intern->lock) == 0) {
			intern->vm = vm;
			result->setBool(
				(pthread_create(intern->thread, NULL, ThreadHandler, intern) == 0)
			);
			pthread_mutex_unlock(intern->lock);
		} else {
			/* report fatality */
			result->setBool(false);
		}
	} else {
		result->setBool(false);
	}
}

// void Thread.wait()
// Waits for this thread to finish executing
CLEVER_METHOD(Thread::wait)
{
	ThreadData* intern = CLEVER_GET_OBJECT(ThreadData*, CLEVER_THIS());
	
	if (!intern) {
		//CLEVER_THROW(eventually);
		return;
	}
	
	if (pthread_mutex_lock(intern->lock) == 0) {
		if (!intern->joined) {
			result->setBool(
				(pthread_join(*intern->thread, NULL) == 0)
			);
			intern->joined = true;
		} else {
			result->setNull();
		}
		pthread_mutex_unlock(intern->lock);
	} else {
		//CLEVER_THROW(eventually);
		result->setNull();
	}
}

// Thread.new(function entry)
// Constructs a new Thread object to execute the supplied function
CLEVER_METHOD(Thread::ctor)
{
	result->setType(this);
	result->setObj(allocData(&args));
}

CLEVER_TYPE_INIT(Thread::init)
{
	Function* ctor = new Function("Thread", (MethodPtr) &Thread::ctor);

	setConstructor(ctor);

	addMethod(ctor);

	addMethod(new Function("start",    (MethodPtr)&Thread::start));
	addMethod(new Function("wait",		(MethodPtr)&Thread::wait));
}

}}} // clever::packages::std
