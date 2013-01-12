/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_RESPONSE_H
#define CLEVER_STD_FCGI_RESPONSE_H

#include <map>
#include <iostream>
#include "core/cstring.h"
#include "types/type.h"
#include "modules/std/fcgi/request.h"

namespace clever { namespace packages { namespace std {

class Response : public Type {
public:
	Request* request;
	::std::map< ::std::string, Value*>* headers;
	::std::map< ::std::string, Value*>* cookies;
	
	Response()
		: Type(CSTRING("Response")) {request = NULL; headers = NULL; cookies = NULL;}
	Response(Request* from)
		: Type(CSTRING("Response")) {request = from; headers = NULL; cookies = NULL;}

	~Response() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_RESPONSE_H
