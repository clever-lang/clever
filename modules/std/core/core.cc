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

// Native types
Type* const g_clever_int_type    = new IntType;
Type* const g_clever_double_type = new DoubleType;
Type* const g_clever_str_type    = new StrType;
Type* const g_clever_func_type   = new FuncType;
Type* const g_clever_thread_type = new ThreadType;
Type* const g_clever_bool_type   = new BoolType;
Type* const g_clever_array_type  = new ArrayType;
Type* const g_clever_map_type    = new MapType;

} // clever

namespace clever { namespace packages { namespace std {

CLEVER_MODULE_INIT(CoreModule)
{
	// Native type allocation
	addType(CSTRING("Function"), CLEVER_FUNC_TYPE);
	addType(CSTRING("String"),   CLEVER_STR_TYPE);
	addType(CSTRING("Int"),      CLEVER_INT_TYPE);
	addType(CSTRING("Double"),   CLEVER_DOUBLE_TYPE);
	addType(CSTRING("Bool"),     CLEVER_BOOL_TYPE);
	addType(CSTRING("Array"),    CLEVER_ARRAY_TYPE);
	addType(CSTRING("Map"),      CLEVER_MAP_TYPE);
	addType(CSTRING("Thread"),   CLEVER_THREAD_TYPE);
}

}}} // clever::packages::std
