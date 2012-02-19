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

#include "compiler/cstring.h"
#include "std_pkg.h"

namespace clever { namespace packages {

/**
 * Initializes Std package
 */
void Std::init() {
#ifdef HAVE_STD_IO
	addModule(new std::IOModule);
#endif
#ifdef HAVE_STD_MATH
	addModule(new std::Math);
#endif
#ifdef HAVE_STD_FILE
	addModule(new std::File);
#endif
#ifdef HAVE_STD_OS
	addModule(new std::OSModule);
#endif
#ifdef HAVE_STD_REFLECTION
	addModule(new std::Reflection);
#endif
#ifdef HAVE_STD_NET
	addModule(new std::NetModule);
#endif
#ifdef HAVE_STD_REGEX
	addModule(new std::Regex);
#endif
#ifdef HAVE_STD_FFI
	addModule(new std::FFI);
#endif
}


}} // clever::packages
