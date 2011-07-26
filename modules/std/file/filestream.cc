/**
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
 */

#include <fstream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "std/file/filestream.h"

namespace clever { namespace packages { namespace std { namespace file {

/**
 * FileStream::toString()
 * A representation of this class as a string
 */
CLEVER_TYPE_METHOD(FileStream::toString) {
	retval->setString(CSTRING("FileStream class"));
	retval->set_type(Value::STRING);
}

/**
 * FileStream::open(String file, [Int mode])
 * Open a file
 */
CLEVER_TYPE_METHOD(FileStream::open) {
	size_t size = args->size();
	
	FileStreamValue* fsv = static_cast<FileStreamValue*>(value->get_data()->dv_value);
	
	if (size == 1) {
		fsv->m_fstream.open(args->at(0)->toString().c_str());
		fsv->m_is_open = true;
	}
	else Compiler::error("calling Filestream::read() : wrong number "
		"of arguments given to FileStream::open(String)");
	
	retval->set_type(Value::NONE);
}

/**
 * FileStream::read([String, Int, Double])
 * Get the next token from the file
 */
CLEVER_TYPE_METHOD(FileStream::read) {
	size_t size = args->size();
	
	if (size != 1)
		Compiler::error("calling Filestream::read([String, Int, Double]) : wrong number of arguments given");
	
	
	FileStreamValue* fsv = static_cast<FileStreamValue*>(value->get_data()->dv_value);
	
	if (!fsv->m_is_open) {
		Compiler::error("calling Filestream::read([String, Int, Double])"
			" : no file stream is open (use Filestream::open() before)");
	}
	
	if (args->at(0)->isInteger()) {
		uint64_t val;
		fsv->m_fstream >> val;
		
		args->at(0)->setInteger(val);
	}
	else if (args->at(0)->isDouble()) {
		double val;
		fsv->m_fstream >> val;
		
		args->at(0)->setDouble(val);
	}
	else if (args->at(0)->isString()) {
		::std::string val;
		fsv->m_fstream >> val;
		
		args->at(0)->setString(CSTRING(val));
	}
	// @TODO : support more "native" types
	//else if (args->at(0)->isBoolean()) { 
	//	bool val;
	//	m_fstream >> val;
	//	
	//	args->at(0)->setBoolean(val);
	//}
	else {
		Compiler::error("calling Filestream::read([String, Int, Double]) : argument type is incompatible");
	}
	
	retval->set_type(Value::NONE);
}



void FileStream::init() {
	addMethod(new Method("toString", (MethodPtr)&FileStream::toString));
	addMethod(new Method("open", (MethodPtr)&FileStream::open));
	addMethod(new Method("read", (MethodPtr)&FileStream::read));
}

DataValue* FileStream::allocateValue() const {
	return new FileStreamValue;
}

}}}} // clever::packages::std::file
