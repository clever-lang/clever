/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "core/modmanager.h"
#include "modules/std/concurrent/condition.h"
#include "modules/std/concurrent/module.h"
#include "modules/std/concurrent/mutex.h"
#include "modules/std/concurrent/thread.h"
#include "modules/std/concurrent/sync.h"

#ifndef CLEVER_THREADS_BEBUG
#undef clever_debug
#define clever_debug(...)
#endif

namespace clever { namespace modules { namespace std {

/// Initializes Standard Concurrency module
CLEVER_MODULE_INIT(ConcurrencyModule)
{
	addType(new Mutex);
	addType(new Condition);
	addType(new Thread);
	addType(new Sync);
}

}}} // clever::modules::std
