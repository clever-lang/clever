/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/pkgmanager.h"
#include "modules/std/reflection/reflection.h"
#include "modules/std/reflection/reflectionfunction.h"

namespace clever { namespace packages { namespace std {

CLEVER_MODULE_INIT(Reflection)
{
	BEGIN_DECLARE_TYPE()

	addType(CSTRING("ReflectionFunction"), new ReflectionFunction);

	END_DECLARE()
}

}}} // clever::packages::std

