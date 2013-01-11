/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_H
#define CLEVER_STD_FCGI_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard FCGI Module
class FCGIModule : public Module {
public:
	FCGIModule()
		: Module("fcgi") { }

	~FCGIModule() {
	}
		
	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(FCGIModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_H
