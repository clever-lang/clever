/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CRYPTO_H
#define CLEVER_CRYPTO_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

class CryptoModule : public Module {
public:
	CryptoModule()
		: Module("std.crypto") {}

	~CryptoModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(CryptoModule);
};

}}} // clever::modules::std

#endif // CLEVER_CRYPTO_H
