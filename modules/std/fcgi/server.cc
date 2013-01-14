/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "types/type.h"
#include "types/native_types.h"
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/fcgi/fcgi.h"
#include "modules/std/fcgi/server.h"

namespace clever { namespace packages { namespace std {

const size_t CLEVER_FCGI_STDIN_MAX = 1000000;

void Server::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void Server::dump(const void* data, ::std::ostream& out) const
{
	Value::DataValue* dvalue = (Value::DataValue*)data;
	if (dvalue) {
		FCGX_Request* uvalue = CLEVER_GET_OBJECT(FCGX_Request*, dvalue->obj);
		if (uvalue) {
			/* do something here, the user has printed a request */
		}
	}
}

// Server.new()
// Setup the process for responding to FCGI requests by creating a new Request object
void* Server::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	FCGX_Request* request = new FCGX_Request;
	if (request) {
		if (FCGX_InitRequest(request, 0, 0) == 0) {
			return request;
		}
		delete request;
	}
	return NULL;
}

void Server::deallocData(void* data)
{
	delete static_cast<FCGX_Request*>(data);
}

// Server.accept()
// Accepts the next FCGI Request
CLEVER_METHOD(Server::accept)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_BOOL(false);
		return;
	}

	in->clear();
	out->clear();

	if (FCGX_Accept(&request->in, &request->out, &request->err, &request->envp) != 0) {
		CLEVER_RETURN_BOOL(false);
		return;
	}

	const char* const* n = request->envp;
	if (!n) {
		CLEVER_RETURN_BOOL(false);
		return;
	}

	while (*n) {
		::std::string l(*n);
		::std::string k(l.substr(0, l.find_first_of("=")));
		::std::string v(l.substr(k.length()+1));

		switch (k.at(0)) {
			case 'X':
			case 'H':
				if (k.find("HTTP_COOKIE") == 0) {
					::std::string name;
					::std::string data;
					bool inv = false;
					
					for (size_t position = 0; position < v.length(); position++) {
						switch(v.at(position)){								
							case '=': inv=true; break;

							case ' ':
							case ';': {
								inv=false;
								if (name.size() && data.size()) {
									in->cookie->insert(CLEVER_FCGI_PAIR(name, data));
								}
								name.clear();
								data.clear();
							} break;

							default:
								if(inv) {
									data += v.at(position);									
								} else {
									name += v.at(position);
								}
							break;
						}
					}
					
					if (name.size() && data.size()) {
						in->cookie->insert(CLEVER_FCGI_PAIR(name, data));
					}			
				} else {
					if (k.find("HTTP") == 0) {
						in->head->insert(CLEVER_FCGI_PAIR(k.substr(5), v));
					} else {
						in->head->insert(CLEVER_FCGI_PAIR(k, v));
					}
				}
				break;

			default:
				if (k.find("QUERY_STRING") == 0) {
					size_t next = v.find("&"), last = 0;

					if (next) {
						do {
							::std::string chunk(v.substr(last, next));
							if (chunk.size()) {
								size_t split = chunk.find("=");

								if (split) {
									::std::string l(chunk.substr(0, split));
									::std::string r(chunk.substr(split+1, chunk.size()));
									in->params->insert(CLEVER_FCGI_PAIR(l, r));
								} else {
									in->params->insert(CLEVER_FCGI_NULL(chunk));
								}
							}
						} while((last=(next+1)) && (next = v.find("&", next+1)));
					} else {
						in->env->insert(CLEVER_FCGI_PAIR(k, v));
					}
				} else {
					in->env->insert(CLEVER_FCGI_PAIR(k, v));
				}
				break;
		}
		++n;
	}
	CLEVER_RETURN_BOOL(true);
}

// Server.print(string text, [...])
// Prints to the FCGI standard output
CLEVER_METHOD(Server::print)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (request) {
		if (!out->inBody()) {
			FCGX_PutStr("Content-Type: text/html\n\n", sizeof("Content-Type: text/html\n\n"), request->out);
			out->setBody(true);
		}

		for (size_t arg = 0; arg < args.size(); arg++) {
			if (CLEVER_ARG_TYPE(arg) == CLEVER_STR_TYPE) {
				FCGX_PutStr(CLEVER_ARG_CSTR(arg)->c_str(),
					CLEVER_ARG_CSTR(arg)->size(), request->out);
			}
		}
	}
	CLEVER_RETURN_NULL();
}

// Server.flush()
// Flushes the FCGI standard output buffer
CLEVER_METHOD(Server::flush)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (request) {
		CLEVER_RETURN_BOOL((FCGX_FFlush(request->out) == 0));
	} else {
		CLEVER_RETURN_NULL();
	}
}

// Server.finish()
// Closes the FCGI standard output, disconnecting the client
CLEVER_METHOD(Server::finish)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (request) {
		CLEVER_RETURN_BOOL((FCGX_FClose(request->out) == 0));
	} else {
		CLEVER_RETURN_NULL();
	}
}

// Server.getEnvironment([string param])
// Fetches environment information, returns map when no param specified
CLEVER_METHOD(Server::getEnvironment)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	if (args.size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->env, CLEVER_ARG_PSTR(0));

		if (it != CLEVER_FCGI_END(in->env)) {
			CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
			return;
		}
		CLEVER_RETURN_NULL();
	} else {
		::std::vector<Value*> mapping;

		CLEVER_FCGI_ITERATOR item(in->env->begin());
		CLEVER_FCGI_ITERATOR last(in->env->end());

		while (item != last) {
			mapping.push_back(new Value(CSTRING(item->first)));
			mapping.push_back(new Value(CSTRING(item->second)));
			++item;
		}

		CLEVER_RETURN_MAP(CLEVER_MAP_TYPE->allocData(&mapping));
	}
}

