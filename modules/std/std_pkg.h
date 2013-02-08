/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_PACKAGE_H
#define CLEVER_STD_PACKAGE_H

#include "core/clever.h"
#include "modules/std/std_forwarder.h"
#include "core/module.h"

namespace clever { namespace modules {

class Std : public Module {
public:
	Std()
		: Module("std") {}

	~Std() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(Std);
};

}} // clever::modules

#endif // CLEVER_STD_PACKAGE_H
