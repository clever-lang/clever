/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/std_pkg.h"

namespace clever { namespace packages {

// Initializes Std package
void Std::init() {
#ifdef HAVE_MOD_STD_IO
	addModule(new std::IOModule);
#endif
#ifdef HAVE_MOD_STD_REFLECTION
	addModule(new std::Reflection);
#endif
#ifdef HAVE_MOD_STD_MATH
	addModule(new std::Math);
#endif
#ifdef HAVE_MOD_STD_UNICODE
	addModule(new std::UnicodeModule);
#endif
#ifdef HAVE_MOD_STD_SYS
	addModule(new std::SYSModule);
#endif
#ifdef HAVE_MOD_STD_FILE
	addModule(new std::FileModule);
#endif
/*
#ifdef HAVE_MOD_STD_NET
	addModule(new std::NetModule);
#endif
#ifdef HAVE_MOD_STD_REGEX
	addModule(new std::Regex);
#endif
#ifdef HAVE_MOD_STD_FFI
	addModule(new std::FFI);
#endif
#ifdef HAVE_MOD_STD_RPC
	addModule(new std::RPCModule);
#endif
*/
}

}} // clever::packages
