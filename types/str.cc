/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <string>
#include <sstream>
#include "types/str.h"

namespace clever {

CLEVER_TYPE_OPERATOR(StrType::add)
{
	if (EXPECTED(rhs->getType() == this)) {
		// TODO(Felipe): Do not require CString everywhere (because it stores the
		// data in an string table)
		result->setStr(CSTRING(*lhs->getStr() + *rhs->getStr()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::sub)
{	
}

CLEVER_TYPE_OPERATOR(StrType::mul)
{
	if (rhs->getType() == CLEVER_INT_TYPE) {
		std::ostringstream os;

		for (long i = 0, j = rhs->getInt(); i < j; ++i) {
			os << *lhs->getStr();
		}

		result->setStr(CSTRING(os.str()));
	}
}

CLEVER_TYPE_OPERATOR(StrType::div)
{
}

CLEVER_TYPE_OPERATOR(StrType::mod)
{	
}

CLEVER_METHOD(StrType::subString) 
{
	char *of;
	int bounds[2];

	bounds[0]=-1;
	bounds[1]=-1;

	if (CLEVER_THIS()) {
		of = (char*) CLEVER_THIS()->getStr()->c_str();
		switch(CLEVER_ARG_COUNT()) {
			case 2:
				bounds[0]=CLEVER_ARG_INT(0);
				bounds[1]=CLEVER_ARG_INT(1);
			break;
			case 1: 
				bounds[0]=CLEVER_ARG_INT(0);
			break;
			default: std::cerr << "String.subString expected at least one argument";
		}
	} else {
		of = CLEVER_ARG_PSTR(0);
		switch(CLEVER_ARG_COUNT()) {
			case 3:
				bounds[0]=CLEVER_ARG_INT(1);
				bounds[1]=CLEVER_ARG_INT(2);
			break;
			case 2: bounds[0]=CLEVER_ARG_INT(1); break;
			
			default: std::cerr << "String.subString expected at least two arguments";
		}
	}

	if (of && bounds[0]>-1) {
		std::ostringstream buffer;
		{
			buffer << of;
			if (buffer) {
				if (bounds[1]>-1) {
					result->setStr(CSTRING(buffer.str().substr(bounds[0], bounds[1])));
				} else result->setStr(CSTRING(buffer.str().substr(bounds[0])));
			}
		}
	}
}

CLEVER_TYPE_INIT(StrType::init) 
{
	addMethod(CSTRING("subString"),  (MethodPtr) &StrType::subString);
}

} // clever
