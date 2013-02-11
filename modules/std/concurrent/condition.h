/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_CONDITION_H
#define CLEVER_STD_CONCURRENT_CONDITION_H

#include <iostream>

#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace modules { namespace std {

struct ConditionObject : public TypeObject {
	ConditionObject()
		: condition(new pthread_cond_t) {}

	~ConditionObject() {
		delete condition;
	}

	pthread_cond_t* condition;
};

class Condition : public Type {
public:
	Condition()
		: Type(CSTRING("Condition")) {}

	~Condition() {}

	void dump(TypeObject* data) const;
	void dump(TypeObject* data, ::std::ostream& out) const;

	virtual void increment(Value*, const VM*, CException*) const {}
	virtual void decrement(Value*, const VM*, CException*) const {}

	void init();

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);

	CLEVER_METHOD(signal);
	CLEVER_METHOD(broadcast);
	CLEVER_METHOD(wait);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_CONDITION_H
