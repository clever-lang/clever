/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_REQUEST_H
#define CLEVER_STD_FCGI_REQUEST_H

#include <map>
#include <iostream>
#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

#define CLEVER_FCGI_TYPE FCGX_Request*
#define CLEVER_FCGI_CAST(what) (CLEVER_FCGI_TYPE) what
#define CLEVER_FCGI_THIS() CLEVER_FCGI_CAST(CLEVER_THIS()->getObj())

class Request : public Type {
public:
	::std::map< ::std::string, ::std::string>* env;
	::std::map< ::std::string, ::std::string>* head;
	::std::map< ::std::string, ::std::string>* cookie;
	::std::map< ::std::string, ::std::string>* params;

	Request() : Type(CSTRING("Request")) {
		env = new ::std::map< ::std::string, ::std::string>();
		head = new ::std::map< ::std::string, ::std::string>();
		cookie = new ::std::map< ::std::string, ::std::string>();
		params = new ::std::map< ::std::string, ::std::string>();
	}

	~Request() {
		delete env;
		delete head;
		delete cookie;
		delete params;
	}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD_D(accept);
	CLEVER_METHOD_D(finish);
	CLEVER_METHOD_D(print);
	CLEVER_METHOD_D(flush);

	CLEVER_METHOD_D(getServer);
	CLEVER_METHOD_D(getParam);
	CLEVER_METHOD_D(getHeader);
	CLEVER_METHOD_D(getCookie);
	
	CLEVER_METHOD_D(getParams);
	CLEVER_METHOD_D(getHeaders);
	CLEVER_METHOD_D(getCookies);

	CLEVER_METHOD_D(debug);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_REQUEST_H
