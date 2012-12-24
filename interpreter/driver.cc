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

#include <fstream>
#include <setjmp.h>
#include "compiler/cstring.h"
#include "interpreter/driver.h"
#include "interpreter/parser.hh"
#include "interpreter/position.hh"
#include "scanner.h"

namespace clever {

jmp_buf fatal_error;

/**
 * Interpreter constructor
 */
Interpreter::Interpreter(int* argc, char*** argv)
{
}

/**
 * Executes the script
 */
void Interpreter::execute(bool interactive)
{
/*
	VM::setIR(&m_compiler.getIR());
	VM::run();
	VM::shutdown();
*/
	m_compiler.shutdown();
}

/**
 * Read the file defined in file property
 */
void Driver::readFile(std::string& source) const
{
	std::string line;
	std::fstream filep(m_file->c_str());

	if (!filep) {
		std::cerr << "Couldn't open file " << m_file->str() << std::endl;
		exit(1);
	}
	source = "";

	while (!filep.eof()) {
		getline(filep, line);
		source += line;
		source += '\n';
	}

	filep.clear();
	filep.close();
}

/**
 * Starts the parsing of the supplied file
 */
int Driver::parseFile(const std::string& filename)
{
	ScannerState* new_scanner = new ScannerState;
	Parser parser(*this, *new_scanner, m_compiler);
	std::string& source = new_scanner->getSource();

	m_is_file = true;
	m_file = CSTRING(filename);

	readFile(source);

	m_scanners.push(new_scanner);

	const unsigned char* s = reinterpret_cast<const unsigned char*>(source.c_str());

	m_scanners.top()->set_cursor(s);
	m_scanners.top()->set_limit(s + source.length());

	// Bison debug option
	parser.set_debug_level(m_trace_parsing);

	int result = parser.parse();

	delete new_scanner;
	m_scanners.pop();

	return result;
}

/**
 * Starts the parsing of the supplied string
 */
int Driver::parseStr(const std::string& code, bool importStd)
{
	ScannerState *new_scanner = new ScannerState;
	Parser parser(*this, *new_scanner, m_compiler);
	std::string& source = new_scanner->getSource();

	if (importStd) {
		source += std::string("import std.*;");
	}
	source += code;

	/* Set the source code to scanner read it */
	m_scanners.push(new_scanner);

	const unsigned char* s = reinterpret_cast<const unsigned char*>(source.c_str());
	m_scanners.top()->set_cursor(s);
	m_scanners.top()->set_limit(s + source.length());

	/* Bison debug option */
	parser.set_debug_level(m_trace_parsing);

	int result = parser.parse();

	delete new_scanner;
	m_scanners.pop();

	return result;
}

/**
 * Prints an error message and exit
 */
void Driver::error(const location& location, const std::string& msg) const
{
	position last = location.end - 1;

	if (last.filename) {
		std::cerr << msg << " in " << *last.filename <<
			" on line " << last.line << std::endl;
	} else {
		std::cerr << msg << " on line " << last.line << std::endl;
	}
	exit(1);
}

/**
 * Prints an error message
 */
void Driver::error(const std::string& message) const
{
	std::cerr << message << std::endl;
}

} // clever
