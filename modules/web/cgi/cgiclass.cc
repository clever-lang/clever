/**
 * Clever programming language
 * Copyright (c) 2012 Clever Team
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
 */

#include <iostream>
#include <fstream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/web/cgi/cgiclass.h"
#include "types/nativetypes.h"


namespace clever { namespace packages { namespace web { namespace cgi {


CLEVER_METHOD(Cgi::getString) {
	CgiValue* cv = CLEVER_GET_VALUE(CgiValue*, value);
	
	cgicc::form_iterator name = cv->cgi->getElement(CLEVER_ARG_STR(0));
	if(name != cv->cgi->getElements().end()) {
		CLEVER_RETURN_STR(CSTRING(name->getValue().c_str()));
		return;
	}

	CLEVER_RETURN_STR(CSTRING(""));
}

CLEVER_METHOD(Cgi::getInt) {
	CgiValue* cv = CLEVER_GET_VALUE(CgiValue*, value);
	
	cgicc::form_iterator name = cv->cgi->getElement(CLEVER_ARG_STR(0));
	if(name != cv->cgi->getElements().end()) {
		CLEVER_RETURN_INT(name->getIntegerValue());
		return;
	}

	CLEVER_RETURN_INT(0);
}

CLEVER_METHOD(Cgi::getDouble) {
	CgiValue* cv = CLEVER_GET_VALUE(CgiValue*, value);
	
	cgicc::form_iterator name = cv->cgi->getElement(CLEVER_ARG_STR(0));
	if(name != cv->cgi->getElements().end()) {
		CLEVER_RETURN_DOUBLE(name->getDoubleValue());
		return;
	}

	CLEVER_RETURN_DOUBLE(0.0);
}


void Cgi::init() {
	
	addMethod(
		(new Method("getString", (MethodPtr)&Cgi::getString, CLEVER_STR))
			->addArg("name", CLEVER_STR)
	);

	addMethod(
		(new Method("getInt", (MethodPtr)&Cgi::getInt, CLEVER_INT))
			->addArg("name", CLEVER_STR)
	);

	addMethod(
		(new Method("getDouble", (MethodPtr)&Cgi::getDouble, CLEVER_DOUBLE))
			->addArg("name", CLEVER_STR)
	);
	
}

DataValue* Cgi::allocateValue() const {
	return new CgiValue;
}

void Cgi::destructor(Value* value) const {
	//CgiValue* cv = CLEVER_GET_VALUE(CgiValue*, value);
	//delete cv->cgi;
	//delete cv;
}

}}}} // clever::packages::web::cgi
