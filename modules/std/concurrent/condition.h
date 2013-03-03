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
#include "core/type.h"
#include "core/cthread.h"

namespace clever { namespace modules { namespace std {

struct ConditionObject : public TypeObject {
	ConditionObject()
		: condition() {}

	~ConditionObject() {}

	CCondition condition;
};

class Condition : public Type {
public:
	Condition()
		: Type("Condition") {}

	~Condition() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(signal);
	CLEVER_METHOD(broadcast);
	CLEVER_METHOD(wait);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_CONDITION_H
