/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cstdio>
#include <sys/stat.h>
#ifndef _WIN32
#include <glob.h>
#else
#include <windows.h>
#endif
#include <libgen.h>
#include "core/clever.h"
#include "core/value.h"
#include "core/vm.h"
#include "modules/std/file/cfile.h"
#include "modules/std/file/file.h"
#include "modules/std/core/function.h"
#include "modules/std/core/array.h"
#include "types/type.h"


namespace clever { namespace modules { namespace std {

namespace file {

// rename(String current_path, String new_path)
static CLEVER_FUNCTION(rename)
{
	if (!clever_static_check_args("ss")) {
		return;
	}

	const char* from = args[0]->getStr()->c_str();
	const char* to = args[1]->getStr()->c_str();
	struct stat info;

	// Check if file from exists
	if (stat(from, &info) != 0) {
		clever_throw("File FROM does not exists.");
		return;
	}

	result->setBool(::std::rename(from, to) == 0);
}

// remove(String path)
static CLEVER_FUNCTION(remove)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* file = args[0]->getStr()->c_str();
	struct stat info;

	// Check if file from exists
	if (stat(file, &info) != 0) {
		clever_throw("File does not exists.");
		return;
	}

	result->setBool(::std::remove(file) == 0);
}

// file_exists(String path)
static CLEVER_FUNCTION(file_exists)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* file = args[0]->getStr()->c_str();
	struct stat info;

	result->setBool(stat(file, &info) == 0);
}

// is_dir(String path)
static CLEVER_FUNCTION(is_dir)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* dir = args[0]->getStr()->c_str();
	struct stat info;

	if (stat(dir, &info) != 0) {
		result->setBool(false);
        return;
	}

	result->setBool((info.st_mode & S_IFMT) == S_IFDIR);
}

// glob(String pattern)
static CLEVER_FUNCTION(glob)
{
	if (!clever_static_check_args("s")) {
		return;
	}
	::std::vector< ::std::string> paths;

#ifndef _WIN32
	glob_t globbuf;

	globbuf.gl_offs = 0;

	glob(args[0]->getStr()->c_str(), GLOB_DOOFFS, NULL, &globbuf);

	for (size_t i = 0; i < globbuf.gl_pathc; ++i) {
		paths.push_back(globbuf.gl_pathv[i]);
	}

	if (globbuf.gl_pathc) {
		globfree(&globbuf);
	}
#else
	WIN32_FIND_DATA ffd;
	HANDLE hf = FindFirstFile(args[0]->getStr()->c_str(), &ffd);

	if (hf) {
		do {
			paths.push_back(ffd.cFileName);
		} while (FindNextFile(hf, &ffd) != 0);

		FindClose(hf);
	}
#endif

	if (paths.empty()) {
		result->setBool(false);
	} else {
		::std::vector< ::std::string>::const_iterator it(paths.begin()),
			end(paths.end());
		ArrayObject* array = new ArrayObject;

		for (; it != end; ++it) {
			Value* value = new Value;
			value->setStr(new StrObject(*it));

			array->getData().push_back(value);
		}
		result->setObj(CLEVER_ARRAY_TYPE, array);
	}
}

// basename(String path)
static CLEVER_FUNCTION(basename)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* path = basename(const_cast<char*>(args[0]->getStr()->c_str()));

	result->setStr(new StrObject(path));
}

// dirname(String path)
static CLEVER_FUNCTION(dirname)
{
	if (!clever_static_check_args("s")) {
		return;
	}

	const char* path = dirname(const_cast<char*>(args[0]->getStr()->c_str()));

	result->setStr(new StrObject(path));
}

} // clever::modules::std::file

/// Initializes Standard File module
CLEVER_MODULE_INIT(FileModule)
{
	addFunction(new Function("rename",      &CLEVER_NS_FNAME(file, rename)));
	addFunction(new Function("remove",      &CLEVER_NS_FNAME(file, remove)));
	addFunction(new Function("file_exists", &CLEVER_NS_FNAME(file, file_exists)));
	addFunction(new Function("is_dir",      &CLEVER_NS_FNAME(file, is_dir)));
	addFunction(new Function("glob",        &CLEVER_NS_FNAME(file, glob)));
	addFunction(new Function("basename",    &CLEVER_NS_FNAME(file, basename)));
	addFunction(new Function("dirname",     &CLEVER_NS_FNAME(file, dirname)));

	addType(new CFile);
}

}}} // clever::modules::std
