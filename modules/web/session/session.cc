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


#include <iostream>
#include <fstream>
#include <cgicc/HTTPHeader.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/CgiEnvironment.h>
#include <map>
#include <vector>
#include <string>
#include <cgicc/Cgicc.h>

#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/web/request/request.h"
#include "modules/web/session/session.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace web {


cgicc::Cgicc* s_cgi;
cgicc::HTTPHTMLHeader* header;
cgicc::CgiEnvironment* cgiEnv;
std::vector<cgicc::HTTPCookie>* cookVec;
std::map<std::string,std::string>* mapCook;	

typedef std::vector<cgicc::HTTPCookie>::iterator it_cv;

void __init_session__() {
	
	cgicc::CgiEnvironment& c = *(cgiEnv);
	std::vector<cgicc::HTTPCookie>& cv = *(cookVec);
	std::map<std::string,std::string>& mc = *(mapCook);	

	cv = c.getCookieList();
	mapCook->clear();

	it_cv it = cv.begin(), end = cv.end();

	while (it != end) {
		mc[it->getName()]=it->getValue();
		++it;
	}
}


namespace session {

static CLEVER_FUNCTION(getCookie) {
	std::map<std::string,std::string>& mc = *(mapCook);

	CLEVER_RETURN_STR(CSTRING(mc[CLEVER_ARG_STR(0)]));
}

static CLEVER_FUNCTION(setCookie) {
	cgicc::HTTPHTMLHeader& h =  *(header);
	std::vector<cgicc::HTTPCookie>& cv = *(cookVec);
	std::map<std::string,std::string>& mc = *(mapCook);	

	cgicc::HTTPCookie cookie(CLEVER_ARG_STR(0),CLEVER_ARG_STR(1));	
	
	mc[CLEVER_ARG_STR(0)]=CLEVER_ARG_STR(1);
	cv.push_back(cookie);
	h.setCookie(cookie);

}

static CLEVER_FUNCTION(header) {
	cgicc::HTTPHTMLHeader& h =  *(header);

	::std::cout<< h << ::std::endl;
}

} // web

/**
 * Load module data
 */
void Session::init() {

	__init_session__();

	addFunction(new Function("header",&CLEVER_NS_FNAME(session, header), CLEVER_VOID));
		
	addFunction(new Function("getCookie",&CLEVER_NS_FNAME(session,getCookie), CLEVER_STR))
		->addArg("name", CLEVER_STR);

	
	addFunction(new Function("setCookie", &CLEVER_NS_FNAME(session,setCookie), CLEVER_VOID))
			->addArg("name", CLEVER_STR)
			->addArg("value",CLEVER_STR);
}

Session::Session()
	: Module("Session") { 
	s_cgi = new cgicc::Cgicc;
	header = new cgicc::HTTPHTMLHeader;
	cgiEnv = new cgicc::CgiEnvironment(s_cgi->getEnvironment()); 
	cookVec = new std::vector<cgicc::HTTPCookie>; 
	mapCook = new std::map<std::string,std::string>;
}

Session::~Session() {
	delete s_cgi; 
	delete header; 
	delete cgiEnv; 
	delete cookVec; 
	delete mapCook;
}

}}} // clever::packages::web
