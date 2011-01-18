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

namespace clever { namespace std_module {

/**
 * sqrt(double x)
 * Returns the square root of a number x
 */
CLEVER_FUNCTION(sqrt) {
	retval->setDouble(std::sqrt(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * cos(double x)
 * Returns the cosine of an angle of x radians
 */
CLEVER_FUNCTION(cos) {
	retval->setDouble(std::cos(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * sin(double x)
 * Returns the sine of an angle of x radians
 */
CLEVER_FUNCTION(sin) {
	retval->setDouble(std::sin(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * tan(double x)
 * Returns the tangent of an angle of x radians
 */
CLEVER_FUNCTION(tan) {
	retval->setDouble(std::tan(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * atan(double x)
 * Returns the arc tangent of an angle of x radians
 */
CLEVER_FUNCTION(atan) {
	retval->setDouble(std::atan(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * pow(double x, double y)
 * Returns x raised to the power y
 */
CLEVER_FUNCTION(pow) {
	retval->setDouble(std::pow(args.at(0)->getDouble(), args.at(1)->getDouble()));
	retval->set_type(Value::DOUBLE);
}

/**
 * ceil(double x)
 * Returns the smallest integral value that is not less than x
 */
CLEVER_FUNCTION(ceil) {
	retval->setDouble(std::ceil(args.at(0)->getDouble()));
	retval->set_type(Value::DOUBLE);
}


}} // clever::std_module