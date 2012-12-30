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

namespace clever { namespace packages {

class Std : public Package {
public:
	Std()
		: Package("std") { }

	~Std() { }

	void init();

	const char* getVersion() const { return NULL; }
private:
	DISALLOW_COPY_AND_ASSIGN(Std);
};

}} // clever::std_pkg

#endif // CLEVER_STD_PACKAGE_H
