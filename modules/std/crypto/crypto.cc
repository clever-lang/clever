/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/crypto/crypto.h"
#include "modules/std/crypto/md5.h"
#include "modules/std/crypto/base64.h"

namespace clever { namespace modules { namespace std {

namespace crypto {

// md5(string)
// Returns the MD5 hashing for the supplied string
static CLEVER_FUNCTION(md5)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	result->setStr(new StrObject(md5(*args[0]->getStr())));
}

static CLEVER_FUNCTION(base64_encode)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	result->setStr(new StrObject(base64Encode(*args[0]->getStr())));
}

static CLEVER_FUNCTION(base64_decode)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	result->setStr(new StrObject(base64Decode(*args[0]->getStr())));
}

} // clever::modules::std::crypto

CLEVER_MODULE_INIT(CryptoModule)
{
	addFunction(new Function("md5",           &CLEVER_NS_FNAME(crypto, md5)));
	addFunction(new Function("base64_encode", &CLEVER_NS_FNAME(crypto, base64_encode)));
	addFunction(new Function("base64_decode", &CLEVER_NS_FNAME(crypto, base64_decode)));
}

}}} // clever::modules::std
