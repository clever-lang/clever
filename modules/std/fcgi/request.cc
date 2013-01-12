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
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/request.h"

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
		
		env->clear();
		head->clear();
		params->clear();
		cookie->clear();

		if ((FCGX_Accept(&request->in, &request->out, &request->err, &request->envp) == 0)) {
			{
				const char* const * n = request->envp;
				if (n) {
					while(*n) {
						::std::string l(*n);
						::std::string k(l.substr(0, l.find_first_of("=")));
						::std::string v(l.substr(k.length()+1));

						switch (k.at(0)) {
							case 'X':
							case 'H': {
								if ((k.find("HTTP_COOKIE") == 0)) {
									/** process cookies **/
									::std::cout << "COOKIE[" << v << "]" << ::std::endl;					
								} else {
									head->insert(CLEVER_FCGI_PAIR(k.substr(5), v));
								}
							} break;

							default: {
								if ((k.find("QUERY_STRING") == 0)) {
									size_t last = 0, next = v.find("&");
									if (next) do {
										::std::string chunk(v.substr(last, next));
										if (chunk.size()) {
											size_t split = chunk.find("=");
											if (split) {
												::std::string l(chunk.substr(0, split));
												::std::string r(chunk.substr(split+1, chunk.size()));
												params->insert(CLEVER_FCGI_PAIR(l, r));
											} else {
												params->insert(CLEVER_FCGI_NULL(chunk));
											}
										}
									} while((last=(next+1)) && (next = v.find("&", next+1)));
								} else {
									env->insert(CLEVER_FCGI_PAIR(k, v));
								}
							} break;
						}
						++n;
					}
				}
			}
			CLEVER_RETURN_BOOL(true);
		} else {
			CLEVER_RETURN_BOOL(false);
		}		
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

// Request.getServer(string param)
// Fetches a server environment variable
CLEVER_METHOD(Request::getServer)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (clever_check_args("s")) {
			if (env->size()) {
				CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(env, CLEVER_ARG_PSTR(0));
				if (it != CLEVER_FCGI_END(env)) {
					CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
				} else CLEVER_RETURN_NULL();
			} else CLEVER_RETURN_NULL();
		} else {
			CLEVER_RETURN_NULL();
		}
	}
}

// Request.getParam(string param)
// Fetches a request parameter
CLEVER_METHOD(Request::getParam)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (clever_check_args("s")) {
			if (params->size()) {
				CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(params, CLEVER_ARG_PSTR(0));
				if (it != CLEVER_FCGI_END(params)) {
					CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
				} else CLEVER_RETURN_NULL();
			} else CLEVER_RETURN_NULL();
		} else {
			CLEVER_RETURN_NULL();
		}
	}
}

// Request.getParam(string param)
// Fetches a request header (all upper-case, eg HOST not host, CONTENT_TYPE not content-type)
CLEVER_METHOD(Request::getHeader)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (clever_check_args("s")) {
			if (head->size()) {
				CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(head, CLEVER_ARG_PSTR(0));
				if (it != CLEVER_FCGI_END(head)) {
					CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
				} else CLEVER_RETURN_NULL();
			} else CLEVER_RETURN_NULL();
		} else {
			CLEVER_RETURN_NULL();
		}
	}
}

// Request.getCookie(string param)
// Fetches a request cookie
CLEVER_METHOD(Request::getCookie)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		if (clever_check_args("s")) {
			if (cookie->size()) {
				CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(cookie, CLEVER_ARG_PSTR(0));
				if ((it != CLEVER_FCGI_END(cookie))) {
					CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
				} else CLEVER_RETURN_NULL();
			} else CLEVER_RETURN_NULL();
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
// Will return a Map/Array of request parameters
CLEVER_METHOD(Request::getParams)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		
	}
	CLEVER_RETURN_NULL();
}

// Request.getHeaders()
// Will return a Map/Array of request headers
CLEVER_METHOD(Request::getHeaders)
{
	CLEVER_FCGI_TYPE request = CLEVER_FCGI_THIS();
	if (request) {
		
	}
	CLEVER_RETURN_NULL();
}

// Request.getCookies()
// Will return a Map/Array of request cookies
CLEVER_METHOD(Request::getCookies)
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
	addMethod(CSTRING("getServer"), (MethodPtr)&Request::getServer);
	addMethod(CSTRING("getParam"), (MethodPtr)&Request::getParam);
	addMethod(CSTRING("getHeader"), (MethodPtr)&Request::getHeader);
	addMethod(CSTRING("getCookie"), (MethodPtr)&Request::getCookie);

	addMethod(CSTRING("getParams"), (MethodPtr)&Request::getParams);
	addMethod(CSTRING("getHeaders"), (MethodPtr)&Request::getHeaders);
	addMethod(CSTRING("getCookies"), (MethodPtr)&Request::getCookies);
	
	/* Debug Environment */
	addMethod(CSTRING("debug"),		(MethodPtr)&Request::debug);
}

}}} // clever::packages::std
