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
#include <string>
#include <iostream>
#include "compiler/symboltable.h"
#include "modules/std/math/math.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std {

namespace math {

/**
 * abs(double x)
 * Returns the absolute value of a number x
 */
static CLEVER_FUNCTION(abs_double) {
	retval->setDouble(::std::abs(args->at(0)->getDouble()));
}

/**
 * abs(int x)
 * Returns the absolute value of a number x
 */
static CLEVER_FUNCTION(abs_int) {
	retval->setInteger(::std::labs(args->at(0)->getInteger()));
}

/**
 * acos(double x)
 * Returns the arc cosine of an angle of x radians
 */
static CLEVER_FUNCTION(acos) {
	retval->setDouble(::std::acos(args->at(0)->getDouble()));
}

/**
 * asin(double x)
 * Returns the arc sine of an angle of x radians
 */
static CLEVER_FUNCTION(asin) {
	retval->setDouble(::std::asin(args->at(0)->getDouble()));
}

/**
 * atan(double x)
 * Returns the arc tangent of an angle of x radians
 */
static CLEVER_FUNCTION(atan) {
	retval->setDouble(::std::atan(args->at(0)->getDouble()));
}

/**
 * ceil(double x)
 * Returns the smallest integral value that is not less than x
 */
static CLEVER_FUNCTION(ceil) {
	retval->setDouble(::std::ceil(args->at(0)->getDouble()));
}

/**
 * cos(double x)
 * Returns the cosine of an angle of x radians
 */
static CLEVER_FUNCTION(cos) {
	retval->setDouble(::std::cos(args->at(0)->getDouble()));
}

/**
 * floor(double x)
 * Returns the largest integral value that is not greater than x
 */
static CLEVER_FUNCTION(floor) {
	retval->setDouble(::std::floor(args->at(0)->getDouble()));
}

/**
 * logb(double x, double base)
 * Returns the logarithm of the value using the specified base
 */
static CLEVER_FUNCTION(logb) {
	double logval = ::std::log10(args->at(0)->getDouble());
	double logbase = ::std::log10(args->at(1)->getDouble());
	
	retval->setDouble(logval/logbase);
}

/**
 * loge(double x)
 * Returns the natural logarithm of the value
 */
static CLEVER_FUNCTION(loge) {
	retval->setDouble(::std::log(args->at(0)->getDouble()));
}

/**
 * log10(double x)
 * Returns the common (base 10) logarithm of the value
 */
static CLEVER_FUNCTION(log10) {
	retval->setDouble(::std::log10(args->at(0)->getDouble()));
}

/**
 * max(double x, double y)
 * Returns which value is greater, x or y
 */
static CLEVER_FUNCTION(max_double) {
	if (args->at(0)->getDouble() > args->at(1)->getDouble()) {
		retval->setDouble(args->at(0)->getDouble());
	} else {
		retval->setDouble(args->at(1)->getDouble());
	}
}

/**
 * max(int x, int y)
 * Returns which value is greater, x or y
 */
static CLEVER_FUNCTION(max_int) {
	if (args->at(0)->getInteger() > args->at(1)->getInteger()) {
		retval->setInteger(args->at(0)->getInteger());
	} else {
		retval->setInteger(args->at(1)->getInteger());
	}
}

/**
 * min(double x, double y)
 * Returns which value is smaller, x or y
 */
static CLEVER_FUNCTION(min_double) {
	if (args->at(0)->getDouble() < args->at(1)->getDouble()) {
		retval->setDouble(args->at(0)->getDouble());
	} else {
		retval->setDouble(args->at(1)->getDouble());
	}
}

/**
 * min(int x, int y)
 * Returns which value is smaller, x or y
 */
static CLEVER_FUNCTION(min_int) {
	if (args->at(0)->getInteger() < args->at(1)->getInteger()) {
		retval->setInteger(args->at(0)->getInteger());
	} else {
		retval->setInteger(args->at(1)->getInteger());
	}
}

/**
 * pow(double x, double y)
 * Returns x raised to the power y
 */
static CLEVER_FUNCTION(pow_double) {
	retval->setDouble(::std::pow(args->at(0)->getDouble(), args->at(1)->getDouble()));
}

/**
 * pow(int x, int y)
 * Returns x raised to the power y
 */
static CLEVER_FUNCTION(pow_int) {
	retval->setInteger(::std::pow(args->at(0)->getInteger(), args->at(1)->getInteger()));
}

/**
 * round(double x)
 * Returns the rounded value of x
 */
static CLEVER_FUNCTION(round) {
	double value = args->at(0)->getDouble();
	
	retval->setDouble(::round(value));
}

/**
 * sign(double x)
 * Returns a value indicating the sign of x
 */
static CLEVER_FUNCTION(sign_double) {
	if (args->at(0)->getDouble() == .0) {
		retval->setDouble(.0);
	} else if (args->at(0)->getDouble() < .0) {
		retval->setDouble(-1.0);
	} else {
		retval->setDouble(1.0);
	}
}

/**
 * sign(int x)
 * Returns a value indicating the sign of x
 */
static CLEVER_FUNCTION(sign_int) {
	if (args->at(0)->getInteger() == 0) {
		retval->setInteger(0);
	} else if (args->at(0)->getInteger() < 0) {
		retval->setInteger(-1);
	} else {
		retval->setInteger(1);
	}
}

/**
 * sin(double x)
 * Returns the sine of an angle of x radians
 */
static CLEVER_FUNCTION(sin) {
	retval->setDouble(::std::sin(args->at(0)->getDouble()));
}

/**
 * sqrt(double x)
 * Returns the square root of a number x
 */
static CLEVER_FUNCTION(sqrt) {
	double value;
	
	if (args->at(0)->isDouble()) {
		value = args->at(0)->getDouble();
	}
	else if (args->at(0)->isInteger()) {
		value = double(args->at(0)->getInteger());
	}
	else {
		::std::cout << "Double sqrt(Double num) requires 'num' "
                    "to be convertible to type Double.\n";
		::std::exit(1);
	}

	retval->setDouble(::std::sqrt(value));
}

/**
 * tan(double x)
 * Returns the tangent of an angle of x radians
 */
static CLEVER_FUNCTION(tan) {
	retval->setDouble(::std::tan(args->at(0)->getDouble()));
}

/**
 * truncate(double x)
 * Returns the value of x truncating the decimal part
 */
static CLEVER_FUNCTION(truncate) {
	retval->setDouble((int)args->at(0)->getDouble());
}

} // math

