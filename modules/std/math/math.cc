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

static CLEVER_FUNCTION(ceil) {
	switch (CLEVER_ARG_COUNT()) {
		case 1: {
			if (CLEVER_ARG_TYPE(0)==CLEVER_INT_TYPE) {
				//CLEVER_RETURN_INT(::std::ceil(CLEVER_ARG_INT(0)));
			} else if (CLEVER_ARG_TYPE(0)==CLEVER_DOUBLE_TYPE) {
				//CLEVER_RETURN_DBL(::std::ceil(CLEVER_ARG_DBL(0)));
			} else {
				Compiler::error("Math.ceil expected a double or integral value");
			}
		} break;
		
		default:
			Compiler::error("Math.ceil expected exactly one argument");
	}
}

static CLEVER_FUNCTION(floor) {
	switch (CLEVER_ARG_COUNT()) {
		case 1: {
			if (CLEVER_ARG_TYPE(0)==CLEVER_INT_TYPE) {
				//CLEVER_RETURN_INT(::std::floor(CLEVER_ARG_INT(0)));
			} else if (CLEVER_ARG_TYPE(0)==CLEVER_DOUBLE_TYPE) {
				//CLEVER_RETURN_DBL(::std::floor(CLEVER_ARG_DBL(0)));
			} else {
				Compiler::error("Math.floor expected a double or integral value");
			}
		} break;
		
		default:
			Compiler::error("Math.floor expected exactly one argument");
	}
}

static CLEVER_FUNCTION(abs) {
	switch (CLEVER_ARG_COUNT()) {
		case 1: {
			if (CLEVER_ARG_TYPE(0)==CLEVER_INT_TYPE) {
				//CLEVER_RETURN_INT(::std::labs(CLEVER_ARG_INT(0)));
			} else if (CLEVER_ARG_TYPE(0)==CLEVER_DOUBLE_TYPE) {
				//CLEVER_RETURN_DBL(::std::abs(CLEVER_ARG_DBL(0)));
			} else {
				Compiler::error("Math.floor expected a double or integral value");
			}
		} break;
		
		default:
			Compiler::error("Math.floor expected exactly one argument");
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
	addFunction(new Function("ceil", &CLEVER_FUNC_NAME(ceil)));
	addFunction(new Function("floor", &CLEVER_FUNC_NAME(floor)));
	addFunction(new Function("abs", &CLEVER_FUNC_NAME(abs)));
	END_DECLARE();
}

}}} // clever::packages::std
