/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "modules/std/core/function.h"
#include "core/modmanager.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/server.h"

namespace clever { namespace modules { namespace std {

/// Initializes Standard FCGI module
CLEVER_MODULE_INIT(FCGIModule)
{
	addType(new Server);
}

}}} // clever::modules::std
