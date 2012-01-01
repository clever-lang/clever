/*
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
 *
 * $Id$
 */

#ifndef CLEVER_TESTRUNNER_H
#define CLEVER_TESTRUNNER_H

#include <vector>
#include <dirent.h>
#include <sys/time.h>
#include <pcrecpp.h>

class TestRunner {
	unsigned int pass, fail, leak;
	timeval start_time;
	std::vector<std::string> files;
	std::vector<std::string> tmp_files;

	bool file_exists(std::string file);
	std::string extract_folder(const char* file) const;
	unsigned int file_size(std::string file);
	void load_folder(const char* dir);
	void write_log(std::string testname, std::string message);
public:
	TestRunner() : pass(0), fail(0), leak(0), valgrind(false) { gettimeofday(&start_time, NULL); }
	~TestRunner();

	std::string read_file(const char*) const;
	void find(char* dir);
	void run(void);
	void show_result(void) const;
	void write_file(std::string&, std::string&);

	bool valgrind;
};

#endif // CLEVER_TESTRUNNER_H
