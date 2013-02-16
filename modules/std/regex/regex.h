/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_REGEX_H
#define CLEVER_STD_REGEX_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

class Regex : public Module {
public:
	Regex()
		: Module("std.regex") {}

	~Regex() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(Regex);
};

}}} // clever::modules::std

#endif
