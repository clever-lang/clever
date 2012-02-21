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
#include "modules/web/http/sessionclass.h"
#include "types/nativetypes.h"


namespace clever { namespace packages { namespace web { namespace http {


typedef std::vector<cgicc::HTTPCookie>::iterator it_cv;

CLEVER_METHOD(Session::refresh) {
	SessionValue* sv = CLEVER_GET_VALUE(SessionValue*, value);

	cgicc::CgiEnvironment& c = *(sv->cgiEnv);
	std::vector<cgicc::HTTPCookie>& cv = *(sv->cookVec);
	std::map<std::string,std::string>& mc = *(sv->mapCook);	

	cv = c.getCookieList();
	sv->mapCook->clear();

	it_cv it = cv.begin(), end = cv.end();

	while (it != end) {
		mc[it->getName()]=it->getValue();
		++it;
	}
}

CLEVER_METHOD(Session::getCookie) {
	SessionValue* sv = CLEVER_GET_VALUE(SessionValue*, value);
	std::map<std::string,std::string>& mc = *(sv->mapCook);

	CLEVER_RETURN_STR(CSTRING(mc[CLEVER_ARG_STR(0)]));
}

CLEVER_METHOD(Session::getCookies) {
	SessionValue* sv = CLEVER_GET_VALUE(SessionValue*, value);
	cgicc::CgiEnvironment& c = *(sv->cgiEnv);

	CLEVER_RETURN_STR(CSTRING(c.getCookies()));
}

CLEVER_METHOD(Session::setCookie) {
	SessionValue* sv = CLEVER_GET_VALUE(SessionValue*, value);

	cgicc::HTTPHTMLHeader& h =  *(sv->header);
	std::vector<cgicc::HTTPCookie>& cv = *(sv->cookVec);
	std::map<std::string,std::string>& mc = *(sv->mapCook);	

	cgicc::HTTPCookie cookie(CLEVER_ARG_STR(0),CLEVER_ARG_STR(1));	
	
	mc[CLEVER_ARG_STR(0)]=CLEVER_ARG_STR(1);
	cv.push_back(cookie);
	h.setCookie(cookie);

}

CLEVER_METHOD(Session::header) {
	SessionValue* sv = CLEVER_GET_VALUE(SessionValue*, value);
	cgicc::HTTPHTMLHeader& h =  *(sv->header);

	::std::cout<< h << ::std::endl;
}

void Session::init() {
	addMethod(
		(new Method("refresh", (MethodPtr)&Session::refresh, CLEVER_VOID))
	);

	addMethod(
		(new Method("getCookie", (MethodPtr)&Session::getCookie, CLEVER_STR))
			->addArg("name", CLEVER_STR)
	);

	addMethod(
		(new Method("getCookies", (MethodPtr)&Session::getCookie, CLEVER_STR))
	);

	addMethod(
		(new Method("setCookie", (MethodPtr)&Session::setCookie, CLEVER_VOID))
			->addArg("name", CLEVER_STR)
			->addArg("value",CLEVER_STR)
	);

	addMethod(
		(new Method("header", (MethodPtr)&Session::header, CLEVER_VOID))
	);
}

DataValue* Session::allocateValue() const {
	return new SessionValue;
}

void Session::destructor(Value* value) const {
	//CgiValue* cv = CLEVER_GET_VALUE(CgiValue*, value);
	//delete cv->cgi;
	//delete cv;
}

}}}} // clever::packages::web::http

