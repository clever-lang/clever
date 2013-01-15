/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/concurrent/module.h"
#include "modules/std/concurrent/mutex.h"

namespace clever { namespace packages { namespace std {

/// Initializes Standard Concurrency module
CLEVER_MODULE_INIT(ConcurrencyModule) {
	addType(CSTRING("Mutex"), new Mutex);
}

}}} // clever::packages::std
