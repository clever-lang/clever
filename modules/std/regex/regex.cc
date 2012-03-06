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
 */

#include <pcrecpp.h>
#include "modules/std/regex/regex.h"
#include "modules/std/regex/pcre.h"

namespace clever { namespace packages { namespace std {

Type* regex::g_regex_type;

void Regex::init() {
	regex::g_regex_type = new regex::Pcre();

	addClass(regex::g_regex_type);

	/**
	 * Module constants
	 */
	addConstant(CSTRING("DOTALL"),    new Value(int64_t(PCRE_DOTALL)));
	addConstant(CSTRING("MULTILINE"), new Value(int64_t(PCRE_MULTILINE)));
	addConstant(CSTRING("CASELESS"),  new Value(int64_t(PCRE_CASELESS)));
	addConstant(CSTRING("UTF8"),      new Value(int64_t(PCRE_UTF8)));
	addConstant(CSTRING("UNGREEDY"),  new Value(int64_t(PCRE_UNGREEDY)));

}

}}} // clever::packages:std
