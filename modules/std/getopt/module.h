/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_GETOPT_H
#define CLEVER_STD_GETOPT_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

class GetoptModule : public Module {
public:
	GetoptModule()
		: Module("std.getopt") {}

	~GetoptModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(GetoptModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_GETOPT_H
