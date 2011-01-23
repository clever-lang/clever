/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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
 * $Id: std.cc 299 2011-01-16 23:06:11Z felipensp $
 */

#include <cmath>
#include "module.h"
#include "std/math.h"

namespace clever { namespace std_pkg {

Module* g_math_module = new Math;

/**
 * sqrt(double x)
 * Returns the square root of a number x
 */
static CLEVER_FUNCTION(sqrt) {
	retval->setDouble(std::sqrt(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * cos(double x)
 * Returns the cosine of an angle of x radians
 */
static CLEVER_FUNCTION(cos) {
	retval->setDouble(std::cos(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * sin(double x)
 * Returns the sine of an angle of x radians
 */
static CLEVER_FUNCTION(sin) {
	retval->setDouble(std::sin(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * tan(double x)
 * Returns the tangent of an angle of x radians
 */
static CLEVER_FUNCTION(tan) {
	retval->setDouble(std::tan(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * atan(double x)
 * Returns the arc tangent of an angle of x radians
 */
static CLEVER_FUNCTION(atan) {
	retval->setDouble(std::atan(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * pow(double x, double y)
 * Returns x raised to the power y
 */
static CLEVER_FUNCTION(pow) {
	retval->setDouble(std::pow(args->at(0)->getDouble(), args->at(1)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * ceil(double x)
 * Returns the smallest integral value that is not less than x
 */
static CLEVER_FUNCTION(ceil) {
	retval->setDouble(std::ceil(args->at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * abs(double x)
 * Returns the absolute value of a number x
 */
static CLEVER_FUNCTION(abs) {
	if (args->at(0)->get_type() == Value::DOUBLE) {
		retval->setDouble(std::fabs(args->at(0)->getDouble()));
		retval->set_type(Value::DOUBLE);
	} else {
		retval->setInteger(std::abs(args->at(0)->getInteger()));
		retval->set_type(Value::INTEGER);
	}
}

/**
 * Load module data
 */
void Math::Init() throw() {
	addFunction("sqrt", &CLEVER_FUNC_NAME(sqrt));
	addFunction("sin",  &CLEVER_FUNC_NAME(sin));
	addFunction("cos",  &CLEVER_FUNC_NAME(cos));
	addFunction("tan",  &CLEVER_FUNC_NAME(tan));
	addFunction("atan", &CLEVER_FUNC_NAME(atan));
	addFunction("pow",  &CLEVER_FUNC_NAME(pow));
	addFunction("ceil", &CLEVER_FUNC_NAME(ceil));
	addFunction("abs",	&CLEVER_FUNC_NAME(abs));
}


}} // clever::std_package