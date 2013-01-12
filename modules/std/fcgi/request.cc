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
#include "types/native_types.h"
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
	fcgi.print("Hello World\n");
	fcgi.debug();
	fcgi.finish();
}

fcgi.finish();
*/
namespace clever { namespace packages { namespace std {

#define CLEVER_FCGI_STDIN_MAX 1000000
#define CLEVER_FCGI_DEFAULT_SOCK "/var/run/fcgi.sock"
#define CLEVER_FCGI_DEFAULT_BACKLOG 0

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

// @TODO spawn-fcgi is the only way to run right now DO NOT PASS arguments to constructor method
void* Request::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	FCGX_Request* request = new FCGX_Request;
	if (request) {
		int socket = 0;

		/* I KNOW THIS IS A BIT MESSY I AM WORKING ON IT */
		::std::cout << "[FCGI SETUP]" << ::std::endl;
		if (args->size()) {
			::std::cout << "[SOCKET SETUP]" << ::std::endl;
			socket = FCGX_OpenSocket(
				(args->at(0)->getType() == CLEVER_STR_TYPE) ? 
					args->at(0)->getStr()->c_str() : CLEVER_FCGI_DEFAULT_SOCK,
				(args->size() > 1 && args->at(1)->getType() == CLEVER_INT_TYPE) ? 
					args->at(1)->getInt() : CLEVER_FCGI_DEFAULT_BACKLOG
			);
			if (socket) {
				::std::cout << "[SOCKET OPENED (" << socket << ")]" << ::std::endl;
			} else ::std::cout << "[SOCKET FAILED]" << ::std::endl;
		} else FCGX_Init();
		
		if (FCGX_InitRequest(
				request, 
				socket, 
				0
			) == 0) {
			::std::cout << "[FCGI READY]" << ::std::endl;
			return request;
		} else ::std::cout << "[FCGI FAILED]" << ::std::endl;
		delete request;
	}
	return NULL;
}

void Request::deallocData(void *data) {
	delete static_cast<FCGX_Request*>(data);
}

// Request.accept()
// Accepts the next FCGI Request
CLEVER_METHOD(Request::accept)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		CLEVER_RETURN_BOOL((FCGX_Accept(&request->in, &request->out, &request->err, &request->envp) == 0));
	} else {
		CLEVER_RETURN_BOOL(false);
	}
}

// Request.print(string text, [...])
// Prints to the FCGI standard output
CLEVER_METHOD(Request::print) {
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		for (size_t arg = 0; arg < CLEVER_ARG_COUNT(); arg++) {
			if (CLEVER_ARG_TYPE(arg) == CLEVER_STR_TYPE) {
				FCGX_PutStr(CLEVER_ARG_CSTR(arg)->c_str(), CLEVER_ARG_CSTR(arg)->size(), request->out);
			}
		}
	}
}

// Request.flush()
// Flushes the FCGI standard output buffer
CLEVER_METHOD(Request::flush) {
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		CLEVER_RETURN_BOOL((FCGX_FFlush(request->out) == 0));
	} else {
		CLEVER_RETURN_NULL();
	}	
}

// Request.finish()
// Closes the FCGI standard output, disconnecting the client
CLEVER_METHOD(Request::finish)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		CLEVER_RETURN_BOOL((FCGX_FClose(request->out) == 0));
	} else {
		CLEVER_RETURN_NULL();
	}
}

// Request.getParam(string param)
// Fetches a FCGI parameter from the environment
// @TODO params will correspect to get/post variables this is temporary
CLEVER_METHOD(Request::getParam)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (clever_check_args("s")) {
			CLEVER_RETURN_CSTR(CSTRING(FCGX_GetParam(CLEVER_ARG_PSTR(0), request->envp)));
		} else {
			CLEVER_RETURN_NULL();
		}
	}
}

// Request.debug()
// Prints the request environment to the FCGI standard output
CLEVER_METHOD(Request::debug)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		const char* const * next = request->envp;
		if (next) {
			FCGX_PutStr("<pre>\n", sizeof("<pre>\n"), request->out);
			while(*next) {
				FCGX_PutStr(*next, strlen(*next), request->out);
				FCGX_PutStr("\n", sizeof("\n"), request->out);
				++next;
			}
			FCGX_PutStr("</pre>\n", sizeof("</pre>\n"), request->out);
		}
	}

	CLEVER_RETURN_NULL();
}

// Request.getParams()
// Will return a Map/Array of parameters
CLEVER_METHOD(Request::getParams)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		
	}
	CLEVER_RETURN_NULL();
}

CLEVER_TYPE_INIT(Request::init)
{
	/* IO */
	addMethod(CSTRING("accept"), (MethodPtr)&Request::accept);
	addMethod(CSTRING("print"), (MethodPtr)&Request::print);
	addMethod(CSTRING("flush"), (MethodPtr)&Request::flush);
	addMethod(CSTRING("finish"), (MethodPtr)&Request::finish);

	/* Util */
	addMethod(CSTRING("getParam"), (MethodPtr)&Request::getParam);
	addMethod(CSTRING("getParams"), (MethodPtr)&Request::getParams);
	
	/* Debug Environment */
	addMethod(CSTRING("debug"),		(MethodPtr)&Request::debug);
}

}}} // clever::packages::std
