/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_SERVER_H
#define CLEVER_STD_FCGI_SERVER_H

#include <map>
#include <iostream>
#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

class Server : public Type {
public:
	class RequestData {
	public:
		CLEVER_FCGI_MAP* env;
		CLEVER_FCGI_MAP* head;
		CLEVER_FCGI_MAP* cookie;
		CLEVER_FCGI_MAP* params;
	
		RequestData() {
			env = new CLEVER_FCGI_MAP();
			head = new CLEVER_FCGI_MAP();
			cookie = new CLEVER_FCGI_MAP();
			params = new CLEVER_FCGI_MAP();
		}

		~RequestData() {
			delete env;
			delete head;
			delete cookie;
			delete params;
		}
		
		void clear() {
			env->clear();
			head->clear();
			cookie->clear();
			params->clear();
		}
	};

	class ResponseData {
	public:
		CLEVER_FCGI_MAP* head;
		CLEVER_FCGI_MAP* cookie;
		bool body;		
		
		ResponseData() {
			head = new CLEVER_FCGI_MAP();
			cookie = new CLEVER_FCGI_MAP();
			body = false;
		}

		~ResponseData() {
			delete head;
			delete cookie;
		}

		void setBody(bool flag) 	{ body = flag; }
		bool inBody()				{ return body; }

		void clear() {
			head->clear();
			cookie->clear();
			setBody(false);
		}
	};

	ResponseData* out;
	RequestData* in;
	
	Server() : Type(CSTRING("Server")) {
		in = new RequestData();
		out = new ResponseData();
	}

	~Server() {
		delete in;
		delete out;
	}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(accept);
	CLEVER_METHOD(finish);
	CLEVER_METHOD(print);
	CLEVER_METHOD(flush);

	CLEVER_METHOD(getEnvironment);
	CLEVER_METHOD(getParam);
	CLEVER_METHOD(getHeader);
	CLEVER_METHOD(getCookie);
	
	CLEVER_METHOD(getParams);
	CLEVER_METHOD(getHeaders);
	CLEVER_METHOD(getCookies);

	CLEVER_METHOD(setHeader);
	CLEVER_METHOD(setCookie);

	CLEVER_METHOD(debug);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_SERVER_H
