/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_H
#define CLEVER_STD_CONCURRENT_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard Concurrency Module
class ConcurrencyModule : public Module {
public:
	ConcurrencyModule()
		: Module("concurrent") { }
		
	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(ConcurrencyModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_CONCURRENT_H
