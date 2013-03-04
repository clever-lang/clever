/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "core/value.h"
#include "core/native_types.h"
#include "core/modmanager.h"
#include "modules/std/math/math.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

namespace clever { namespace modules { namespace std {

namespace math {

// round(double)
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

// ceil(number)
static CLEVER_FUNCTION(ceil)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::ceil(args[0]->getInt()));
	} else {
		result->setDouble(::std::ceil(args[0]->getDouble()));
	}
}

// sqrt(number)
static CLEVER_FUNCTION(sqrt)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::sqrt(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::sqrt(args[0]->getDouble()));
	}
}

// floor(number)
static CLEVER_FUNCTION(floor)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::floor(args[0]->getInt()));
	} else if (args[0]->isDouble()) {
		result->setDouble(::std::floor(args[0]->getDouble()));
	}
}

// abs(number)
static CLEVER_FUNCTION(abs)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::labs(args[0]->getInt()));
	} else {
		result->setDouble(::std::abs(args[0]->getDouble()));
	}
}

// cos(number)
static CLEVER_FUNCTION(cos)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::cos(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::cos(args[0]->getDouble()));
	}
}

// acos(number)
static CLEVER_FUNCTION(acos)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::acos(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::acos(args[0]->getDouble()));
	}
}

// cosh(number)
static CLEVER_FUNCTION(cosh)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::cosh(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::cosh(args[0]->getDouble()));
	}
}

// sin(number)
static CLEVER_FUNCTION(sin)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::sin(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::sin(args[0]->getDouble()));
	}
}

// asin(number)
static CLEVER_FUNCTION(asin)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::asin(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::asin(args[0]->getDouble()));
	}
}

// sinh(number)
static CLEVER_FUNCTION(sinh)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::sinh(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::sinh(args[0]->getDouble()));
	}
}

// tan(number)
static CLEVER_FUNCTION(tan)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::tan(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::tan(args[0]->getDouble()));
	}
}

// tanh(number)
static CLEVER_FUNCTION(tanh)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::tanh(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::tanh(args[0]->getDouble()));
	}
}

// atan(number [, number])
static CLEVER_FUNCTION(atan)
{
	if (!clever_static_check_args("n|n")) {
		return;
	}

	if (args.size() == 1) {
		if (args[0]->isInt()) {
			result->setInt(::std::atan(double(args[0]->getInt())));
		} else {
			result->setDouble(::std::atan(args[0]->getDouble()));
		}
	} else {
		double y = args[0]->isInt() ? double(args[0]->getInt()) : args[0]->getDouble();
		double x = args[1]->isInt() ? double(args[1]->getInt()) : args[1]->getDouble();

		if (args[0]->isInt()) {
			result->setInt(::std::atan2(y, x));
		} else {
			result->setDouble(::std::atan2(y, x));
		}
	}
}

// log(number)
static CLEVER_FUNCTION(log)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::log(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::log(args[0]->getDouble()));
	}
}

// exp(number)
static CLEVER_FUNCTION(exp)
{
	if (!clever_static_check_args("n")) {
		return;
	}

	if (args[0]->isInt()) {
		result->setInt(::std::exp(double(args[0]->getInt())));
	} else {
		result->setDouble(::std::exp(args[0]->getDouble()));
	}
}

// rand()
// generate a random number betwen 0 and 1
static CLEVER_FUNCTION(rand)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setDouble(static_cast<double>(::std::rand()) / RAND_MAX);
}

} // clever::modules::std::math

// Load module data
CLEVER_MODULE_INIT(Math)
{
	::std::srand(::std::time(NULL));

	addFunction(new Function("round", &CLEVER_NS_FNAME(math, round)));
	addFunction(new Function("ceil",  &CLEVER_NS_FNAME(math, ceil)));
	addFunction(new Function("sqrt",  &CLEVER_NS_FNAME(math, sqrt)));
	addFunction(new Function("floor", &CLEVER_NS_FNAME(math, floor)));
	addFunction(new Function("exp",   &CLEVER_NS_FNAME(math, exp)));
	addFunction(new Function("abs",   &CLEVER_NS_FNAME(math, abs)));
	addFunction(new Function("cos",   &CLEVER_NS_FNAME(math, cos)));
	addFunction(new Function("acos",  &CLEVER_NS_FNAME(math, acos)));
	addFunction(new Function("cosh",  &CLEVER_NS_FNAME(math, cosh)));
	addFunction(new Function("sin",   &CLEVER_NS_FNAME(math, sin)));
	addFunction(new Function("sinh",  &CLEVER_NS_FNAME(math, sinh)));
	addFunction(new Function("asin",  &CLEVER_NS_FNAME(math, asin)));
	addFunction(new Function("tan",   &CLEVER_NS_FNAME(math, tan)));
	addFunction(new Function("tanh",  &CLEVER_NS_FNAME(math, tanh)));
	addFunction(new Function("atan",  &CLEVER_NS_FNAME(math, atan)));
	addFunction(new Function("log",   &CLEVER_NS_FNAME(math, log)));
	addFunction(new Function("rand",  &CLEVER_NS_FNAME(math, rand)));

	addVariable("PI",       new Value(M_PI, true));
}

}}} // clever::modules::std
