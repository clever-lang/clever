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

#ifndef CLEVER_SESSIONVALUE_H
#define CLEVER_SESSIONVALUE_H

#include <cgicc/HTTPHeader.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/CgiEnvironment.h>
#include <map>
#include <string>
#include <cgicc/Cgicc.h>

#include "compiler/datavalue.h"

namespace clever { namespace packages { namespace web { namespace http {

class SessionValue : public DataValue {
public:
	SessionValue(){ 
		cgi = new cgicc::Cgicc;
		header = new cgicc::HTTPHTMLHeader;
		cgiEnv = new cgicc::CgiEnvironment(cgi->getEnvironment()); 
		cookVec = new std::vector<cgicc::HTTPCookie>; 
		mapCook = new std::map<std::string,std::string>;
	}
	
	// Cgi
	cgicc::Cgicc* cgi;
	cgicc::HTTPHTMLHeader* header;
	cgicc::CgiEnvironment* cgiEnv;
	std::vector<cgicc::HTTPCookie>* cookVec;
	std::map<std::string,std::string>* mapCook;	

	virtual ~SessionValue() { delete cgi; delete header; delete cgiEnv; delete cookVec; delete mapCook; }
};

}}}} // clever::packages::web::http

#endif

