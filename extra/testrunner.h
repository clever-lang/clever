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
public:
	enum { FAIL_ONLY = 1 };

	TestRunner()
		: valgrind(false), pass(0), fail(0), leak(0), flags(0)
		{ start_time = clock(); }

	~TestRunner();

	std::string read_file(const char*) const;
	void find(const char* dir);
	void run(void);
	bool show_result(void) const;
	void write_file(std::string&, std::string&);
	void setFlags(unsigned int val) { flags |= val; }
	unsigned int getFlags() const { return flags; }

	bool valgrind;
private:
	unsigned int pass, fail, leak, flags;
	clock_t start_time;
	std::vector<std::string> files;
	std::vector<std::string> tmp_files;

	void load_folder(const char* dir);

	static bool fileExists(const std::string&);
	static size_t fileSize(const std::string&);
	static void writeLog(const std::string&, const std::string&);
};

#endif // CLEVER_TESTRUNNER_H
