/**
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
 */

#include <cmath>
#include <cstdlib>
#include <string>
#include <iostream>
#include "compiler/symboltable.h"
#include "modules/std/math/math.h"

namespace clever { namespace packages { namespace std {

namespace math {
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
	retval->setType(Value::DOUBLE);
}

/**
 * cos(double x)
 * Returns the cosine of an angle of x radians
 */
static CLEVER_FUNCTION(cos) {
	retval->setDouble(::std::cos(args->at(0)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * sin(double x)
 * Returns the sine of an angle of x radians
 */
static CLEVER_FUNCTION(sin) {
	retval->setDouble(::std::sin(args->at(0)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * tan(double x)
 * Returns the tangent of an angle of x radians
 */
static CLEVER_FUNCTION(tan) {
	retval->setDouble(::std::tan(args->at(0)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * atan(double x)
 * Returns the arc tangent of an angle of x radians
 */
static CLEVER_FUNCTION(atan) {
	retval->setDouble(::std::atan(args->at(0)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * pow(double x, double y)
 * Returns x raised to the power y
 */
static CLEVER_FUNCTION(pow) {
	retval->setDouble(::std::pow(args->at(0)->getDouble(), args->at(1)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * ceil(double x)
 * Returns the smallest integral value that is not less than x
 */
static CLEVER_FUNCTION(ceil) {
	retval->setDouble(::std::ceil(args->at(0)->getDouble()));
	retval->setType(Value::DOUBLE);
}

/**
 * abs(double x)
 * abs(int x)
 * Returns the absolute value of a number x
 */
static CLEVER_FUNCTION(abs) {
	if (args->at(0)->getType() == Value::DOUBLE) {
		retval->setDouble(::std::abs(args->at(0)->getDouble()));
		retval->setType(Value::DOUBLE);
	} else {
		retval->setInteger(::std::labs(args->at(0)->getInteger()));
		retval->setType(Value::INTEGER);
	}
}

} // math

/**
 * Load module data
 */
void Math::init() throw() {
	const Type* double_type = CLEVER_TYPE("Double");

	addFunction(new Function("sqrt", &CLEVER_NS_FNAME(math, sqrt), double_type))
		->addArg("value", double_type);

	addFunction(new Function("sin",  &CLEVER_NS_FNAME(math, sin), double_type))
		->addArg("value", double_type);

	addFunction(new Function("cos",  &CLEVER_NS_FNAME(math, cos), double_type))
		->addArg("value", double_type);

	addFunction(new Function("tan",  &CLEVER_NS_FNAME(math, tan), double_type))
		->addArg("value", double_type);

	addFunction(new Function("atan", &CLEVER_NS_FNAME(math, atan), double_type))
		->addArg("value", double_type);

	addFunction(new Function("pow",  &CLEVER_NS_FNAME(math, pow), double_type))
		->addArg("x", double_type)
		->addArg("y", double_type);

	addFunction(new Function("ceil", &CLEVER_NS_FNAME(math, ceil), double_type))
		->addArg("value", double_type);

	addFunction(new Function("abs",	&CLEVER_NS_FNAME(math, abs), double_type))
		->addArg("value", double_type);
}

}}} // clever::packages::std
