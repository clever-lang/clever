/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/core/core.h"
#include "core/modmanager.h"
#include "core/value.h"
#include "core/native_types.h"
#include "core/type.h"

namespace clever {

// Native types
Type* g_clever_int_type;
Type* g_clever_double_type;
Type* g_clever_str_type;
Type* g_clever_func_type;
Type* g_clever_bool_type;
Type* g_clever_array_type;
Type* g_clever_map_type;

} // clever

namespace clever { namespace modules { namespace std {

CLEVER_MODULE_INIT(CoreModule)
{
	// Native type allocation
	addType(CLEVER_FUNC_TYPE   = new FuncType);
	addType(CLEVER_STR_TYPE    = new StrType);
	addType(CLEVER_INT_TYPE    = new IntType);
	addType(CLEVER_DOUBLE_TYPE = new DoubleType);
	addType(CLEVER_BOOL_TYPE   = new BoolType);
	addType(CLEVER_ARRAY_TYPE  = new ArrayType);
	addType(CLEVER_MAP_TYPE    = new MapType);
}

}}} // clever::modules::std
