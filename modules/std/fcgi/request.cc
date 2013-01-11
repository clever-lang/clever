/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

#include "types/type.h"
#include "modules/std/fcgi/request.h"
#include "core/value.h"
#include "core/clever.h"

/*
Here is the basic structure of FCGI programs in clever
import std.io.*;
import std.fcgi.*;

var fcgi = Request.new([address, [backlog]]);

while (fcgi.accept()) {
	fcgi.print("Content-Type: text/html\r\n");
	fcgi.print("\r\n");
	fcgi.print("Hello World");
	fcgi.finish();
}
*/
namespace clever { namespace packages { namespace std {

void Request::dump(const void *data) const {
	dump(data, ::std::cout);
}

void Request::dump(const void* data, ::std::ostream& out) const {
	Value::DataValue* dvalue = (Value::DataValue*)data;
	if (dvalue) {
		FCGX_Request* uvalue = (FCGX_Request*) dvalue->obj->getObj();
		if (uvalue) {
			/* do something here, the user has printed a request */
		}
	}
}

void* Request::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	if (args->size()) {
		FCGX_Request* request = new FCGX_Request;
		if (request) {
			/* @todo: accept argument to bind to a specific port/socket */
			if (FCGX_InitRequest(request, 0, 0)==0) {
				return request;
			}
		}
	}
	return NULL;
}

void Request::deallocData(void *data) {
	delete static_cast<FCGX_Request*>(data);
}

CLEVER_METHOD(Request::accept)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (FCGX_Accept_r(request) == 0) {
			/** setup streams */
		}
	}
}

CLEVER_METHOD(Request::finish)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		FCGX_Finish_r(request);
	}
}

CLEVER_TYPE_INIT(Request::init)
{
	addMethod(CSTRING("accept"), (MethodPtr)&Request::accept);
	addMethod(CSTRING("finish"), (MethodPtr)&Request::finish);
	
	FCGX_Init();
}

}}} // clever::packages::std