// Server.getParam(string param)
// Fetches a request parameter
CLEVER_METHOD(Server::getParam)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	if (!clever_check_args("s")) {
		return;
	}

	if (in->params->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->params, CLEVER_ARG_PSTR(0));

		if (it != CLEVER_FCGI_END(in->params)) {
			CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
			return;
		}
	}
	CLEVER_RETURN_NULL();
}

// Server.getParam(string param)
// Fetches a request header (all upper-case, eg HOST not host, CONTENT_TYPE not content-type)
CLEVER_METHOD(Server::getHeader)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	if (!clever_check_args("s")) {
		return;
	}

	if (in->head->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->head, CLEVER_ARG_PSTR(0));
		if (it != CLEVER_FCGI_END(in->head)) {
			CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
			return;
		}
	}
	CLEVER_RETURN_NULL();
}

// Server.getCookie(string param)
// Fetches a request cookie
CLEVER_METHOD(Server::getCookie)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	if (!clever_check_args("s")) {
		return;
	}

	if (in->cookie->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->cookie, CLEVER_ARG_PSTR(0));

		if ((it != CLEVER_FCGI_END(in->cookie))) {
			CLEVER_RETURN_STR(CLEVER_FCGI_FETCH(it));
			return;
		}
	}
	CLEVER_RETURN_NULL();
}

// Server.debug()
// Prints the request environment to the FCGI standard output
CLEVER_METHOD(Server::debug)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	const char* const* next = request->envp;

	if (next) {
		FCGX_PutStr("<pre>\n", sizeof("<pre>\n"), request->out);
		while (*next) {
			FCGX_PutStr(*next, strlen(*next), request->out);
			FCGX_PutStr("\n", sizeof("\n"), request->out);
			++next;
		}
		FCGX_PutStr("</pre>\n", sizeof("</pre>\n"), request->out);
	}
}

// Server.getParams()
// Will return a Map of request parameters
CLEVER_METHOD(Server::getParams)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	::std::vector<Value*> mapping;

	CLEVER_FCGI_ITERATOR item(in->params->begin());
	CLEVER_FCGI_ITERATOR last(in->params->end());

	while (item != last) {
		mapping.push_back(new Value(CSTRING(item->first)));
		mapping.push_back(new Value(CSTRING(item->second)));
		++item;
	}

	CLEVER_RETURN_MAP(CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.getHeaders()
// Will return a Map of request headers
CLEVER_METHOD(Server::getHeaders)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	::std::vector<Value*> mapping;

	CLEVER_FCGI_ITERATOR item(in->head->begin());
	CLEVER_FCGI_ITERATOR last(in->head->end());

	while (item != last) {
		mapping.push_back(new Value(CSTRING(item->first)));
		mapping.push_back(new Value(CSTRING(item->second)));
		++item;
	}

	CLEVER_RETURN_MAP(CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.getCookies()
// Will return a Map of request cookies
CLEVER_METHOD(Server::getCookies)
{
	FCGX_Request* request = CLEVER_GET_OBJECT(FCGX_Request*, CLEVER_THIS());

	if (!request) {
		CLEVER_RETURN_NULL();
		return;
	}

	::std::vector<Value*> mapping;

	CLEVER_FCGI_ITERATOR item(in->cookie->begin());
	CLEVER_FCGI_ITERATOR last(in->cookie->end());

	while (item != last) {
		mapping.push_back(new Value(CSTRING(item->first)));
		mapping.push_back(new Value(CSTRING(item->second)));
		++item;
	}

	CLEVER_RETURN_MAP(CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.setHeader(string key, string value)
// Sets a response header
CLEVER_METHOD(Server::setHeader) 
{
	if (!clever_check_args("ss")) {
		return;	
	}
	
	out->head->insert(CLEVER_FCGI_PAIR(CLEVER_ARG_PSTR(0), CLEVER_ARG_PSTR(1)));
}

// Server.setCookie(string key, string value, [string path, [string expires]])
// Sets a cookie to send with the response
CLEVER_METHOD(Server::setCookie)
{
	if (!clever_check_args("ss")) {
		return;
	}

	out->cookie->insert(CLEVER_FCGI_PAIR(CLEVER_ARG_PSTR(0), CLEVER_ARG_PSTR(1)));
}

CLEVER_TYPE_INIT(Server::init)
{
	// IO
	addMethod(CSTRING("accept"), (MethodPtr)&Server::accept);
	addMethod(CSTRING("print"),  (MethodPtr)&Server::print);
	addMethod(CSTRING("flush"),  (MethodPtr)&Server::flush);
	addMethod(CSTRING("finish"), (MethodPtr)&Server::finish);

	// Util
	addMethod(CSTRING("getEnvironment"), (MethodPtr)&Server::getEnvironment);
	addMethod(CSTRING("getParam"),       (MethodPtr)&Server::getParam);
	addMethod(CSTRING("getHeader"),      (MethodPtr)&Server::getHeader);
	addMethod(CSTRING("getCookie"),      (MethodPtr)&Server::getCookie);	
	
	addMethod(CSTRING("getParams"),  (MethodPtr)&Server::getParams);
	addMethod(CSTRING("getHeaders"), (MethodPtr)&Server::getHeaders);
	addMethod(CSTRING("getCookies"), (MethodPtr)&Server::getCookies);

	addMethod(CSTRING("setHeader"), (MethodPtr)&Server::setHeader);
	addMethod(CSTRING("setCookie"), (MethodPtr)&Server::setCookie);

	// Debug Environment
	addMethod(CSTRING("debug"),		(MethodPtr)&Server::debug);
}

}}} // clever::packages::std
