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

#include <fstream>
#include "driver.h"
#include "parser.hh"
#include "position.hh"
#include "cstring.h"
#include "scanner.h"
#include "vm.h"

namespace clever {

Driver::ScannerStack Driver::s_scanners;

/**
 * Executes the script
 */
void Interpreter::execute() {
	VM vm;

	m_compiler.buildIR();

	vm.set_opcodes(m_compiler.getOpcodes());
	vm.run();
}

void Interpreter::shutdown() {

}

/**
 * Read the file defined in file property
 */
void Driver::readFile() throw() {
	std::string line;
	std::fstream filep(m_file->c_str());

	if (!filep) {
		std::cerr << "Couldn't open file " << m_file << std::endl;
		exit(1);
	}

	while (!filep.eof()) {
		getline(filep, line);
		m_source += line;
		m_source += '\n';
	}

	filep.close();
}

/**
 * Parses a file
 */
int Driver::parseFile(const std::string& filename) {
	ScannerState* new_scanner = new ScannerState;
	Parser parser(*this, new_scanner);
	int result = 0;

	m_is_file = true;
	// Save the filename
	m_file = CSTRING(filename);
	// Read the file
	readFile();
	// Set the file source to scanner read it
	s_scanners.push(new_scanner);
	s_scanners.top()->set_cursor(m_source.c_str());
	// Bison debug option
	parser.set_debug_level(m_trace_parsing);

	result = parser.parse();

	delete new_scanner;
	s_scanners.pop();

	return result;
}

/**
 * Parses a string
 */
int Driver::parseStr(const std::string& code) {
	ScannerState* new_scanner = new ScannerState;
	Parser parser(*this, new_scanner);
	int result = 0;

	/* Save the source code */
	m_source = code;

	/* Set the source code to scanner read it */
	s_scanners.push(new_scanner);
	s_scanners.top()->set_cursor(m_source.c_str());

	/* Bison debug option */
	parser.set_debug_level(m_trace_parsing);

	result = parser.parse();

	delete new_scanner;

	s_scanners.pop();

	return result;
}

/**
 * Prints an error message and exit
 */
void Driver::error(const clever::location& location, const std::string& message) const throw() {
	position last = location.end - 1;

	if (m_input.size()) {
		std::cerr << message << " on line " << last.line << std::endl;
	} else {
		std::cerr << message << " in " << *last.filename << " on line " << last.line << std::endl;
	}
	exit(1);
}

/**
 * Prints an error message
 */
void Driver::error(const std::string& message) const throw() {
	std::cerr << message << std::endl;
}

} // clever