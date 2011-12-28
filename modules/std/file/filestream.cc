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
#include <iostream>
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "types/typeutils.h"
#include "modules/std/file/filestream.h"

namespace clever { namespace packages { namespace std { namespace file {

::std::ios::openmode FileStream::convertOpenMode(::std::string modeString) {
	// @TODO: support binary modes.

	if (modeString == "r") {
		return ::std::ios_base::in;
	} else if (modeString == "w") {
		return ::std::ios_base::out | ::std::ios_base::trunc;
	} else if (modeString == "a") {
		return ::std::ios_base::out | ::std::ios_base::app;
	} else if (modeString == "r+") {
		return ::std::ios_base::in | ::std::ios_base::out;
	} else if (modeString == "w+") {
		return ::std::ios_base::in | ::std::ios_base::out | ::std::ios_base::trunc;
	} else if (modeString == "a+") {
		return ::std::ios_base::in | ::std::ios_base::out | ::std::ios_base::app;
	} else {
		// @TODO: return some kind of error here.
		return ::std::ios_base::in;
	}
}

/**
 * FileStream::toString()
 * A representation of this class as a string
 */
CLEVER_TYPE_METHOD(FileStream::toString) {
	retval->setString(CSTRING("FileStream class"));
}

/**
 * FileStream::open(String file, [String mode])
 * Open a file
 */
CLEVER_TYPE_METHOD(FileStream::open) {
	size_t size = args->size();
	
	FileStreamValue* fsv = static_cast<FileStreamValue*>(value->getData()->dv_value);
	
	if (size == 2) {
		fsv->m_fstream.open(args->at(0)->toString().c_str(), convertOpenMode(args->at(1)->toString()));
	} else {
		Compiler::error("calling Filestream::read() : wrong number "
			"of arguments given to FileStream::open(String, [String])");
	}
	
	retval->setType(Value::NONE);
}

/**
 * FileStream::open()
 * Close the file associated to the current stream
 */
CLEVER_TYPE_METHOD(FileStream::close) {
	FileStreamValue* fsv = static_cast<FileStreamValue*>(value->getData()->dv_value);
	
	if (fsv->m_fstream.is_open()) {
		fsv->m_fstream.close();
	}
	
	retval->setType(Value::NONE);
}

/**
 * FileStream::read([String, Int, Double])
 * Get the next token from the file
 */
CLEVER_TYPE_METHOD(FileStream::read) {
	FileStreamValue* fsv;
	size_t size = args->size();
	
	if (size != 1) {
		Compiler::error("calling Filestream::read([String, Int, Double]) :"
			" wrong number of arguments given");
	}	
	
	fsv = static_cast<FileStreamValue*>(value->getData()->dv_value);
	
	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling Filestream::read([String, Int, Double])"
			" : no file stream is open (use Filestream::open() before)");
	}

	// @TODO: should test if the stream allows reading.

	if (args->at(0)->isInteger()) {
		uint64_t val;
		fsv->m_fstream >> val;
		
		args->at(0)->setInteger(val);
	} else if (args->at(0)->isDouble()) {
		double val;
		fsv->m_fstream >> val;
		
		args->at(0)->setDouble(val);
	} else if (args->at(0)->isString()) {
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
		Compiler::error("calling Filestream::read([String, Int, Double]) :"
			" argument type is incompatible");
	}
	
	retval->setType(Value::NONE);
}

/**
 * FileStream::write([String])
 * Writes a String into the filestream.
 */
CLEVER_TYPE_METHOD(FileStream::write) {
	FileStreamValue *fsv;
	size_t size = args->size();

	if (size != 1) {
		Compiler::error("calling FileStream::write([String])) :"
			"wrong number of arguments given");
	}

	fsv = static_cast<FileStreamValue*>(value->getData()->dv_value);

	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling FileStream::write([Objext]) :"
			"no file stream is open (use Filestream::open() before)");
	}

	// @TODO: should check if the stream allows writing.

	// Write the String.
	fsv->m_fstream << args->at(0)->getString();

	retval->setType(Value::NONE);
}

/**
 * FileStreasm::writeLine([String])
 * Writes n String into the filestream, and then a new line.
 */
CLEVER_TYPE_METHOD(FileStream::writeLine) {
	FileStreamValue *fsv;
	size_t size = args->size();

	if (size != 1) {
		Compiler::error("calling FileStream::writeLine([String])) :"
			"wrong number of arguments given");
	}

	fsv = static_cast<FileStreamValue*>(value->getData()->dv_value);

	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling FileStream::writeLine([Objext]) :"
			"no file stream is open (use Filestream::open() before)");
	}

	// Write the String.
	fsv->m_fstream << args->at(0)->getString();

	// Write a new line.
	fsv->m_fstream << ::std::endl;

	retval->setType(Value::NONE);
}

void FileStream::init() {
	addMethod(new Method("toString", (MethodPtr)&FileStream::toString, 
		makeArgs(NULL), CLEVER_TYPE("Void")));
		
	addMethod(new Method("open", (MethodPtr)&FileStream::open, 
		makeArgs(CLEVER_TYPE("String"), CLEVER_TYPE("String"), NULL), CLEVER_TYPE("Void")));
		
	addMethod(new Method("close", (MethodPtr)&FileStream::close, 
		makeArgs(NULL), CLEVER_TYPE("Void")));
		
	addMethod(new Method("read", (MethodPtr)&FileStream::read, 
		makeArgs(CLEVER_TYPE("String"), NULL), CLEVER_TYPE("Void")));

	addMethod(new Method("write", (MethodPtr)&FileStream::write,
		makeArgs(CLEVER_TYPE("String"), NULL), CLEVER_TYPE("Void")));

	addMethod(new Method("writeLine", (MethodPtr)&FileStream::writeLine,
		makeArgs(CLEVER_TYPE("String"), NULL), CLEVER_TYPE("Void")));
}

DataValue* FileStream::allocateValue() const {
	return new FileStreamValue;
}

void FileStream::destructor(Value* value) const {
	FileStreamValue* fsv = static_cast<FileStreamValue*>(value->getDataValue());
	
	// Just close the stream
	if (fsv && fsv->m_fstream.is_open()) {
		fsv->m_fstream.close();
	}
}

}}}} // clever::packages::std::file
