/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_IO_H
#define CLEVER_STD_IO_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard IO Module
class IOModule : public Module {
public:
	IOModule()
		: Module("std.io") {}

	~IOModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(IOModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_IO_H
