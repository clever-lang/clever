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

namespace clever { namespace modules { namespace std {

/// Initializes Standard Concurrency module
CLEVER_MODULE_INIT(ConcurrencyModule)
{
	addType(CSTRING("Mutex"),     new Mutex);
	addType(CSTRING("Condition"), new Condition);
	addType(CSTRING("Thread"),    new Thread);
}

}}} // clever::modules::std
