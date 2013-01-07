/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_UNICODE_H
#define CLEVER_STD_UNICODE_H

#include "core/module.h"
#include "unicode/uclean.h"

namespace clever { namespace packages { namespace std {

/// Standard Unicode Module
class UnicodeModule : public Module {
public:
	UnicodeModule()
		: Module("unicode") { u_init(&errorCode); }

	~UnicodeModule() {
		u_cleanup();
	}
		
	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(UnicodeModule);
	
	UErrorCode errorCode;
};

}}} // clever::packages::std

#endif // CLEVER_STD_UNICODE_H
