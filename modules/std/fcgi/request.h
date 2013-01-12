/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_REQUEST_H
#define CLEVER_STD_FCGI_REQUEST_H

#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

#include <iostream>
#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace packages { namespace std {

#define CLEVER_FCGI_TYPE FCGX_Request*
#define CLEVER_FCGI_CAST(what) (CLEVER_FCGI_TYPE) what
#define CLEVER_FCGI_THIS() CLEVER_FCGI_CAST(CLEVER_THIS()->getObj())

class Request : public Type {
public:
	Request()
		: Type(CSTRING("Request")) { }

	~Request() {}

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

	CLEVER_METHOD_D(getParam);
	CLEVER_METHOD_D(getParams);

	CLEVER_METHOD_D(debug);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_REQUEST_H
