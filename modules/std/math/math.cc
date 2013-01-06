/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cmath>
#include <cstdlib>
#include <typeinfo>
#include "core/value.h"
#include "types/native_types.h"
#include "core/compiler.h"
#include "core/pkgmanager.h"
#include "modules/std/math/math.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

namespace clever { namespace packages { namespace std {

namespace math {

static CLEVER_FUNCTION(round) {
	switch (CLEVER_ARG_COUNT()) {
		case 1: {
			if (CLEVER_ARG_TYPE(0)==CLEVER_INT_TYPE) {
				//CLEVER_RETURN_INT(::std::round(CLEVER_ARG_INT(0)));
			} else if (CLEVER_ARG_TYPE(0)==CLEVER_DOUBLE_TYPE) {
				//CLEVER_RETURN_DBL(::std::round(CLEVER_ARG_DBL(0)));
			} else {
				Compiler::error("Math.round expected a double or integral value");
			}
		} break;
		
		default:
			Compiler::error("Math.round expected exactly one argument");
	}
}

} // math

/**
 * Load module data
 */
CLEVER_MODULE_INIT(Math) {
	using namespace math;
	
	BEGIN_DECLARE_FUNCTION();
	addFunction(new Function("round", &CLEVER_FUNC_NAME(round)));
	END_DECLARE();
}

}}} // clever::packages::std
