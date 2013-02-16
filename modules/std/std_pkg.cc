/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/std_pkg.h"

namespace clever { namespace modules {

// Initializes Std package
void Std::init()
{
	addModule(new std::CoreModule);
#ifdef HAVE_MOD_STD_CLEVER
	addModule(new std::CleverModule);
#endif
#ifdef HAVE_MOD_STD_CONCURRENT
	addModule(new std::ConcurrencyModule);
#endif
#ifdef HAVE_MOD_STD_DATE
	addModule(new std::DateModule);
#endif
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
#ifdef HAVE_MOD_STD_FCGI
	addModule(new std::FCGIModule);
#endif
#ifdef HAVE_MOD_STD_SYS
	addModule(new std::SYSModule);
#endif
#ifdef HAVE_MOD_STD_FILE
	addModule(new std::FileModule);
#endif
#ifdef HAVE_MOD_STD_NET
	addModule(new std::NetModule);
#endif
#ifdef HAVE_MOD_STD_CRYPTO
	addModule(new std::CryptoModule);
#endif

#ifdef HAVE_MOD_STD_FFI
	addModule(new std::FFIModule);
#endif

#ifdef HAVE_MOD_STD_REGEX
	addModule(new std::Regex);
#endif

#if 0
#ifdef HAVE_MOD_STD_RPC
	addModule(new std::RPCModule);
#endif
#endif
}

}} // clever::modules
