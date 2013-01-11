/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_SYS_H
#define CLEVER_STD_SYS_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard SYS module
class SYSModule : public Module {
public:
	SYSModule()
		: Module("sys") { }

	~SYSModule() { }

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(SYSModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_SYS_H
