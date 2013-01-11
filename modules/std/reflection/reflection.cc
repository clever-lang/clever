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

namespace reflection {

// string get_type()
// Returns the type name of the supplied parameter
static CLEVER_FUNCTION(get_type) {
	if (CLEVER_ARG_COUNT()) {
		CLEVER_RETURN_STR(CLEVER_ARG_TYPE(0)->getName());
	}
	// TODO(Felipe): fix build when throwing exception
	//CLEVER_THROW("Missing parameter to get_type()");
}

} // clever::packages::std::reflection

CLEVER_MODULE_INIT(Reflection)
{
	using namespace reflection;

	// Types
	addType(CSTRING("ReflectionFunction"), new ReflectionFunction);

	// Functions
	addFunction(new Function("get_type", &CLEVER_FUNC_NAME(get_type)));
}

}}} // clever::packages::std

