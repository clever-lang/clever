/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include "testrunner.h"

#ifdef CLEVER_MSVC
# define popen _popen
# define pclose _pclose
#else
# include <unistd.h>
#endif

TestRunner::~TestRunner()
{
	std::vector<std::string>::iterator it;

	for (it = tmp_files.begin(); it != tmp_files.end(); ++it) {
		unlink(it->c_str());
	}
}

bool TestRunner::show_result() const
{
	clock_t end_time;
	double duration;

	end_time = clock();

	duration = (end_time - start_time)*1000/CLOCKS_PER_SEC;

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Tests: " << files.size() << std::endl;
	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Passed tests: " << pass << std::endl;
	std::cout << "Failed tests: " << fail << std::endl;
	std::cout << "Skipped tests: " << skip << std::endl;

#ifndef _WIN32
	if (valgrind) {
		std::cout << "Leaked tests: " << leak << std::endl;
	}
	if (helgrind) {
		std::cout << "Race detecteds: " << races << std::endl;
	}
#endif

	std::cout << "-----------------------------------" << std::endl;
	std::cout << "Time taken: " << duration << "ms" << std::endl;
	std::cout << "-----------------------------------" << std::endl;

	return fail == 0;
}

void TestRunner::find(const char* dir)
{
	DIR *dp;
	std::fstream filep;
	std::string path;

	// Ignore .log and .mem files
	path = std::string(dir);
	if ((path.size()-4 == path.rfind(".log"))
		|| (path.size()-4 == path.rfind(".mem"))
		|| (path.size()-5 == path.rfind(".race"))) {
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

bool TestRunner::checkTest(const std::string& tmp_file)
{
	std::string command = std::string("./clever ") + tmp_file + " 2>&1";
	FILE* fp = popen(command.c_str(), "r");
	char result[300] = {0};

	if (fread(result, 1, sizeof(result)-1, fp) == 0 && ferror(fp) != 0) {
		std::cout << "Something went wrong reading the result." << std::endl;
		exit(1);
	}

	pclose(fp);

	return strstr(result, "skip") == NULL;
}

void TestRunner::run()
{
	FILE *fp;
	std::vector<std::string>::iterator it;
	std::string file_name, tmp_file, check_file;
	bool show_all_results = true, last_ok = true;
	pcrecpp::RE regex("((?s:.(?!==(?:CODE|CHECK)==))+)\\s*(?:==CHECK==\\s*((?s:.(?!==CODE==))+))?\\s*==CODE==\\s*((?s:.(?!==RESULT==))+)\\s*==RESULT==\\s*((?s:.+))\\s+");

	if (!files.size()) {
		std::cout << "No files found.";
		exit(1);
	}

	if (getFlags() & FAIL_ONLY) {
		show_all_results = false;
	}

	for (it = files.begin(); it != files.end(); ++it) {
		char result[300] = {0};
		std::string title, check, source, expect, log_line, command;
		size_t filesize = 0;
		clock_t test_start_time, test_end_time;

		file_name = *it;

		tmp_file = file_name + ".tmp";
		check_file = file_name + ".check.tmp";

		regex.FullMatch(read_file(file_name.c_str()), &title, &check, &source, &expect);

		if (!title.size()) {
			std::cerr << "Test error: malformed test detected (" << file_name << ")" << std::endl;
			exit(1);
		}

		if (check.size()) {
			check = "import std.*;\n" + check;

			write_file(check_file, check);

			bool ok = checkTest(check_file);

			unlink(check_file.c_str());

			if (!ok) {
				++skip;
				continue;
			}
		}

		write_file(tmp_file, source);

		std::cout << "\r[....] " << title << " (" << file_name << ")" << std::flush;

		// We should save the start time here.
		test_start_time = clock();

#ifndef _WIN32
		if (valgrind) {
			command = std::string("GLIBCXX_FORCE_NEW=yes valgrind -q --tool=memcheck --leak-check=yes --num-callers=30 --show-reachable=yes --track-origins=yes --log-file=") + file_name + std::string(".mem");
			command = command + std::string(" ./clever ") + tmp_file + " 2>&1";
		} else if (helgrind) {
			command = std::string("valgrind -q --tool=helgrind --num-callers=30 --log-file=") + file_name + std::string(".race");
			command = command + std::string(" ./clever ") + tmp_file + " 2>&1";
		} else {
			command = std::string("./clever ") + tmp_file + " 2>&1";
		}
		fp = popen(command.c_str(), "r");
#else
		command = std::string("clever.exe ") + tmp_file + " 2>&1";
		fp = _popen(command.c_str(), "r");
#endif

		if (fread(result, 1, sizeof(result)-1, fp) == 0 && ferror(fp) != 0) {
			// Error?
			std::cout << "Something went wrong reading the result." << std::endl;
			exit(1);
		}

		// Tricky uh?
		pclose(fp);

		// And we should also save the end time.
		test_end_time = clock();

		// Valgrind log is empty?
#ifndef _WIN32
		if (valgrind) {
			filesize = fileSize(file_name + std::string(".mem"));
			if (filesize == 0) {
				unlink(std::string(file_name + std::string(".mem")).c_str());
			} else {
				std::cout << "\r[LEAK] ";
				leak++;
				last_ok = false;
			}
		} else if (helgrind) {
			filesize = fileSize(file_name + std::string(".race"));
			if (filesize == 0) {
				unlink(std::string(file_name + std::string(".race")).c_str());
			} else {
				std::cout << "\r[RACE] ";
				races++;
				last_ok = false;
			}
		}
#endif
		if (!valgrind) {
			// If the mem log file exists, then remove it.
			if (fileExists(file_name + ".mem")) {
				unlink(std::string(file_name + ".mem").c_str());
			}
		}
		if (!helgrind) {
			if (fileExists(file_name + ".race")) {
				unlink(std::string(file_name + ".race").c_str());
			}
		}

		if (pcrecpp::RE(expect).FullMatch(result)) {
			if ((valgrind && filesize == 0) || (helgrind && filesize == 0)
				|| !(valgrind || helgrind)) {
				if (show_all_results) {
					std::cout << "\r[OKAY] ";
				}
				last_ok = true;
			}
			pass++;

			// If the log file exists, then remove it.
			if (fileExists(file_name + ".log")) {
				unlink(std::string(file_name + ".log").c_str());
			}
		} else {
			if ((valgrind && filesize == 0)
				|| (helgrind && filesize == 0)
				|| !(valgrind || helgrind)) {
				std::cout << "\r[FAIL] ";
				last_ok = false;
			}
			log_line = std::string("== Expected ==\n") + expect + std::string("\n");
			log_line.append(std::string("== Got ==\n") + std::string(result));
			writeLog(file_name, log_line);
			fail++;
		}

		if (!(show_all_results == true || last_ok == false)) {
			std::cout << "\r[PASS] ";
		}
		std::cout << title << " (" << file_name << ")" << " - " << ((test_end_time - test_start_time)*1000/CLOCKS_PER_SEC) << "ms" << std::endl;

	}
}

void TestRunner::write_file(std::string& name, std::string& source)
{
	std::ofstream file(name.c_str());

	file << source;
	file.close();

	tmp_files.push_back(name);
}

std::string TestRunner::read_file(const char* name) const
{
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

void TestRunner::load_folder(const char* dir)
{
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
			if ((file.size() > 4 &&
				(file.size()-4 == file.rfind(".log")
				|| file.size()-4 == file.rfind(".mem")))
				|| (file.size() > 5 && file.size()-5 == file.rfind(".race"))) {
				continue;
			}
			// Is this a folder or a file?
			path = std::string(dir) + std::string(dirp->d_name) + "/";
			if ((dpr = opendir(path.c_str())) != NULL) {
				closedir(dpr);
				load_folder(path.c_str());
			} else {
				// Ignore non .test file
				if (file.size()-5 != file.rfind(".test")) {
					continue;
				}
				path = std::string(dir) + std::string(dirp->d_name);
				files.push_back(path.c_str());
			}
		}
		closedir(dp);
	}
}

void TestRunner::writeLog(const std::string& testname, const std::string& message)
{
	std::string filename = testname + ".log";
	FILE *log = fopen(filename.c_str(),"w");

	if (log) {
		fputs(message.c_str(), log);
		fclose(log);
	}
}

size_t TestRunner::fileSize(const std::string& file)
{
	std::ifstream stream;
	size_t length;

	stream.open(file.c_str());
	if (stream.is_open()) {
		stream.seekg(0,std::ios::end);
		length = stream.tellg();
		stream.close();

		return length;
	}

	return 0;
}

bool TestRunner::fileExists(const std::string& file)
{
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
	std::cout << "Clever programming language - Testrunner" << std::endl;
	std::cout << "Usage: testrunner [options] path-of-test-file/dir" << std::endl;
#ifndef _WIN32
	std::cout << "\t-m: run memcheck on each test (requires Valgrind)" << std::endl;
	std::cout << "\t-r: run helgrind on each test (requires Valgrind)" << std::endl;
#endif
	std::cout << "\t-q: only list failing tests" << std::endl;
}

int main(int argc, char *argv[])
{
	TestRunner testrunner;
	int start_paths = -1;

	if (argc == 1) {
		usage();
		return 1;
	} else {
		for (int i = 1; i < argc; i++) {
			if (std::string(argv[i]) == "-m") {
#ifdef _WIN32
				usage();
				return 1;
#else
				testrunner.valgrind = true;
#endif
			} else if (std::string(argv[i]) == "-q") {
				testrunner.setFlags(TestRunner::FAIL_ONLY);
			} else if (std::string(argv[i]) == "-r") {
				testrunner.helgrind = true;
			} else {
				start_paths = i;
			}
		}
	}

	if (start_paths < 0) {
		usage();
		return 1;
	}

	for (; start_paths < argc; start_paths++) {
		testrunner.find(argv[start_paths]);
	}
	testrunner.run();

	return !testrunner.show_result();
}
