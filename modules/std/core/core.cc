/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/core/core.h"
#include "core/pkgmanager.h"
#include "core/value.h"
#include "types/native_types.h"
#include "types/type.h"

namespace clever {

// Declaration of namespace global type ptrs for Clever native types
DECLARE_CLEVER_NATIVE_TYPES();

} // clever

namespace clever { namespace packages { namespace std {

CLEVER_MODULE_INIT(CoreModule)
{
	// Native type allocation
	addType(CSTRING("Function"), CLEVER_FUNC_TYPE   = new FuncType);
	addType(CSTRING("String"),   CLEVER_STR_TYPE    = new StrType);
	addType(CSTRING("Int"),      CLEVER_INT_TYPE    = new IntType);
	addType(CSTRING("Double"),   CLEVER_DOUBLE_TYPE = new DoubleType);
	addType(CSTRING("Bool"),     CLEVER_BOOL_TYPE   = new BoolType);
	addType(CSTRING("Array"),    CLEVER_ARRAY_TYPE  = new ArrayType);
	addType(CSTRING("Map"),      CLEVER_MAP_TYPE    = new MapType);
	addType(CSTRING("Thread"),   CLEVER_THREAD_TYPE = new ThreadType);
}

}}} // clever::packages::std
