/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdlib>
#include <sstream>

#ifdef CLEVER_WIN32
# include <direct.h>
# include <windows.h>
# define PATH_MAX MAX_PATH
#else
# include <sys/utsname.h>
# include <dirent.h>
# include <sys/resource.h>
# include <sys/time.h>
# include <unistd.h>
#endif
#include "core/clever.h"
#include "core/value.h"
#include "core/driver.h"
#include "core/native_types.h"
#include "core/modmanager.h"
#include "core/cexception.h"
#include "modules/std/sys/sys.h"

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

// put_env(string env)
// Sets an environment variable
static CLEVER_FUNCTION(put_env)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	::putenv(const_cast<char*>(args[0]->getStr()->c_str()));
}

// get_env(string env)
// Gets an environment variable
static CLEVER_FUNCTION(get_env)
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

// get_cwd()
// Gets the current working directory
static CLEVER_FUNCTION(get_cwd)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	char temp[PATH_MAX];
	const char* path = ::getcwd(temp, PATH_MAX);

	result->setStr(CSTRING(path ? path : ""));
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

	struct timeval tp = {0};
	if (gettimeofday(&tp, NULL)) {
		result->setBool(false);
		return;
	}
	result->setDouble(tp.tv_sec);
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

// get_pid()
// Returns the current process id
static CLEVER_FUNCTION(get_pid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getpid());
}

// get_ppid()
// Returns the current process id
static CLEVER_FUNCTION(get_ppid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getppid());
}

// get_uid()
// Returns the process user id
static CLEVER_FUNCTION(get_uid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::geteuid());
}

// get_sid()
// Returns the process group id
static CLEVER_FUNCTION(get_sid)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	result->setInt(::getsid(0));
}

// exit()
// Exits the execution
static CLEVER_FUNCTION(exit)
{
	if (!clever_static_check_args("i")) {
		return;
	}

	::exit(args[0]->getInt());
}

// info()
// Returns information about the build and environment
static CLEVER_FUNCTION(info)
{
	if (!clever_static_check_no_args()) {
		return;
	}

	::std::ostringstream oss;
	oss << "Version: " << CLEVER_VERSION_STRING << "\n";
	oss << "Debug Mode: ";
#ifdef CLEVER_DEBUG
	oss << "Yes\n";
#else
	oss << "No\n";
#endif

	oss << "OS: ";
#ifdef CLEVER_WIN32
	oss << "Windows";
# ifdef CLEVER_CYGWIN
	oss << " (Cygwin)";
# elif CLEVER_MSVC
	oss << " (MSVC)";
# endif
#elif CLEVER_APPLE
	oss << "Mac OSX";
#elif CLEVER_HAIKU
	oss << "Haiku";
#else
	oss << "Unknown";
#endif
	oss << "\n\n";

	oss << "Integer Size: " << sizeof(long) * 8 << " bits (" << sizeof(long)
		<< " bytes)";

	// TODO(muriloadriano): Add more and more detailed information about the
	// environment and the enabled modules.

	return result->setStr(new StrObject(oss.str()));
}

// Returns a Value ptr containing the OS name
static Value* get_os()
{
	Value* val = new Value(CLEVER_STR_TYPE, true);

#ifndef CLEVER_WIN32
	struct utsname name;

	if (!uname(&name)) {
		val->setStr(new StrObject(name.sysname));
	}
#endif
	return val;
}

// Returns a constant array containing the argv
static Value* get_argv()
{
	Value* argv = new Value();
	ArrayObject* arr = new ArrayObject();
	::std::vector<Value*>& args = arr->getData();

	for (int i = 0; i < *g_clever_argc; ++i) {
		args.push_back(new Value());
		args.back()->setStr((*g_clever_argv)[i]);
		args.back()->setConst(true);
	}

	argv->setConst(true);
	argv->setObj(CLEVER_ARRAY_TYPE, arr);

	return argv;
}

} // clever::modules::std::sys

// Initializes Standard module
CLEVER_MODULE_INIT(SYSModule)
{
	addFunction(new Function("system",    &CLEVER_NS_FNAME(sys, system)));
	addFunction(new Function("put_env",   &CLEVER_NS_FNAME(sys, put_env)));
	addFunction(new Function("get_env",   &CLEVER_NS_FNAME(sys, get_env)));
	addFunction(new Function("get_cwd",   &CLEVER_NS_FNAME(sys, get_cwd)));
	addFunction(new Function("get_pid",   &CLEVER_NS_FNAME(sys, get_pid)));
	addFunction(new Function("get_ppid",  &CLEVER_NS_FNAME(sys, get_ppid)));
	addFunction(new Function("get_uid",   &CLEVER_NS_FNAME(sys, get_uid)));
	addFunction(new Function("get_sid",   &CLEVER_NS_FNAME(sys, get_sid)));
	addFunction(new Function("sleep",     &CLEVER_NS_FNAME(sys, sleep)));
	addFunction(new Function("clock",     &CLEVER_NS_FNAME(sys, clock)));
	addFunction(new Function("time",      &CLEVER_NS_FNAME(sys, time)));
	addFunction(new Function("microtime", &CLEVER_NS_FNAME(sys, microtime)));
	addFunction(new Function("info",      &CLEVER_NS_FNAME(sys, info)));
	addFunction(new Function("exit",      &CLEVER_NS_FNAME(sys, exit)));

	addVariable("OS",   sys::get_os());
	addVariable("argc", new Value(long(*g_clever_argc), true));
	addVariable("argv", sys::get_argv());
}

}}} // clever::modules::std
