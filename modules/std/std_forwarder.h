/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "modules/std/core/core.h"

#ifdef HAVE_MOD_STD_CONCURRENT
#	include "modules/std/concurrent/module.h"
#endif
#ifdef HAVE_MOD_STD_SYS
#	include "modules/std/sys/sys.h"
#endif
#ifdef HAVE_MOD_STD_DATE
#	include "modules/std/date/module.h"
#endif
#ifdef HAVE_MOD_STD_IO
#	include "modules/std/io/io.h"
#endif
#ifdef HAVE_MOD_STD_FILE
#include "modules/std/file/file.h"
#endif
#ifdef HAVE_MOD_STD_REFLECTION
#	include "modules/std/reflection/reflection.h"
#endif
#ifdef HAVE_MOD_STD_MATH
#	include "modules/std/math/math.h"
#endif
#ifdef HAVE_MOD_STD_UNICODE
#	include "modules/std/unicode/unicode.h"
#endif
#ifdef HAVE_MOD_STD_NET
#include "modules/std/net/net.h"
#endif
#ifdef HAVE_MOD_STD_FCGI
#	include "modules/std/fcgi/fcgi.h"
#endif
#ifdef HAVE_MOD_STD_CRYPTO
#	include "modules/std/crypto/crypto.h"
#endif
#ifdef HAVE_MOD_STD_FFI
#	include "modules/std/ffi/ffi.h"
#endif
#ifdef HAVE_MOD_STD_CLEVER
#	include "modules/std/clever/module.h"
#endif
#ifdef HAVE_MOD_STD_JSON
# include "modules/std/json/json.h"
#endif
#ifdef HAVE_MOD_STD_REGEX
# include "modules/std/regex/regex.h"

#endif

#if 0
#ifdef HAVE_MOD_STD_RPC
# include "modules/std/rpc/rpc.h"
#endif
#endif
