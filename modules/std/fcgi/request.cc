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

void* Request::allocData(CLEVER_TYPE_CTOR_ARGS) const {
	FCGX_Request* request = new FCGX_Request;
	if (request) {
		int socket;

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

CLEVER_METHOD(Request::accept)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		CLEVER_RETURN_BOOL((FCGX_Accept(&request->in, &request->out, &request->err, &request->envp) == 0));
	} else {
		CLEVER_RETURN_BOOL(false);
	}
}

CLEVER_METHOD(Request::print) {
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		for (size_t arg = 0; arg < CLEVER_ARG_COUNT(); arg++) {
			FCGX_FPrintF(request->out, CLEVER_ARG_PSTR(arg));
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
	addMethod(CSTRING("print"), (MethodPtr)&Request::print);
}

}}} // clever::packages::std
