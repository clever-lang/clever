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
#ifdef CLEVER_WIN32
#include <direct.h>
#include <windows.h>
#define PATH_MAX MAX_PATH
#else
#include <dirent.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#endif
#include "compiler/value.h"
#include "modules/std/sys/sys.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std {

namespace sys {

/**
 * Int system(string command)
 * Calls a command and returns the exit code.
 */
static CLEVER_FUNCTION(system) {
	CLEVER_RETURN_INT(::system(CLEVER_ARG_STR(0).c_str()));
}

/**
 * Void putenv(String env)
 * Sets an environment variable
 */
static CLEVER_FUNCTION(putenv) {
    ::putenv(const_cast<char*>(CLEVER_ARG_STR(0).c_str()));
}

/**
 * String getenv(String env)
 * Gets an environment variable
 */
static CLEVER_FUNCTION(getenv) {
	const char* ret = ::getenv(const_cast<char*>(CLEVER_ARG_STR(0).c_str()));

	CLEVER_RETURN_STR(CSTRING(ret ? ret : ""));
}

/**
 * String getcwd()
 * Gets the current working directory
 */
static CLEVER_FUNCTION(getcwd) {
	char temp[PATH_MAX];
    const char* path = ::getcwd(temp, PATH_MAX);

	CLEVER_RETURN_STR(CSTRING(path ? path : ""));
}

/**
 * String argv(Int i)
 * Get i-th argv value
 */
static CLEVER_FUNCTION(argv) {
	size_t i = static_cast<size_t>(CLEVER_ARG_INT(0));

	if (i >= (size_t)*g_clever_argc) {
		CLEVER_RETURN_STR(CSTRING(""));
	} else {
		CLEVER_RETURN_STR(CSTRING((*g_clever_argv)[i]));
	}
}

/**
 * Int argc()
 * Get argc value
 */
static CLEVER_FUNCTION(argc) {
	CLEVER_RETURN_INT(*g_clever_argc);
}

/**
 * Void sleep(Int time)
 * Sleep for 'time' milliseconds.
 */
static CLEVER_FUNCTION(sleep) {
	int time = static_cast<int>(CLEVER_ARG_INT(0));

#ifdef CLEVER_WIN32
	SleepEx(time, false);
#else
	usleep(time * 1000);
#endif
}

} // namespace os

/**
 * Initializes Standard module
 */
void SYSModule::init() {
	addFunction(new Function("system", &CLEVER_NS_FNAME(sys, system), CLEVER_INT))
		->addArg("command", CLEVER_STR);

	addFunction(new Function("putenv", &CLEVER_NS_FNAME(sys, putenv), CLEVER_VOID))
		->addArg("env", CLEVER_STR);

	addFunction(new Function("getenv", &CLEVER_NS_FNAME(sys, getenv), CLEVER_STR))
		->addArg("var", CLEVER_STR);

	addFunction(new Function("getcwd", &CLEVER_NS_FNAME(sys, getcwd), CLEVER_STR));

	addFunction(new Function("argc", &CLEVER_NS_FNAME(sys, argc), CLEVER_INT));

	addFunction(new Function("argv", &CLEVER_NS_FNAME(sys, argv), CLEVER_STR))
		->addArg("i", CLEVER_INT);

	addFunction(new Function("sleep", &CLEVER_NS_FNAME(sys, sleep), CLEVER_VOID))
		->addArg("time", CLEVER_INT);
}

}}} // clever::packages::std
