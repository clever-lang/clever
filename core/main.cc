/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
#include "driver.h"
#ifdef _WIN32
#include "win32.h"
#endif

#define MORE_ARG() \
	if (!(++i < argc)) { \
		std::cerr << "Missing parameter for option " << argv[i-1] << std::endl; \
		exit(1); \
	}

static void show_usage(void) {
	std::cout << "Usage: clever <options>" << std::endl;
	std::cout << "\t-f Execute the file" << std::endl;
	std::cout << "\t-r Run the code" << std::endl;
#ifdef _WIN32
	std::cout << "\t-b Run on background (Windows only)" << std::endl;
#endif
	std::cout << "\t-h Help" << std::endl;
}

int main(int argc, char *argv[]) {
	clever::Interpreter clever;

	if (argc == 1) {
		std::cout << "Clever Programming Language" << std::endl;
		show_usage();
	}

	for (int i = 1; i < argc; ++i) {
		if (argv[i] == std::string("-f")) {
			MORE_ARG();
			clever.parseFile(argv[i]);
			clever.execute();
			clever.shutdown();
			break;
#ifdef CLEVER_DEBUG
		} else if (argv[i] == std::string("-p")) {
			clever.trace_parsing = true;
#endif
		} else if (argv[i] == std::string("-r")) {
			MORE_ARG();
			clever.parseStr(argv[i]);
			clever.execute();
			clever.shutdown();
			break;
		} else if (argv[i] == std::string("-i")) {
			std::string input_line;

			while (std::cin) {
				getline(std::cin, input_line);
				clever.parseStr(input_line + '\n');
				clever.execute();
  			}
  			clever.shutdown();
		} else if (argv[i] == std::string("-h")) {
			show_usage();
		} else if (argv[i] == std::string("-v")) {
			std::cout << "Clever - development version" << std::endl;
#ifdef _WIN32
		} else if (argv[i] == std::string("-b")) {
			if (GetConsoleWindow()) {
				std::string cline;

				for (int j = 0; j < argc; ++j) {
					cline = cline + std::string(argv[j]) + " ";
				}

				CreateBackgroundProcess(cline);
				return 0;
			}
#endif
		} else {
			std::cerr << "Unknown option '" << argv[i] << "'" << std::endl;
		}
	}

	return 0;
}
