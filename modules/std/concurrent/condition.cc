/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "types/function.h"
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/concurrent/condition.h"

namespace clever { namespace packages { namespace std {

void Condition::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void Condition::dump(const void* data, ::std::ostream& out) const
{
	Value::DataValue* dvalue = static_cast<Value::DataValue*>(const_cast<void*>(data));
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

void Condition::deallocData(void *data)
{
	pthread_cond_t* condition = static_cast<pthread_cond_t*>(data);
	if (condition) {
		pthread_cond_destroy(condition);
		delete condition;
	}
}

CLEVER_METHOD(Condition::signal)
{
	pthread_cond_t* condition = CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());

	if (!condition) {
		//CLEVER_THROW(eventually)
		return;
	}
	
	result->setBool((pthread_cond_signal(condition)==0));
}

CLEVER_METHOD(Condition::broadcast)
{
	pthread_cond_t* condition = CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());
	
	if (!condition) {
		//CLEVER_THROW(eventually)
		return;
	}

	result->setBool((pthread_cond_broadcast(condition)==0));
}

CLEVER_METHOD(Condition::wait)
{
	pthread_cond_t* condition = CLEVER_GET_OBJECT(pthread_cond_t*, CLEVER_THIS());

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
	
	result->setBool((pthread_cond_wait(condition, mutex)==0));
}

CLEVER_TYPE_INIT(Condition::init)
{
	addMethod(new Function("signal",		(MethodPtr) &Condition::signal));
	addMethod(new Function("broadcast",		(MethodPtr) &Condition::broadcast));
	addMethod(new Function("wait",			(MethodPtr) &Condition::wait));
}

}}} // clever::packages::std
