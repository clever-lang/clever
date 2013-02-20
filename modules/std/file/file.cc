/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/file/file.h"
#include "modules/std/file/cfile.h"
#include "core/vm.h"
#include "core/value.h"
#include "core/clever.h"
#include "types/type.h"
#include "modules/std/core/function.h"
#include <sys/stat.h>
#include <cstdio>


namespace clever { namespace modules { namespace std {
	
namespace file {
	
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

static CLEVER_FUNCTION(file_exists)
{
	if (!clever_static_check_args("s")) {
		return;
	}
	
	const char* file = args[0]->getStr()->c_str();
	struct stat info;
	
	result->setBool(stat(file, &info) == 0);
}

static CLEVER_FUNCTION(is_dir)
{
	if (!clever_static_check_args("s")) {
		return;
	}
	
	const char* dir = args[0]->getStr()->c_str();
	struct stat info;
	
	if (stat(dir, &info) != 0) {
		clever_throw("Directory does not exists.");
		return;
	}
	
	result->setBool((info.st_mode & S_IFMT) == S_IFDIR);
}

} // clever::modules::std::file

/// Initializes Standard File module
CLEVER_MODULE_INIT(FileModule)
{
	addFunction(new Function("rename",      &CLEVER_NS_FNAME(file, rename)));
	addFunction(new Function("remove",      &CLEVER_NS_FNAME(file, remove)));
	addFunction(new Function("file_exists", &CLEVER_NS_FNAME(file, file_exists)));
	addFunction(new Function("is_dir",      &CLEVER_NS_FNAME(file, is_dir)));
	
	addType(new CFile);
}

}}} // clever::modules::std