/**
 * Load module data
 */
void Math::init() throw() {
	addFunction(new Function("abs",	&CLEVER_NS_FNAME(math, abs_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("abs",	&CLEVER_NS_FNAME(math, abs_int), CLEVER_INT))
		->addArg("x", CLEVER_INT);

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

	addFunction(new Function("log",  &CLEVER_NS_FNAME(math, loge), CLEVER_DOUBLE))
		->addArg("value", CLEVER_DOUBLE);

	addFunction(new Function("log10",  &CLEVER_NS_FNAME(math, log10), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("max", &CLEVER_NS_FNAME(math, max_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);

	addFunction(new Function("max", &CLEVER_NS_FNAME(math, max_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("y", CLEVER_INT);

	addFunction(new Function("min", &CLEVER_NS_FNAME(math, min_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);

	addFunction(new Function("min", &CLEVER_NS_FNAME(math, min_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("y", CLEVER_INT);

	addFunction(new Function("pow",  &CLEVER_NS_FNAME(math, pow_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE)
		->addArg("y", CLEVER_DOUBLE);

	addFunction(new Function("pow",  &CLEVER_NS_FNAME(math, pow_int), CLEVER_INT))
		->addArg("x", CLEVER_INT)
		->addArg("exp", CLEVER_INT);

	addFunction(new Function("round",  &CLEVER_NS_FNAME(math, round), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("sin",  &CLEVER_NS_FNAME(math, sin), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("sign", &CLEVER_NS_FNAME(math, sign_double), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("sign", &CLEVER_NS_FNAME(math, sign_int), CLEVER_INT))
		->addArg("x", CLEVER_INT);

	addFunction(new Function("sqrt", &CLEVER_NS_FNAME(math, sqrt), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("tan",  &CLEVER_NS_FNAME(math, tan), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);

	addFunction(new Function("truncate",  &CLEVER_NS_FNAME(math, truncate), CLEVER_DOUBLE))
		->addArg("x", CLEVER_DOUBLE);
}

}}} // clever::packages::std
