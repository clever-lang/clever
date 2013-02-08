/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_REFLECTION_H
#define CLEVER_STD_REFLECTION_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard Reflection Module
class Reflection : public Module {
public:
	Reflection()
		: Module("std.reflection") {}

	~Reflection() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(Reflection);
};

}}} // clever::packages::std

#endif // CLEVER_STD_IO_H
