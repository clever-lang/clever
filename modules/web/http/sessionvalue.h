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
#include <map>
#include <string>
#include <cgicc/Cgicc.h>

#include "compiler/datavalue.h"

namespace clever { namespace packages { namespace web { namespace http {

class SessionValue : public DataValue {
public:
	SessionValue(){ 
		h = new cgicc::HTTPHTMLHeader; 
		cv = new std::vector<cgicc::HTTPCookie>; 
		mc = new std::map<std::string,std::string>;
	}
	
	// Cgi
	cgicc::HTTPHTMLHeader* h;
	std::vector<cgicc::HTTPCookie>* cv;
	std::map<std::string,std::string>* mc;	

	virtual ~SessionValue() { delete h; delete cv; delete mc; }
};

}}}} // clever::packages::web::http

#endif

