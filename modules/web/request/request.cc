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


#include <cgicc/CgiEnvironment.h>
#include <cgicc/Cgicc.h>


#include "compiler/value.h"
#include "modules/web/request/request.h"


namespace clever { namespace packages { namespace web {

cgicc::Cgicc* r_cgi;
cgicc::CgiEnvironment* r_cgiEnv;

namespace request {
	
static CLEVER_FUNCTION(param) {
	
	cgicc::form_iterator name = r_cgi->getElement(CLEVER_ARG_STR(0));
	if(name != r_cgi->getElements().end()) {
		CLEVER_RETURN_STR(CSTRING(name->getValue().c_str()));
		return;
	}

	CLEVER_RETURN_STR(CSTRING("0"));
}

/*
static CLEVER_FUNCTION(params) {
	cgicc::form_iterator name = r_cgi->getElement(CLEVER_ARG_STR(0));
	if(name != r_cgi->getElements().end()) {
		CLEVER_RETURN_STR(CSTRING(name->getValue().c_str()));
		return;
	}

	CLEVER_RETURN_STR(CSTRING("0"));
}
*/

// CGI Env ------

static CLEVER_FUNCTION(getServerSoftware) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getServerSoftware()));
}

static CLEVER_FUNCTION(getServerName) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getServerName()));
}

static CLEVER_FUNCTION(getGatewayInterface) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getGatewayInterface()));
}

static CLEVER_FUNCTION(getServerProtocol) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getServerProtocol()));
}

static CLEVER_FUNCTION(getServerPort) {	
	CLEVER_RETURN_INT(r_cgiEnv->getServerPort());
}

static CLEVER_FUNCTION(usingHTTPS) {	
	CLEVER_RETURN_BOOL(r_cgiEnv->usingHTTPS());
}



static CLEVER_FUNCTION(getPathInfo) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getPathInfo()));
}

static CLEVER_FUNCTION(getRequestMethod) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getRequestMethod()));
}

static CLEVER_FUNCTION(getPathTranslated) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getPathTranslated()));
}

static CLEVER_FUNCTION(getScriptName) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getScriptName()));
}

static CLEVER_FUNCTION(getQueryString) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getQueryString()));
}

static CLEVER_FUNCTION(getContentType) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getContentType()));
}

static CLEVER_FUNCTION(getPostData) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getPostData()));
}

static CLEVER_FUNCTION(getContentLength) {	
	CLEVER_RETURN_INT(r_cgiEnv->getContentLength());
}

static CLEVER_FUNCTION(getReferrer) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getReferrer()));
}


static CLEVER_FUNCTION(getRemoteHost) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getRemoteHost()));
}
static CLEVER_FUNCTION(getRemoteAddr) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getRemoteAddr()));
}
static CLEVER_FUNCTION(getAuthType) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getAuthType()));
}
static CLEVER_FUNCTION(getRemoteUser) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getRemoteUser()));
}
static CLEVER_FUNCTION(getRemoteIdent) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getRemoteIdent()));
}
static CLEVER_FUNCTION(getAccept) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getAccept()));
}
static CLEVER_FUNCTION(getUserAgent) {	
	CLEVER_RETURN_STR(CSTRING(r_cgiEnv->getUserAgent()));
}

} // request

/**
 * Initializes Standard module
 */
void RequestModule::init() {
	TemplateArgs strmap; strmap.push_back(CLEVER_STR); strmap.push_back(CLEVER_STR);
	
	addFunction(new Function("param",&CLEVER_NS_FNAME(request,param), CLEVER_STR))
		->addArg("name", CLEVER_STR);
		
	//addFunction(new Function("params",&CLEVER_NS_FNAME(request,params), strmap));
	
	addFunction(new Function("getServerSoftware", &CLEVER_NS_FNAME(request, getServerSoftware), CLEVER_STR));
	addFunction(new Function("getServerName", &CLEVER_NS_FNAME(request, getServerName), CLEVER_STR));
	addFunction(new Function("getGatewayInterface", &CLEVER_NS_FNAME(request, getGatewayInterface), CLEVER_STR));
	addFunction(new Function("getServerProtocol", &CLEVER_NS_FNAME(request, getServerProtocol), CLEVER_STR));
	addFunction(new Function("getServerPort", &CLEVER_NS_FNAME(request, getServerPort), CLEVER_INT));
	addFunction(new Function("usingHTTPS", &CLEVER_NS_FNAME(request, usingHTTPS), CLEVER_BOOL));
	
	addFunction(new Function("getPathInfo", &CLEVER_NS_FNAME(request, getPathInfo), CLEVER_STR));
	addFunction(new Function("getRequestMethod", &CLEVER_NS_FNAME(request, getRequestMethod), CLEVER_STR));
	addFunction(new Function("getPathTranslated", &CLEVER_NS_FNAME(request, getPathTranslated), CLEVER_STR));
	addFunction(new Function("getScriptName", &CLEVER_NS_FNAME(request, getScriptName), CLEVER_STR));
	addFunction(new Function("getQueryString", &CLEVER_NS_FNAME(request, getQueryString), CLEVER_STR));
	addFunction(new Function("getContentType", &CLEVER_NS_FNAME(request, getContentType), CLEVER_STR));
	addFunction(new Function("getPostData", &CLEVER_NS_FNAME(request, getPostData), CLEVER_STR));
	addFunction(new Function("getContentLength", &CLEVER_NS_FNAME(request, getContentLength), CLEVER_INT));
	
	addFunction(new Function("getReferrer", &CLEVER_NS_FNAME(request, getReferrer), CLEVER_STR));
	
	addFunction(new Function("getRemoteHost", &CLEVER_NS_FNAME(request, getRemoteHost), CLEVER_STR));
	addFunction(new Function("getRemoteAddr", &CLEVER_NS_FNAME(request, getRemoteAddr), CLEVER_STR));
	addFunction(new Function("getAuthType", &CLEVER_NS_FNAME(request, getAuthType), CLEVER_STR));
	addFunction(new Function("getRemoteUser", &CLEVER_NS_FNAME(request, getRemoteUser), CLEVER_STR));
	addFunction(new Function("getRemoteIdent", &CLEVER_NS_FNAME(request, getRemoteIdent), CLEVER_STR));
	addFunction(new Function("getAccept", &CLEVER_NS_FNAME(request, getAccept), CLEVER_STR));
	addFunction(new Function("getUserAgent", &CLEVER_NS_FNAME(request, getUserAgent), CLEVER_STR));
	
}

RequestModule::RequestModule()
	: Module("request") { 
	r_cgi=new cgicc::Cgicc;
	r_cgiEnv = new cgicc::CgiEnvironment(r_cgi->getEnvironment());
}

RequestModule::~RequestModule() {
	delete r_cgi;
	delete r_cgiEnv;
}


}}} // clever::packages::web
