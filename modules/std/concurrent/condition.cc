/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/concurrent/condition.h"
#include "modules/std/core/function.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

void Condition::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void Condition::dump(const void* data, ::std::ostream& out) const
{
	ValueObject* dvalue =
		static_cast<ValueObject*>(const_cast<void*>(data));

	if (dvalue) {
	}
}

void* Condition::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	pthread_cond_t* condition = new pthread_cond_t;
	if (condition) {
		// @TODO(krakjoe) condition attributes
		pthread_cond_init(condition, NULL);
	}
	return condition;
}

void Condition::deallocData(void* data)
{
	pthread_cond_t* condition = static_cast<pthread_cond_t*>(data);
	if (condition) {
		pthread_cond_destroy(condition);
		delete condition;
	}
}

// bool Condition.signal()
// Will signal to one thread waiting on this Condition
CLEVER_METHOD(Condition::signal)
{
	pthread_cond_t* condition =
		CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());

	if (!condition) {
		//CLEVER_THROW(eventually)
		return;
	}

	result->setBool((pthread_cond_signal(condition) == 0));
}

// bool Condition.broadcast()
// Will broadcast to every thread waiting on this Condition
CLEVER_METHOD(Condition::broadcast)
{
	pthread_cond_t* condition =
		CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());

	if (!condition) {
		//CLEVER_THROW(eventually)
		return;
	}

	result->setBool((pthread_cond_broadcast(condition) == 0));
}

// bool Condition.wait(Mutex locked)
// Will wait for another thread to signal or broadcast to this condition
// You should have the Mutex locked at time of the call
// When the call to Condition.wait returns the Mutex owner has not changed
CLEVER_METHOD(Condition::wait)
{
	pthread_cond_t* condition =
		CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());

	if (!condition) {
		//CLEVER_THROW(eventually)
		return;
	}

	if (!clever_check_args("*")) {
		return;
	}

	pthread_mutex_t* mutex = static_cast<pthread_mutex_t*>(args[0]->getObj());

	if (!mutex) {
		//CLEVER_THROW(eventually);
		return;
	}

	result->setBool((pthread_cond_wait(condition, mutex) == 0));
}

CLEVER_METHOD(Condition::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Condition::init)
{
	Function* ctor = new Function("Condition", (MethodPtr) &Condition::ctor);

	setConstructor(ctor);

	addMethod(ctor);

	addMethod(new Function("signal",    (MethodPtr)&Condition::signal));
	addMethod(new Function("broadcast", (MethodPtr)&Condition::broadcast));
	addMethod(new Function("wait",		(MethodPtr)&Condition::wait));
}

}}} // clever::packages::std
