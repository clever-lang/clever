/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/std/concurrent/module.h"
#include "modules/std/concurrent/thread.h"
#include "modules/std/core/function.h"

#ifndef CLEVER_THREADS_BEBUG
#undef clever_debug
#define clever_debug(...)
#endif

namespace clever { namespace modules { namespace std {

static inline void* ThreadHandler(void* ThreadArgument)
{
	ThreadData* intern = static_cast<ThreadData*>(ThreadArgument);

	if (intern->vm) {
		intern->result = intern->vm->runFunction(
			intern->entry, &intern->args
		);
		delete intern->vm;
	}

#ifndef CLEVER_WIN32
	pthread_exit(NULL);
#endif

	/*
	* MSVC will complain without it, also some posix implementations make gcc complain
	*/
	return intern;
}

TypeObject* Thread::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ThreadData* intern = new ThreadData;


	//clever_debug("Thread.new allocated lock for thread at %@", intern->lock);

	intern->entry = NULL;
	intern->vm = NULL;
	intern->joined = false;

	//if (intern->lock) {
		//if (pthread_mutex_init(intern->lock, NULL) != 0) {
			//clever_error("Thread.new failed to initialize a lock for the thread at %@", intern->lock);
		//} else clever_debug("Thread.new has initialized a lock for the thread at %@", intern->lock);
	//}

	if (args->size()) {
		Value* point = args->at(0);

		if (point->isFunction()) {
			intern->entry = static_cast<Function*>(point->getObj());
			//clever_debug("Thread.new has set entry point for thread to %@", intern->entry);
		} else {
			//clever_debug("Thread.new was expecting a Function and got something else at %@", point);
		}

		for (size_t i = 1; i < args->size(); ++i) {
			Value* v = args->at(i);
			intern->args.push_back(v->clone());
		}
	} else {
		clever_error("Thread.new was expecting a Function entry point and recieved no arguments");
	}

	return intern;
}

ThreadData::~ThreadData()
{
	//clever_debug("Thread.dtor executing %@ ...", thread);

	if (!joined) {
		//clever_debug("Thread.dtor calling pthread_join for %@", thread);
		this->thread.wait();
		//if (pthread_join(thread, NULL) != 0) {
			//clever_debug("Thread.dtor failed to join with %@", thread);
		//} else {
			//clever_debug("Thread.dtor joined with %@", thread);
		//}
	} else {
		//clever_debug("Thread.dtor skipping join for %@, previously joined", thread);
	}

	//if (lock) {
		//if (pthread_mutex_destroy(lock) != 0) {
			//clever_debug("Thread.dtor experienced an error destroying the lock for %@", thread);
		//} else {
			//clever_debug("Thread.dtor has destroyed the lock associated with %@", thread);
		//}
		//delete lock;
	//}

	for (size_t i = 0; i < this->args.size(); ++i) {
		delete this->args.at(i);
	}

	if (result) {
		delete result;
	}
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
		intern->lock.lock();

		//clever_debug("Thread.start set vm for thread to %@", vm);

		intern->vm = new VM();
		intern->vm->copy(vm, true);
		intern->vm->setChild();


		intern->thread.create(ThreadHandler, intern);

		//clever_debug("Thread.start created thread at %@", intern->thread);
		intern->lock.unlock();
	} else {
		//clever_debug("Thread.start lost it's entry point at %@", intern);
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

	intern->lock.lock();
	if (!intern->joined) {
		intern->thread.wait();
		intern->joined = true;
	}
	intern->lock.unlock();
}

// Thread.result()
// get function result

CLEVER_METHOD(Thread::getResult)
{
	ThreadData* intern = CLEVER_GET_OBJECT(ThreadData*, CLEVER_THIS());

	result->copy(intern->result);
}

// Thread.new(function entry)
// Constructs a new Thread object to execute the supplied function
CLEVER_METHOD(Thread::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Thread::init)
{
	setConstructor((MethodPtr) &Thread::ctor);

	addMethod(new Function("start",    (MethodPtr)&Thread::start));
	addMethod(new Function("wait",     (MethodPtr)&Thread::wait));
	addMethod(new Function("result",   (MethodPtr)&Thread::getResult));
}

}}} // clever::modules::std
