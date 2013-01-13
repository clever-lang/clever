/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FCGI_H
#define CLEVER_STD_FCGI_H

#include <stdlib.h>
#ifdef _WIN32
#include <process.h>
#else
#include <unistd.h>
extern char ** environ;
#endif
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

#include "core/module.h"

#define CLEVER_FCGI_PAIR(k, v) ::std::pair< ::std::string, ::std::string>(k, v)
#define CLEVER_FCGI_MAP	::std::map< ::std::string, ::std::string>
#define CLEVER_FCGI_ITERATOR CLEVER_FCGI_MAP::const_iterator
#define CLEVER_FCGI_NULL(k) CLEVER_FCGI_PAIR(k, ::std::string(""))
#define CLEVER_FCGI_FIND(m, k) m->find(k)
#define CLEVER_FCGI_END(m) m->end()
#define CLEVER_FCGI_FETCH(f) CSTRING(f->second)

namespace clever { namespace packages { namespace std {

/// Standard FCGI Module
class FCGIModule : public Module {
public:
	FCGIModule()
		: Module("fcgi") { }

	~FCGIModule() {
	}
		
	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(FCGIModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FCGI_H
