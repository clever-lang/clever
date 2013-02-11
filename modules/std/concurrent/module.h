/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_H
#define CLEVER_STD_CONCURRENT_H

#include "core/vm.h"
#include "core/module.h"

namespace clever { namespace modules { namespace std {

struct ThreadData : public TypeObject {
	pthread_t          	thread;
	pthread_mutex_t*    lock;
	Function*           entry;
	Value*              result;
	VM*           		vm;
	bool				joined;
};

/// Standard Concurrency Module
class ConcurrencyModule : public Module {
public:
	ConcurrencyModule()
		: Module("std.concurrent") { }

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(ConcurrencyModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_H
