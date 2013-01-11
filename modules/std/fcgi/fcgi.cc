/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/request.h"

namespace clever { namespace packages { namespace std {

namespace fcgi {

} // clever::packages::std::fcgi

/// Initializes Standard FCGI module
CLEVER_MODULE_INIT(FCGIModule) {
	using namespace fcgi;
	
	addType(CSTRING("Request"), new Request);
}

}}} // clever::packages::std
