/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cmath>
#include <cstdlib>
#include "core/value.h"
#include "types/native_types.h"
#include "core/pkgmanager.h"
#include "modules/std/math/math.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

namespace clever { namespace packages { namespace std {

namespace math {

// double round(double value)
static CLEVER_FUNCTION(round) {
	if (!check_args(args, "d")) {
		return;
	}
	double value = CLEVER_ARG_DBL(0);

#ifdef CLEVER_MSVC
	CLEVER_RETURN_DBL((value > 0.0) ? ::floor(value + 0.5) : ::ceil(value - 0.5));
#else
	CLEVER_RETURN_DBL(::round(value));
#endif
}

// number ceil(number value)
static CLEVER_FUNCTION(ceil) {
	if (!check_args(args, "n")) {
		return;
	}

	if (CLEVER_ARG_TYPE(0) == CLEVER_INT_TYPE) {
		CLEVER_RETURN_INT(::std::ceil(CLEVER_ARG_INT(0)));
	} else if (CLEVER_ARG_TYPE(0) == CLEVER_DOUBLE_TYPE) {
		CLEVER_RETURN_DBL(::std::ceil(CLEVER_ARG_DBL(0)));
	}
}

// double floor(number value)
static CLEVER_FUNCTION(floor) {
	if (!check_args(args, "n")) {
		return;
	}

	if (CLEVER_ARG_TYPE(0) == CLEVER_INT_TYPE) {
		CLEVER_RETURN_INT(::std::floor(CLEVER_ARG_INT(0)));
	} else if (CLEVER_ARG_TYPE(0) == CLEVER_DOUBLE_TYPE) {
		CLEVER_RETURN_DBL(::std::floor(CLEVER_ARG_DBL(0)));
	}
}

// number abs(number value)
static CLEVER_FUNCTION(abs) {
	if (!check_args(args, "n")) {
		return;
	}

	if (CLEVER_ARG_TYPE(0) == CLEVER_INT_TYPE) {
		CLEVER_RETURN_INT(::std::labs(CLEVER_ARG_INT(0)));
	} else if (CLEVER_ARG_TYPE(0) == CLEVER_DOUBLE_TYPE) {
		CLEVER_RETURN_DBL(::std::abs(CLEVER_ARG_DBL(0)));
	}
}

} // clever::packages::std::math

/**
 * Load module data
 */
CLEVER_MODULE_INIT(Math) {
	using namespace math;

	addFunction(new Function("round", &CLEVER_FUNC_NAME(round)));
	addFunction(new Function("ceil",  &CLEVER_FUNC_NAME(ceil)));
	addFunction(new Function("floor", &CLEVER_FUNC_NAME(floor)));
	addFunction(new Function("abs",   &CLEVER_FUNC_NAME(abs)));
}

}}} // clever::packages::std
