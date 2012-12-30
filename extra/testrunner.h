/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TESTRUNNER_H
#define CLEVER_TESTRUNNER_H

#include <vector>
#include <ctime>
#ifndef CLEVER_WIN32
#include <dirent.h>
#else
#include <win32/dirent.h>
#endif
#include <pcrecpp.h>

class TestRunner {
	unsigned int pass, fail, leak, flags;
	clock_t start_time;
	std::vector<std::string> files;
	std::vector<std::string> tmp_files;

	bool file_exists(std::string file);
	std::string extract_folder(const char* file) const;
	unsigned int file_size(std::string file);
	void load_folder(const char* dir);
	void write_log(std::string testname, std::string message);
public:
	enum { FAIL_ONLY = 1 };

	TestRunner() : pass(0), fail(0), leak(0), flags(0), valgrind(false) { start_time = clock(); }
	~TestRunner();

	std::string read_file(const char*) const;
	void find(char* dir);
	void run(void);
	void show_result(void) const;
	void write_file(std::string&, std::string&);
	void setFlags(int val) { flags |= val; }
	int getFlags() const { return flags; }

	bool valgrind;
};

#endif // CLEVER_TESTRUNNER_H
