/*
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "testrunner.h"

TestRunner::~TestRunner() {
	std::vector<std::string>::iterator it;

	for (it = tmp_files.begin(); it != tmp_files.end(); ++it) {
		unlink(it->c_str());
	}
}

void TestRunner::show_result(void) const {
	timeval end_time;
	double duration;

	gettimeofday(&end_time, NULL);

	duration = (end_time.tv_sec  - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec)/1000000.0;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Tests: " << files.size() << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Passed tests: " << pass << std::endl;
	std::cout << "Failed tests: " << fail << std::endl;

#ifndef _WIN32
	if (valgrind) {
		std::cout << "Leaked tests: " << leak << std::endl;
	}
#endif

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Time taken: " << duration << " seconds" << std::endl;
	std::cout << "-----------------------------------" << std::endl;
}

void TestRunner::find(char* dir) {
	DIR *dp;
	std::fstream filep;
	std::string path;

	// Ignore .log files
	path = std::string(dir);
	if ((path.size()-4 == path.rfind(".log")) || (path.size()-4 == path.rfind(".mem"))) {
		return;
	}

	// If it's not a file, then it must be a directory
	filep.open(dir);
	if (filep.is_open()) {
		filep.close();
		files.push_back(std::string(dir));
	} else if ((dp = opendir(dir)) != NULL) {
		closedir(dp);
		path = std::string(dir);
		if (path[path.size()-1] != '/') {
			path = path + "/";
		}
		load_folder(path.c_str());
	} else {
		std::cout << "Couldn't open the file or directory specified: " << std::string(dir) << std::endl;
		//exit(1);
		return;
	}
}

void TestRunner::run(void) {
	FILE *fp;
	std::vector<std::string>::iterator it;
	std::string file_name, tmp_file;
	pcrecpp::RE regex("((?s:.(?!==CODE==))+)\\s*==CODE==\\s*((?s:.(?!==RESULT==))+)\\s*==RESULT==\\s*((?s:.+))\\s+");

	if (!files.size()) {
		std::cout << "No files found.";
		exit(1);
	}

	for (it = files.begin(); it != files.end(); ++it) {
		char result[300] = {0};
		std::string title, source, expect, log_line, command;
		unsigned int filesize;

		file_name = *it;

		tmp_file = file_name + ".tmp";

		regex.FullMatch(read_file(file_name.c_str()), &title, &source, &expect);

		write_file(tmp_file, source);

#ifndef _WIN32
		if (valgrind) {
			command = std::string("valgrind -q --tool=memcheck --leak-check=yes --num-callers=30 --log-file=") + file_name + std::string(".mem");
			command = command + std::string(" ./clever -f ") + tmp_file + " 2>&1";
			fp = popen(command.c_str(), "r");
		} else {
			command = std::string("./clever -f ") + tmp_file + " 2>&1";
			fp = popen(command.c_str(), "r");
		}
#else
		command = std::string("clever.exe -f ") + tmp_file + " 2>&1";
		fp = popen(command.c_str(), "r");
#endif

		if (fread(result, 1, sizeof(result)-1, fp) <= 0) {
			// Error?
			std::cout << "Something went wrong reading the result." << std::endl;
			exit(1);
		}
		
		// Tricky uh?
		pclose(fp);

		// Valgrind log is empty?
#ifndef _WIN32
		if (valgrind) {
			filesize = file_size(file_name + std::string(".mem"));
			if (filesize == 0) {
				remove(std::string(file_name + std::string(".mem")).c_str());
			} else {
				std::cout << "[LEAK] ";
				leak++;
			}
		}
#endif

		if (pcrecpp::RE(expect).FullMatch(result)) {
			if ((valgrind && filesize == 0) || !valgrind) {
				std::cout << "[OKAY] ";
			}
			pass++;

			// If the log file exists, then remove it.
			if (file_exists(file_name + ".log")) {
				unlink(std::string(file_name + ".log").c_str());
			}
		} else {
			if ((valgrind && filesize == 0) || !valgrind) {
				std::cout << "[FAIL] ";
			}
			log_line = std::string("== Expected ==\n") + expect + std::string("\n");
			log_line.append(std::string("== Got ==\n") + std::string(result));
			write_log(file_name,log_line);
			fail++;
		}

		std::cout << title << " (" << file_name << ")" << std::endl;
	}
}

void TestRunner::write_file(std::string& name, std::string& source) {
	std::ofstream file(name.c_str());

	file << source;
	file.close();

	tmp_files.push_back(name);
}

std::string TestRunner::read_file(const char* name) const {
	std::string source, line;
	std::ifstream file;

	file.open(name);

	if (!file) {
		std::cout << "Couldn't open file " << name << std::endl;
		exit(1);
	}

	while (!file.eof()) {
		getline(file, line);
		source += line + '\n';
	}
	file.close();

	return source;
}

void TestRunner::load_folder(const char* dir) {
	DIR *dp, *dpr;
	struct dirent *dirp;
	std::string path,file;

	if ((dp = opendir(dir)) != NULL) {
		while ((dirp = readdir(dp)) != NULL) {
			if (strcmp(dirp->d_name, ".") == 0 ||
				strcmp(dirp->d_name, "..") == 0 ||
				strstr(dirp->d_name, ".tmp") ||
				strstr(dirp->d_name, ".svn") ||
                strstr(dirp->d_name, ".gitignore")) {
				continue;
			}
			// Ignore .log files
			file = std::string(dirp->d_name);
			if ((file.size()-4 == file.rfind(".log")) || (file.size()-4 == file.rfind(".mem"))) {
				continue;
			}
			// Is this a folder or a file?
			path = std::string(dir) + std::string(dirp->d_name) + "/";
			if ((dpr = opendir(path.c_str())) != NULL) {
				closedir(dpr);
				load_folder(path.c_str());
			} else {
				path = std::string(dir) + std::string(dirp->d_name);
				files.push_back(path.c_str());
			}
		}
		closedir(dp);
	}
}

std::string TestRunner::extract_folder(const char* file) const {
	std::string path;
	size_t found;

	path = std::string(file);
	found = path.rfind("/");
	if (found != path.npos) {
		path = path.substr(0,found+1);
	}

	return path;
}

void TestRunner::write_log(std::string testname, std::string message) {
	FILE *log;

	testname = testname + ".log";
	log = fopen(testname.c_str(),"w");
	if (log) {
		fputs(message.c_str(),log);
		fclose(log);
	}
}

unsigned int TestRunner::file_size(std::string file) {
	std::ifstream stream;
	unsigned int length;

	stream.open(file.c_str());
	if (stream.is_open()) {
		stream.seekg(0,std::ios::end);
		length = stream.tellg();
		stream.close();

		return length;
	}

	return 0;
}

bool TestRunner::file_exists(std::string file) {
	std::ifstream stream;

	stream.open(file.c_str());
	if (stream.is_open()) {
		stream.close();
		return true;
	} else {
		return false;
	}
}

// ---------------------

void usage(void)
{
	std::cout << "Clever Language - Testrunner" << std::endl;
	std::cout << "Usage: testrunner [options] path-of-test-file/dir" << std::endl;
#ifndef _WIN32
	std::cout << "\t-m: run valgrind on each test" << std::endl;
#endif
}

int main(int argc, char *argv[])
{
	TestRunner testrunner;
	int start_paths = 1;

	if (argc == 1) {
		usage();
		return 1;
	} else {
#ifndef _WIN32
		if (std::string(argv[1]) == std::string("-m")) {
			if (argc == 2) {
				// ./testrunner -m?
				usage();
				return 1;
			}
			// ./testrunner -m <something here>?
			testrunner.valgrind = true;
			start_paths = 2;
#else
			if (argc == 1) {
				// ./testrunner -m?
				usage();
				return 1;
#endif
		} else {
			// ./testrunner <something here>
			testrunner.valgrind = false;
			start_paths = 1;
		}
	}

	for (; start_paths < argc; start_paths++) {
		testrunner.find(argv[start_paths]);
	}
	testrunner.run();
	testrunner.show_result();

	return 0;
}
