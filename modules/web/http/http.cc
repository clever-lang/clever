/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */


#include <iostream>
#include <fstream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/web/cgi/cgiclass.h"
#include "modules/web/http/http.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace web {

namespace http {

/**
 * header()
 */
static CLEVER_FUNCTION(header) {
	::std::cout<< cgicc::HTTPHTMLHeader() << ::std::endl;
}

/**
 * html()
 */
static CLEVER_FUNCTION(html) {
	::std::cout<< cgicc::html() << ::std::endl;
}

/**
 * body()
 */
static CLEVER_FUNCTION(body) {
	::std::cout<< cgicc::body() << ::std::endl;
}

/**
 * head()
 */
static CLEVER_FUNCTION(head) {
	::std::cout<< cgicc::head() << ::std::endl;
}


/*
 *String title(String)
 */
static CLEVER_FUNCTION(title) {
	::std::cout << cgicc::title(CLEVER_ARG_STR(0))<< ::std::endl;
}


} // web

/**
 * Load module data
 */
void Http::init() {
	
	addFunction(new Function("header",&CLEVER_NS_FNAME(http, header), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(0);

	addFunction(new Function("html",&CLEVER_NS_FNAME(http, html), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(0);

	addFunction(new Function("body",&CLEVER_NS_FNAME(http, body), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(0);

	addFunction(new Function("head",&CLEVER_NS_FNAME(http, head), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(0);

	addFunction(new Function("title", &CLEVER_NS_FNAME(http, title), CLEVER_VOID))
		->setVariadic()
		->setMinNumArgs(1);

}

}}} // clever::packages::web
