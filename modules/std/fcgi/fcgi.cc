/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/request.h"
#include "modules/std/fcgi/response.h"

namespace clever { namespace packages { namespace std {

/// Initializes Standard FCGI module
CLEVER_MODULE_INIT(FCGIModule) {
	addType(CSTRING("Request"), new Request);
	addType(CSTRING("Response"), new Response);
}

}}} // clever::packages::std
