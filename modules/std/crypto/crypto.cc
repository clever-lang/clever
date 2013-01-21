/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/crypto/crypto.h"
#include "modules/std/crypto/md5.h"

namespace clever { namespace packages { namespace std {

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

} // clever::packages::std::crypto

CLEVER_MODULE_INIT(CryptoModule)
{
	addFunction(new Function("md5", &CLEVER_NS_FNAME(crypto, md5)));
}

}}} // clever::packages::std
