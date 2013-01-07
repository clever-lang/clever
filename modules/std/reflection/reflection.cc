/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include "core/pkgmanager.h"
#include "core/vm.h"
#include "modules/std/reflection/reflection.h"
#include "modules/std/reflection/reflectionfunction.h"

namespace clever { namespace packages { namespace std {

namespace reflection {

// string get_type()
// Returns the type name of the supplied parameter
static CLEVER_FUNCTION(get_type) {
	if (CLEVER_ARG_COUNT()) {
		CLEVER_RETURN_CSTR(CLEVER_ARG_TYPE(0)->getName());
	}
	CLEVER_THROW("Missing parameter to get_type()");
}

} // clever::packages::std::reflection

CLEVER_MODULE_INIT(Reflection)
{
	BEGIN_DECLARE_TYPE()

	addType(CSTRING("ReflectionFunction"), new ReflectionFunction);

	END_DECLARE()

	BEGIN_DECLARE_FUNCTION()
	using namespace reflection;

	addFunction(new Function("get_type", &CLEVER_FUNC_NAME(get_type)));

	END_DECLARE()
}

}}} // clever::packages::std

