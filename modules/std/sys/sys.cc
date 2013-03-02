/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdlib>

#ifdef CLEVER_WIN32
# include <direct.h>
# include <windows.h>
# define PATH_MAX MAX_PATH
#else
# include <dirent.h>
# include <unistd.h>
# include <sys/resource.h>
# include <sys/time.h>
#endif
#include "core/value.h"
#include "core/driver.h"
#include "modules/std/sys/sys.h"
#include "core/native_types.h"
#include "core/modmanager.h"
#include "core/cexception.h"

#include "types/thread.h"

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

namespace clever { namespace modules { namespace std {

namespace sys {

// system(string command)
// Calls a command and returns the exit code
static CLEVER_FUNCTION(system)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	result->setInt(::system(args[0]->getStr()->c_str()));
}

// putenv(string env)
// Sets an environment variable
static CLEVER_FUNCTION(putenv)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	::putenv(const_cast<char*>(args[0]->getStr()->c_str()));
}

// getenv(string env)
// Gets an environment variable
static CLEVER_FUNCTION(getenv)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* ret = ::getenv(const_cast<char*>(args[0]->getStr()->c_str()));

	if (ret) {
		result->setStr(CSTRINGT(ret));
	} else {
		result->setStr(CSTRING(""));
	}
}

// getcwd()
// Gets the current working directory
static CLEVER_FUNCTION(getcwd)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	char temp[PATH_MAX];
	const char* path = ::getcwd(temp, PATH_MAX);

	result->setStr(CSTRING(path ? path : ""));
}

// argv(int n)
// Get n-th argv value
static CLEVER_FUNCTION(argv)
{
	if (!clever_static_check_args("i")) {
		return;
	}

	if (args[0]->getInt() >= *g_clever_argc) {
		result->setBool(false);
	} else {
		result->setStr(new StrObject((*g_clever_argv)[args[0]->getInt()]));
	}
}

// argc()
// Get argc value
static CLEVER_FUNCTION(argc)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(*g_clever_argc);
}

// sleep(int time)
// Sleep for 'time' milliseconds
static CLEVER_FUNCTION(sleep)
{
	if (!clever_static_check_args("i")) {
		return;
	}

	int time = static_cast<int>(args[0]->getInt());

#ifdef CLEVER_WIN32
	SleepEx(time, false);
#else
	usleep(time * 1000);
#endif
}

// clock()
// Returns the execution clock
static CLEVER_FUNCTION(clock)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(clock());
}

// time()
// Returns the execution time in sec
static CLEVER_FUNCTION(time)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	size_t n_threads = ThreadType::getNThreads();
	if ( n_threads == 0) {
		result->setDouble(static_cast<double>(clock()) / CLOCKS_PER_SEC);
	} else {
		result->setDouble(static_cast<double>(clock()) / n_threads / CLOCKS_PER_SEC);
	}
}

// microtime()
// Returns the unix timestamp with microseconds
static CLEVER_FUNCTION(microtime)
{
	struct timeval tp = {0};

	if (!clever_static_check_no_args()) {
		return;
	}
	if (gettimeofday(&tp, NULL)) {
		result->setBool(false);
		return;
	}

	result->setDouble(tp.tv_sec + tp.tv_usec / 1000000.00);
}

// getpid()
// Returns the current process id
static CLEVER_FUNCTION(getpid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getpid());
}

// getppid()
// Returns the current process id
static CLEVER_FUNCTION(getppid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getppid());
}

// getuid()
// Returns the process user id
static CLEVER_FUNCTION(getuid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::geteuid());
}

// getsid()
// Returns the process group id
static CLEVER_FUNCTION(getsid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getsid(0));
}

} // clever::modules::std::sys

// Initializes Standard module
CLEVER_MODULE_INIT(SYSModule)
{
	addFunction(new Function("system",    &CLEVER_NS_FNAME(sys, system)));
	addFunction(new Function("putenv",    &CLEVER_NS_FNAME(sys, putenv)));
	addFunction(new Function("getenv",    &CLEVER_NS_FNAME(sys, getenv)));
	addFunction(new Function("getcwd",    &CLEVER_NS_FNAME(sys, getcwd)));
	addFunction(new Function("getpid",    &CLEVER_NS_FNAME(sys, getpid)));
	addFunction(new Function("getppid",   &CLEVER_NS_FNAME(sys, getppid)));
	addFunction(new Function("getuid",    &CLEVER_NS_FNAME(sys, getuid)));
	addFunction(new Function("getsid",    &CLEVER_NS_FNAME(sys, getsid)));
	addFunction(new Function("argc",      &CLEVER_NS_FNAME(sys, argc)));
	addFunction(new Function("argv",      &CLEVER_NS_FNAME(sys, argv)));
	addFunction(new Function("sleep",     &CLEVER_NS_FNAME(sys, sleep)));
	addFunction(new Function("clock",     &CLEVER_NS_FNAME(sys, clock)));
	addFunction(new Function("time",      &CLEVER_NS_FNAME(sys, time)));
	addFunction(new Function("microtime", &CLEVER_NS_FNAME(sys, microtime)));
}

}}} // clever::modules::std
