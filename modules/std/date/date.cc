/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "types/type.h"
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/date/module.h"
#include "modules/std/date/date.h"

namespace clever { namespace packages { namespace std {

void Date::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void Date::dump(const void* data, ::std::ostream& out) const
{
	Value::DataValue* dvalue = static_cast<Value::DataValue*>(const_cast<void*>(data));
	if (dvalue) {
		time_t* uvalue = static_cast<time_t*>(dvalue->obj->getObj());
		if (uvalue) {
			out << *uvalue;
		}
	}
}

void* Date::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	time_t* intern = new time_t;
	if (intern) {
		if (args->size()) {
			*intern = static_cast<time_t>(args->at(0)->getInt());
		} else { time(intern); }
	}
	return intern;
}

void Date::deallocData(void *data)
{
	time_t* intern = static_cast<time_t*>(data);
	if (intern) {
		delete intern;
	}
}

static inline void clever_date_format(const ::std::vector<Value*>* args,
	const Value* obj, Value* result, bool utc)
{
	time_t* intern = CLEVER_GET_OBJECT(time_t*, CLEVER_THIS());

	if (!intern) {
		//CLEVER_THROW(eventually)
		return;
	}

	const char* format = args->at(0)->getStr()->c_str();
	if (!format) {
		//CLEVER_THROW(eventually);
		return;
	}

	struct tm* local;
	if (utc) {
		local = gmtime(intern);
	} else {
		local = localtime(intern);
	}

	size_t need = strftime(NULL, -1, format, local);
	if (!need) {
		//CLEVER_THROW(eventually);
		//There shouldn't be a circumstance where this arises ??
		return;
	} else {
		need += 1;
	}

	char buffer[need];
	if (strftime(buffer, need, format, local)) {
		result->setStr(new StrObject(new CString(buffer), false));
	} else {
		result->setNull();
	}
}

/*
String Date::format(string specstring)
Formats this date object as a string:
specifier	Replaced by								Example
%a			Abbreviated weekday name				Thu
%A			Full weekday name						Thursday
%b			Abbreviated month name					Aug
%B			Full month name							August
%c			Date and time representation			Thu Aug 23 14:55:02 2001
%d			Day of the month (01-31)				23
%H			Hour in 24h format (00-23)				14
%I			Hour in 12h format (01-12)				02
%j			Day of the year (001-366)				235
%m			Month as a decimal number (01-12)		08
%M			Minute (00-59)							55
%p			AM or PM designation					PM
%S			Second (00-61)							02
%U			Week number (00-53)						33
%w			Weekday with Sunday as 0 (0-6)			4
%W			Week number (00-53)						34
%x			Date representation 					08/23/01
%X			Time representation 					14:55:02
%y			Year, last two digits (00-99)			01
%Y			Year									2001
%Z			Timezone name or abbreviation			CDT
%%			A % sign								%
*/
CLEVER_METHOD(Date::format)
{
	if (!clever_check_args("s")) {
		return;
	}

	clever_date_format(&args, CLEVER_THIS(), result, false);
}

// String Date.uformat(string specstring)
// Formats this date as a string, using the same specifiers as Date.format
// Treats the date as UTC
CLEVER_METHOD(Date::uformat)
{
	if (!clever_check_args("s")) {
		return;
	}

	clever_date_format(&args, CLEVER_THIS(), result, true);
}

// Int Date::getTime()
// Returns the time represented by this Date object as a Unix timestamp
CLEVER_METHOD(Date::getTime)
{
	time_t* intern = CLEVER_GET_OBJECT(time_t*, CLEVER_THIS());

	if (!intern) {
		//CLEVER_THROW(eventually)
		return;
	}

	result->setInt(*intern);
}

// Date Date.new([int time])
// Constructs a new Date object, uses the current time if none is provided
CLEVER_METHOD(Date::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_TYPE_INIT(Date::init)
{
	Function* ctor = new Function("Date", (MethodPtr) &Date::ctor);

	setConstructor(ctor);

	addMethod(ctor);
	addMethod(new Function("format",     (MethodPtr) &Date::format));
	addMethod(new Function("uformat",    (MethodPtr) &Date::uformat));
	addMethod(new Function("getTime",    (MethodPtr) &Date::getTime));
}

}}} // clever::packages::std
