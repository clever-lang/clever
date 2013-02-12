/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_DATE_H
#define CLEVER_STD_DATE_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

/// Standard Date Module
class DateModule : public Module {
public:
	DateModule()
		: Module("std.date") { }

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(DateModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_DATE_H
