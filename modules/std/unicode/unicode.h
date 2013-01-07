/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_UNICODE_H
#define CLEVER_STD_UNICODE_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard Unicode Module
class UnicodeModule : public Module {
public:
	UnicodeModule()
		: Module("unicode") { }

	~UnicodeModule() { }
		
	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(UnicodeModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_UNICODE_H
