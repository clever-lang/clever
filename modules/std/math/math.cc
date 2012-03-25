/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#include <cmath>
#include <cstdlib>
#include "modules/std/math/math.h"
#include "types/nativetypes.h"
#include "compiler/pkgmanager.h"

#ifndef M_PI
#define M_PI    3.14159265358979323846
#endif

namespace clever { namespace packages { namespace std {

namespace math {

/**
 * abs(double x)
 * Returns the absolute value of a number x
 */
static CLEVER_FUNCTION(abs_double) {
	/* FIXME: Remove this if when we got overload support for functions */
	if (CLEVER_ARG_TYPE_P(0) == CLEVER_INT) {
		retval->setInteger(::std::labs(CLEVER_ARG_INT(0)));
	} else {
		CLEVER_RETURN_DOUBLE(::std::abs(CLEVER_ARG_DOUBLE(0)));
	}
}

/**
 * abs(int x)
 * Returns the absolute value of a number x
 */
 /*
static CLEVER_FUNCTION(abs_int) {
	retval->setInteger(::std::labs(CLEVER_ARG_INT(0)));
}
*/

/**
 * acos(double x)
 * Returns the arc cosine of an angle of x radians
 */
static CLEVER_FUNCTION(acos) {
	CLEVER_RETURN_DOUBLE(::std::acos(CLEVER_ARG_DOUBLE(0)));
}

/**
 * asin(double x)
 * Returns the arc sine of an angle of x radians
 */
static CLEVER_FUNCTION(asin) {
	CLEVER_RETURN_DOUBLE(::std::asin(CLEVER_ARG_DOUBLE(0)));
}

/**
 * atan(double x)
 * Returns the arc tangent of an angle of x radians
 */
static CLEVER_FUNCTION(atan) {
	CLEVER_RETURN_DOUBLE(::std::atan(CLEVER_ARG_DOUBLE(0)));
}

/**
 * ceil(double x)
 * Returns the smallest integral value that is not less than x
 */
static CLEVER_FUNCTION(ceil) {
	CLEVER_RETURN_DOUBLE(::std::ceil(CLEVER_ARG_DOUBLE(0)));
}

/**
 * cos(double x)
 * Returns the cosine of an angle of x radians
 */
static CLEVER_FUNCTION(cos) {
	CLEVER_RETURN_DOUBLE(::std::cos(CLEVER_ARG_DOUBLE(0)));
}

/**
 * floor(double x)
 * Returns the largest integral value that is not greater than x
 */
static CLEVER_FUNCTION(floor) {
	CLEVER_RETURN_DOUBLE(::std::floor(CLEVER_ARG_DOUBLE(0)));
}

/**
 * logb(double x, double base)
 * Returns the logarithm of the value using the specified base
 */
static CLEVER_FUNCTION(logb) {
	double logval = ::std::log10(CLEVER_ARG_DOUBLE(0));
	double logbase = ::std::log10(CLEVER_ARG_DOUBLE(1));

	CLEVER_RETURN_DOUBLE(logval/logbase);
}

/**
 * loge(double x)
 * Returns the natural logarithm of the value
 */
/*
static CLEVER_FUNCTION(loge) {
	CLEVER_RETURN_DOUBLE(::std::log(CLEVER_ARG_DOUBLE(0)));
}*/

/**
 * log10(double x)
 * Returns the common (base 10) logarithm of the value
 */
static CLEVER_FUNCTION(log10) {
	CLEVER_RETURN_DOUBLE(::std::log10(CLEVER_ARG_DOUBLE(0)));
}

/**
 * max(double x, double y)
 * Returns which value is greater, x or y
 */
static CLEVER_FUNCTION(max_double) {
	if (CLEVER_ARG_DOUBLE(0) > CLEVER_ARG_DOUBLE(1)) {
		CLEVER_RETURN_DOUBLE(CLEVER_ARG_DOUBLE(0));
	} else {
		CLEVER_RETURN_DOUBLE(CLEVER_ARG_DOUBLE(1));
	}
}

/**
 * max(int x, int y)
 * Returns which value is greater, x or y
 */
 /*
static CLEVER_FUNCTION(max_int) {
	if (CLEVER_ARG_INT(0) > CLEVER_ARG(1)->getInteger()) {
		retval->setInteger(CLEVER_ARG_INT(0));
	} else {
		retval->setInteger(CLEVER_ARG(1)->getInteger());
	}
}*/

/**
 * min(double x, double y)
 * Returns which value is smaller, x or y
 */
static CLEVER_FUNCTION(min_double) {
	if (CLEVER_ARG_DOUBLE(0) < CLEVER_ARG_DOUBLE(1)) {
		CLEVER_RETURN_DOUBLE(CLEVER_ARG_DOUBLE(0));
	} else {
		CLEVER_RETURN_DOUBLE(CLEVER_ARG_DOUBLE(1));
	}
}

/**
 * min(int x, int y)
 * Returns which value is smaller, x or y
 */
 /*
static CLEVER_FUNCTION(min_int) {
	if (CLEVER_ARG_INT(0) < CLEVER_ARG(1)->getInteger()) {
		retval->setInteger(CLEVER_ARG_INT(0));
	} else {
		retval->setInteger(CLEVER_ARG(1)->getInteger());
	}
}*/

/**
 * pow(double x, double y)
 * Returns x raised to the power y
 */
static CLEVER_FUNCTION(pow_double) {
	CLEVER_RETURN_DOUBLE(::std::pow(CLEVER_ARG_DOUBLE(0), CLEVER_ARG_DOUBLE(1)));
}

/**
 * pow(int x, int y)
 * Returns x raised to the power y
 */
 /*
static CLEVER_FUNCTION(pow_int) {
	retval->setInteger(::std::pow(CLEVER_ARG_INT(0), CLEVER_ARG(1)->getInteger()));
}*/

/**
 * round(double x)
 * Returns the rounded value of x
 */
static CLEVER_FUNCTION(round) {
	double value = CLEVER_ARG_DOUBLE(0);

#ifdef CLEVER_MSVC
	CLEVER_RETURN_DOUBLE((value > 0.0) ? ::floor(value + 0.5) : ::ceil(value - 0.5));
#else
	CLEVER_RETURN_DOUBLE(::round(value));
#endif
}

/**
 * sign(double x)
 * Returns a value indicating the sign of x
 */
static CLEVER_FUNCTION(sign_double) {
	if (CLEVER_ARG_DOUBLE(0) == .0) {
		CLEVER_RETURN_DOUBLE(.0);
	} else if (CLEVER_ARG_DOUBLE(0) < .0) {
		CLEVER_RETURN_DOUBLE(-1.0);
	} else {
		CLEVER_RETURN_DOUBLE(1.0);
	}
}

/**
 * sign(int x)
 * Returns a value indicating the sign of x
 */
 /*
static CLEVER_FUNCTION(sign_int) {
	if (CLEVER_ARG_INT(0) == 0) {
		retval->setInteger(0);
	} else if (CLEVER_ARG_INT(0) < 0) {
		retval->setInteger(-1);
	} else {
		retval->setInteger(1);
	}
}*/

/**
 * sin(double x)
 * Returns the sine of an angle of x radians
 */
static CLEVER_FUNCTION(sin) {
	CLEVER_RETURN_DOUBLE(::std::sin(CLEVER_ARG_DOUBLE(0)));
}

/**
 * sqrt(double x)
 * Returns the square root of a number x
 */
static CLEVER_FUNCTION(sqrt) {
	double value;

	if (CLEVER_ARG(0)->isDouble()) {
		value = CLEVER_ARG_DOUBLE(0);
	} else {
		value = double(CLEVER_ARG_INT(0));
	}

	CLEVER_RETURN_DOUBLE(::std::sqrt(value));
}

/**
 * tan(double x)
 * Returns the tangent of an angle of x radians
 */
static CLEVER_FUNCTION(tan) {
	CLEVER_RETURN_DOUBLE(::std::tan(CLEVER_ARG_DOUBLE(0)));
}

/**
 * truncate(double x)
 * Returns the value of x truncating the decimal part
 */
static CLEVER_FUNCTION(truncate) {
	CLEVER_RETURN_DOUBLE((int)CLEVER_ARG_DOUBLE(0));
}

} // math

/**
 * Load module data
 */
CLEVER_MODULE_INIT(Math) {
	BEGIN_DECLARE_FUNCTION();

	addConstant(CSTRING("MATH_PI"), new Value(M_PI));

	addFunction(new Function("abs",	&CLEVER_NS_FNAME(math, abs_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

/*	addFunction(new Function("abs",	&CLEVER_NS_FNAME(math, abs_int), CLEVER_INT))
		->addArg("x", CLEVER_INT);
*/
	addFunction(new Function("acos", &CLEVER_NS_FNAME(math, acos), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("asin", &CLEVER_NS_FNAME(math, asin), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("atan", &CLEVER_NS_FNAME(math, atan), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("ceil", &CLEVER_NS_FNAME(math, ceil), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("cos",  &CLEVER_NS_FNAME(math, cos), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("floor",  &CLEVER_NS_FNAME(math, floor), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("log", &CLEVER_NS_FNAME(math, logb), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("base", CLEVER_DOUBLE);

/*	addFunction(new Function("log",  &CLEVER_NS_FNAME(math, loge), CLEVER_DOUBLE))
		->addArg("value", CLEVER_DOUBLE);
*/
	addFunction(new Function("log10",  &CLEVER_NS_FNAME(math, log10), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("max", &CLEVER_NS_FNAME(math, max_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);
/*
	addFunction(new Function("max", &CLEVER_NS_FNAME(math, max_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("y", CLEVER_INT);*/

	addFunction(new Function("min", &CLEVER_NS_FNAME(math, min_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);
/*
	addFunction(new Function("min", &CLEVER_NS_FNAME(math, min_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("y", CLEVER_INT);*/

	addFunction(new Function("pow",  &CLEVER_NS_FNAME(math, pow_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);/*

	addFunction(new Function("pow",  &CLEVER_NS_FNAME(math, pow_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("exp", CLEVER_INT);*/

	addFunction(new Function("round",  &CLEVER_NS_FNAME(math, round), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("sin",  &CLEVER_NS_FNAME(math, sin), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("sign", &CLEVER_NS_FNAME(math, sign_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);
/*
	addFunction(new Function("sign", &CLEVER_NS_FNAME(math, sign_int), CLEVER_INT))
		->addArg("x", CLEVER_INT);*/

	addFunction(new Function("sqrt", &CLEVER_NS_FNAME(math, sqrt), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("tan",  &CLEVER_NS_FNAME(math, tan), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("truncate",  &CLEVER_NS_FNAME(math, truncate), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	END_DECLARE();
}

}}} // clever::packages::std
