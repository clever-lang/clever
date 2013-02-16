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

namespace clever { namespace modules { namespace std {

const size_t CLEVER_FCGI_STDIN_MAX = 1000000;

// Server.new()
// Setup the process for responding to FCGI requests by creating a new Request object
TypeObject* Server::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	ServerObject* server = new ServerObject;

	if (server->request) {
		if (FCGX_InitRequest(server->request, 0, 0) == 0) {
			return server;
		}
		delete server;
	}
	return NULL;
}

void Server::deallocData(void* data)
{
	delete static_cast<ServerObject*>(data);
}

// Server constructor
CLEVER_METHOD(Server::ctor)
{
	if (!clever_check_no_args()) {
		return;
	}

	result->setObj(this, allocData(&args));
}

// Server.accept()
// Accepts the next FCGI Request
CLEVER_METHOD(Server::accept)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
		result->setBool(false);
		return;
	}

	if (!clever_check_no_args()) {
		return;
	}

	in->clear();
	out->clear();

	if (FCGX_Accept(&request->in, &request->out, &request->err, &request->envp) != 0) {
		result->setBool(false);
		return;
	}

	const char* const* n = request->envp;
	if (!n) {
		result->setBool(false);
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
	result->setBool(true);
}

// Server.print(string text, [...])
// Prints to the FCGI standard output
CLEVER_METHOD(Server::print)
{
	if (!clever_check_args("s*")) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (request) {
		if (!out->inBody()) {
			FCGX_PutStr("Content-Type: text/html\n\n", sizeof("Content-Type: text/html\n\n"), request->out);
			out->setBody(true);
		}

		for (size_t arg = 0; arg < args.size(); arg++) {
			if (args[arg]->isStr()) {
				FCGX_PutStr(args[arg]->getStr()->c_str(),
					args[arg]->getStr()->size(), request->out);
			}
		}
	}
	result->setNull();
}

// Server.flush()
// Flushes the FCGI standard output buffer
CLEVER_METHOD(Server::flush)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!clever_check_no_args()) {
		return;
	}

	if (request) {
		result->setBool((FCGX_FFlush(request->out) == 0));
	} else {
		result->setNull();
	}
}

// Server.finish()
// Closes the FCGI standard output, disconnecting the client
CLEVER_METHOD(Server::finish)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!clever_check_no_args()) {
		return;
	}

	if (request) {
		result->setBool((FCGX_FClose(request->out) == 0));
	} else {
		result->setNull();
	}
}

// Server.getEnvironment([string param])
// Fetches environment information, returns map when no param specified
CLEVER_METHOD(Server::getEnvironment)
{
	if (!clever_check_args("|s")) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
		return;
	}

	if (args.size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->env, args[0]->getStr()->c_str());

		if (it != CLEVER_FCGI_END(in->env)) {
			result->setStr(CLEVER_FCGI_FETCH(it));
			return;
		}
		result->setNull();
	} else {
		::std::vector<Value*> mapping;

		CLEVER_FCGI_ITERATOR item(in->env->begin());
		CLEVER_FCGI_ITERATOR last(in->env->end());

		while (item != last) {
			mapping.push_back(new Value(CSTRING(item->first)));
			mapping.push_back(new Value(CSTRING(item->second)));
			++item;
		}

		result->setObj(CLEVER_MAP_TYPE, CLEVER_MAP_TYPE->allocData(&mapping));
	}
}

// Server.getParam(string param)
// Fetches a request parameter
CLEVER_METHOD(Server::getParam)
{
	if (!clever_check_args("s")) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
		result->setNull();
		return;
	}

	if (in->params->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->params, args[0]->getStr()->c_str());

		if (it != CLEVER_FCGI_END(in->params)) {
			result->setStr(CLEVER_FCGI_FETCH(it));
			return;
		}
	}

	result->setNull();
}

// Server.getParam(string param)
// Fetches a request header (all upper-case, eg HOST not host, CONTENT_TYPE not content-type)
CLEVER_METHOD(Server::getHeader)
{
	if (!clever_check_args("s")) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
		result->setNull();
		return;
	}

	if (in->head->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->head, args[0]->getStr()->c_str());
		if (it != CLEVER_FCGI_END(in->head)) {
			result->setStr(CLEVER_FCGI_FETCH(it));
			return;
		}
	}
	result->setNull();
}

// Server.getCookie(string param)
// Fetches a request cookie
CLEVER_METHOD(Server::getCookie)
{
	if (!clever_check_args("s")) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
		return;
	}

	if (in->cookie->size()) {
		CLEVER_FCGI_ITERATOR it = CLEVER_FCGI_FIND(in->cookie, args[0]->getStr()->c_str());

		if ((it != CLEVER_FCGI_END(in->cookie))) {
			result->setStr(CLEVER_FCGI_FETCH(it));
			return;
		}
	}
	result->setNull();
}

// Server.debug()
// Prints the request environment to the FCGI standard output
CLEVER_METHOD(Server::debug)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
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
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
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

	result->setObj(CLEVER_MAP_TYPE, CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.getHeaders()
// Will return a Map of request headers
CLEVER_METHOD(Server::getHeaders)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
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

	result->setObj(CLEVER_MAP_TYPE, CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.getCookies()
// Will return a Map of request cookies
CLEVER_METHOD(Server::getCookies)
{
	if (!clever_check_no_args()) {
		return;
	}

	ServerObject* sobj = CLEVER_GET_OBJECT(ServerObject*, CLEVER_THIS());
	FCGX_Request* request = sobj->request;

	if (!request) {
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

	result->setObj(CLEVER_MAP_TYPE, CLEVER_MAP_TYPE->allocData(&mapping));
}

// Server.setHeader(string key, string value)
// Sets a response header
CLEVER_METHOD(Server::setHeader)
{
	if (!clever_check_args("ss")) {
		return;
	}

	out->head->insert(CLEVER_FCGI_PAIR(args[0]->getStr()->c_str(), args[1]->getStr()->c_str()));
}

// Server.setCookie(string key, string value, [string path, [string expires]])
// Sets a cookie to send with the response
CLEVER_METHOD(Server::setCookie)
{
	if (!clever_check_args("ss")) {
		return;
	}

	out->cookie->insert(CLEVER_FCGI_PAIR(args[0]->getStr()->c_str(), args[1]->getStr()->c_str()));
}

CLEVER_TYPE_INIT(Server::init)
{
	setConstructor((MethodPtr)&Server::ctor);

	// IO
	addMethod(new Function("accept", (MethodPtr)&Server::accept));
	addMethod(new Function("print",  (MethodPtr)&Server::print));
	addMethod(new Function("flush",  (MethodPtr)&Server::flush));
	addMethod(new Function("finish", (MethodPtr)&Server::finish));

	// Util
	addMethod(new Function("getEnvironment", (MethodPtr)&Server::getEnvironment));
	addMethod(new Function("getParam",       (MethodPtr)&Server::getParam));
	addMethod(new Function("getHeader",      (MethodPtr)&Server::getHeader));
	addMethod(new Function("getCookie",      (MethodPtr)&Server::getCookie));

	addMethod(new Function("getParams",  (MethodPtr)&Server::getParams));
	addMethod(new Function("getHeaders", (MethodPtr)&Server::getHeaders));
	addMethod(new Function("getCookies", (MethodPtr)&Server::getCookies));

	addMethod(new Function("setHeader", (MethodPtr)&Server::setHeader));
	addMethod(new Function("setCookie", (MethodPtr)&Server::setCookie));

	// Debug Environment
	addMethod(new Function("debug",		(MethodPtr)&Server::debug));
}

}}} // clever::modules::std
