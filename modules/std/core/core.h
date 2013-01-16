/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CORE_H
#define CLEVER_STD_CORE_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard Core Module
class CoreModule : public Module {
public:
	CoreModule()
		: Module("core") {}

	~CoreModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(CoreModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_CORE_H
