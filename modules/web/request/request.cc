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


#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include <cgicc/Cgicc.h>


#include "compiler/value.h"
#include "modules/web/request/request.h"


namespace clever { namespace packages { namespace web {

cgicc::Cgicc* r_cgi;

namespace request {
	
static CLEVER_FUNCTION(params) {
	
	cgicc::form_iterator name = r_cgi->getElement(CLEVER_ARG_STR(0));
	if(name != r_cgi->getElements().end()) {
		CLEVER_RETURN_STR(CSTRING(name->getValue().c_str()));
		return;
	}

	CLEVER_RETURN_STR(CSTRING("0"));
}

} // request

/**
 * Initializes Standard module
 */
void RequestModule::init() {
	addFunction(new Function("params",&CLEVER_NS_FNAME(request,params), CLEVER_STR))
		->addArg("name", CLEVER_STR);
}

RequestModule::RequestModule()
	: Module("request") { 
	r_cgi=new cgicc::Cgicc;
}

RequestModule::~RequestModule() {
	delete r_cgi;
}


}}} // clever::packages::web
