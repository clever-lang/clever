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

#include "driver.h"
#include "parser.hh"
#include "position.hh"
#include "types.h"
#include "scanner.h"

namespace clever {

std::stack<ScannerState*> Driver::scanners;

void Interpreter::execute(void)
{
//	compiler_p->finalize();	
}

void Interpreter::shutdown(void)
{
//	compiler_p->shutdown();
}

/**
 * Read the file defined in file property
 */
void Driver::read_file(void)
{
	std::string line;
	std::fstream filep;

	filep.open(file.c_str());

	if (!filep) {
		std::cout << "Couldn't open file " << file << std::endl;
		exit(1);
	}

	while (!filep.eof()) {
		getline(filep, line);
		source += line + '\n';
	}
	
	filep.close();
}

/**
 * Parses a file
 * @param filename the file name
 */
int Driver::parse_file(const std::string& filename)
{
	ScannerState* new_scanner = new ScannerState;
	clever::Parser parser(*this, new_scanner);
	int result = 0;

	is_file = true;
	// Save the filename
	file = filename;	
	// Read the file
	read_file();
	// Set the file source to scanner read it
	scanners.push(new_scanner);
	scanners.top()->set_cursor(source.c_str());
	// Bison debug option
	parser.set_debug_level(trace_parsing);
	
	result = parser.parse();
	
	delete new_scanner;
	scanners.pop();
	
	return result;
}

/**
 * Parses a string
 * @param source the string to be parsed
 */
int Driver::parse_str(const std::string& code)
{
	ScannerState* new_scanner = new ScannerState;
	clever::Parser parser(*this, new_scanner);
	int result = 0;

	// Save the source code
	source = code;
	// Set the source code to scanner read it
	scanners.push(new_scanner);
	scanners.top()->set_cursor(source.c_str());
	// Bison debug option
	parser.set_debug_level(trace_parsing);
	
	result = parser.parse();
	
	delete new_scanner;
	scanners.pop();
	
	return result;
}

/**
 * Prints an error message
 * @param location the location
 * @param message the message to be printed
 */
void Driver::error(const clever::location& location, const std::string& message) const
{
	clever::position last = location.end - 1;

	if (input.size()) {
		std::cout << message << " on line " << last.line << std::endl;
	} else {
		std::cout << message << " in " << *last.filename << " on line " << last.line << std::endl;
	}
}

/**
 * Prints an error message
 * @param message the message to be printed
 */
void Driver::error(const std::string& message) const
{
	std::cout << message << std::endl;
}

} // clever