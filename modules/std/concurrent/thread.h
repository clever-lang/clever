/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_THREAD_H
#define CLEVER_STD_CONCURRENT_THREAD_H

#include <iostream>

#include "core/cstring.h"
#include "core/type.h"
#include "core/cthread.h"

namespace clever { namespace modules { namespace std {

struct ThreadData : public TypeObject {
	ThreadData()
		: entry(NULL), result(NULL), vm(NULL) {}

	~ThreadData();

	CThread thread;
	CMutex lock;
	const Function* entry;
	Value* result;
	VM* vm;
	::std::vector<Value*> args;
	bool joined;
};

class Thread : public Type {
public:
	Thread()
		: Type("Thread") {}

	~Thread() {}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(start);
	CLEVER_METHOD(wait);
	CLEVER_METHOD(getResult);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_THREAD_H
