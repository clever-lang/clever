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

#include <cstdlib>
#include "compiler/value.h"
#include "compiler/symboltable.h"
#include "modules/std/os/os.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std {

namespace os {

/**
 * system(string command)
 * Calls a command and returns the exit code.
 */
static CLEVER_FUNCTION(system) {
	retval->setInteger(::system(args->at(0)->getString().c_str()));
}

} // namespace io

/**
 * Initializes Standard module
 */
void OSModule::init() throw() {
	using namespace os;

	addFunction(new Function("system", &CLEVER_FUNC_NAME(system), CLEVER_INT))
		->addArg("command", CLEVER_STR);
}

}}} // clever::packages::std
