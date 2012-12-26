/**
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
 */

#include <iostream>
#include "compiler/clever.h"
#include "interpreter/driver.h"
#ifdef _WIN32
#include "win32/win32.h"
#endif

#define MORE_ARG() \
	if (!(++i < argc)) { \
		std::cerr << "Missing parameter for option " << argv[i-1] << std::endl; \
		exit(1); \
	}

static void show_usage()
{
    std::cout << "Usage: clever <options> [filename]\n\n"
                 "General options:\n";

#ifdef _WIN32
    std::cout << "\t-b\tRun on background\n";
#endif

    std::cout << "\t-h\tHelp\n"
                 "\t-v\tShow version\n"
                 "\n";

    std::cout << "Code options (must be the last one and unique):\n"
                 "\t-i\tRun the interative mode\n"
                 "\t-r\tRun the code\n"
                 "\t-qr\tQuickly run the code (import std automatically)\n"
                 "\n";

#ifdef CLEVER_DEBUG
    std::cout << "Debug options:\n"
                 "\t-p\tTrace parsing\n"
                 "\t-d\tDump opcode\n"
                 "\n";
#endif
}

int main(int argc, char **argv)
{
    clever::Interpreter clever(&argc, &argv);

	if (argc == 1) {
		std::cout << "Clever Programming Language" << std::endl;
		show_usage();
		return 0;
	}

    int inc_arg = 0;

    for (int i = 1; i < argc; ++i) {
		// Look for general options, then code options and finally debug options.
		if (argv[i] == std::string("-h")) {
			show_usage();
			return 0;
		} else if (argv[i] == std::string("-v")) {
            std::cout << "Clever - development version";

#ifdef CLEVER_DEBUG
            std::cout << " (debug)";
#endif
            std::cout << "\n"
                         "Copyright (c) 2011-2012 Clever Team\n"
                         "(built: " __DATE__ " " __TIME__ ")\n";

			return 0;
#ifdef _WIN32
		} else if (argv[i] == std::string("-b")) {
			if (GetConsoleWindow()) {
				std::string cline;

				for (int j = 0; j < argc; ++j) {
					if (argv[j] != std::string("-b")) {
						cline = cline + std::string(argv[j]) + " ";
					}
				}

				CreateBackgroundProcess(cline);
				return 0;
			}
#endif
		} else if (argv[i] == std::string("-i")) {
			std::string input_line;
			inc_arg++;
			while (std::cin) {
				getline(std::cin, input_line);
				if (clever.loadStr(input_line + '\n', false) == 0) {
					clever.execute(true);
				}
  			}
  			clever.shutdown();
  			return 0;
		} else if (argv[i] == std::string("-r")) {
			MORE_ARG();
			inc_arg++;
			if (clever.loadStr(argv[i], false)) {
				clever.shutdown();
				exit(1);
			}
			break;
		} else if (argv[i] == std::string("-qr")) {
			MORE_ARG();
			inc_arg++;
			if (clever.loadStr(argv[i], true)) {
				clever.shutdown();
				exit(1);
			}
			break;
#ifdef CLEVER_DEBUG
		} else if (argv[i] == std::string("-p")) {
			inc_arg++;
			clever.setTraceParsing(true);
		} else if (argv[i] == std::string("-d")) {
			inc_arg++;
			clever.setDebug();
#endif
		} else if (argv[i][0] == '-') {
			std::cerr << "Unknown option '" << argv[i] << "'" << std::endl;
			exit(1);
		} else {
			clever.loadFile(argv[i]);
			break;
		}
	}

	argc -= inc_arg + 1;
	argv += inc_arg + 1;

	clever.execute(false);
    clever.shutdown();

	return 0;
}
