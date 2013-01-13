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
static CLEVER_FUNCTION(round)
{
	if (!clever_static_check_args("d")) {
		return;
	}
	double value = args[0]->getDouble();

#ifdef CLEVER_MSVC
	result->setDouble((value > 0.0) ? ::floor(value + 0.5) : ::ceil(value - 0.5));
#else
	result->setDouble(::round(value));
#endif
}

// number ceil(number value)
static CLEVER_FUNCTION(ceil)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->getType() == CLEVER_INT_TYPE) {
		result->setInt(::std::ceil(args[0]->getInt()));
	} else if (args[0]->getType() == CLEVER_DOUBLE_TYPE) {
		result->setDouble(::std::ceil(args[0]->getDouble()));
	}
}

// double floor(number value)
static CLEVER_FUNCTION(floor)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->getType() == CLEVER_INT_TYPE) {
		result->setInt(::std::floor(args[0]->getInt()));
	} else if (args[0]->getType() == CLEVER_DOUBLE_TYPE) {
		result->setDouble(::std::floor(args[0]->getDouble()));
	}
}

// number abs(number value)
static CLEVER_FUNCTION(abs)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->getType() == CLEVER_INT_TYPE) {
		result->setInt(::std::labs(args[0]->getInt()));
	} else if (args[0]->getType() == CLEVER_DOUBLE_TYPE) {
		result->setDouble(::std::abs(args[0]->getDouble()));
	}
}

} // clever::packages::std::math

// Load module data
CLEVER_MODULE_INIT(Math)
{
	using namespace math;

	addFunction(new Function("round", &CLEVER_FUNC_NAME(round)));
	addFunction(new Function("ceil",  &CLEVER_FUNC_NAME(ceil)));
	addFunction(new Function("floor", &CLEVER_FUNC_NAME(floor)));
	addFunction(new Function("abs",   &CLEVER_FUNC_NAME(abs)));
}

}}} // clever::packages::std
