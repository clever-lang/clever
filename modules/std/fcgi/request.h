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

class Request : public Type {
public:
	CLEVER_FCGI_MAP* env;
	CLEVER_FCGI_MAP* head;
	CLEVER_FCGI_MAP* cookie;
	CLEVER_FCGI_MAP* params;

	Request() : Type(CSTRING("Request")) {
		env = new CLEVER_FCGI_MAP();
		head = new CLEVER_FCGI_MAP();
		cookie = new CLEVER_FCGI_MAP();
		params = new CLEVER_FCGI_MAP();
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

	CLEVER_METHOD_D(getEnvironment);
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
