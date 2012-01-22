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
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "modules/std/file/filestream.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace file {

::std::ios::openmode FileStream::convertOpenMode(const ::std::string& modeString) {
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
 * FileStream::FileStream([String file, [String openmode]])
 * A representation of this class as a string
 */
CLEVER_TYPE_METHOD(FileStream::constructor) {
	FileStreamValue* fsv = new FileStreamValue;

	if (args != NULL) {
		if (CLEVER_NUM_ARGS() == 1) {
			fsv->m_fstream.open(CLEVER_ARG_STR(0).c_str());
		}
		else if (CLEVER_NUM_ARGS() == 2) {
			fsv->m_fstream.open(CLEVER_ARG_STR(0).c_str(), convertOpenMode(CLEVER_ARG(1)->getString()));
		}
	}
	
	fsv->setReference(0);

	CLEVER_RETURN_DATA_VALUE(fsv);
}

/**
 * FileStream::toString()
 * A representation of this class as a string
 */
CLEVER_TYPE_METHOD(FileStream::toString) {
	CLEVER_RETURN_STR(CSTRING("FileStream class"));
}

/**
 * Void FileStream::__assign__(FileStream)
 */
CLEVER_TYPE_METHOD(FileStream::do_assign) {
	CLEVER_ARG(0)->getDataValue()->addRef();
	CLEVER_THIS()->copy(CLEVER_ARG(0));
}

/**
 * FileStream::open(String file, [String mode])
 * Open a file
 */
CLEVER_TYPE_METHOD(FileStream::open) {
	size_t size = CLEVER_NUM_ARGS();
	FileStreamValue* fsv = CLEVER_GET_VALUE(FileStreamValue*, value);

	if (size == 2) {
		fsv->m_fstream.open(CLEVER_ARG(0)->toString().c_str(), convertOpenMode(CLEVER_ARG(1)->toString()));
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
	FileStreamValue* fsv = CLEVER_GET_VALUE(FileStreamValue*, value);

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
	size_t size = CLEVER_NUM_ARGS();

	if (size != 1) {
		Compiler::error("calling Filestream::read([String, Int, Double]) :"
			" wrong number of arguments given");
	}

	fsv = CLEVER_GET_VALUE(FileStreamValue*, value);

	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling Filestream::read([String, Int, Double])"
			" : no file stream is open (use Filestream::open() before)");
	}

	// @TODO: should test if the stream allows reading.

	if (CLEVER_ARG_IS_INT(0)) {
		uint64_t val;
		fsv->m_fstream >> val;

		CLEVER_ARG(0)->setInteger(val);
	} else if (CLEVER_ARG_IS_DOUBLE(0)) {
		double val;
		fsv->m_fstream >> val;

		CLEVER_ARG(0)->setDouble(val);
	} else if (CLEVER_ARG_IS_STR(0)) {
		::std::string val;
		fsv->m_fstream >> val;

		CLEVER_ARG(0)->setString(CSTRING(val));
	}
	// @TODO : support more "native" types
	//else if (CLEVER_ARG(0)->isBoolean()) {
	//	bool val;
	//	m_fstream >> val;
	//
	//	CLEVER_ARG(0)->setBoolean(val);
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
	size_t size = CLEVER_NUM_ARGS();

	if (size != 1) {
		Compiler::error("calling FileStream::write([String])) :"
			"wrong number of arguments given");
	}

	fsv = CLEVER_GET_VALUE(FileStreamValue*, value);

	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling FileStream::write([Objext]) :"
			"no file stream is open (use Filestream::open() before)");
	}

	// @TODO: should check if the stream allows writing.

	// Write the String.
	fsv->m_fstream << CLEVER_ARG_STR(0);

	retval->setType(Value::NONE);
}

/**
 * FileStreasm::writeLine([String])
 * Writes n String into the filestream, and then a new line.
 */
CLEVER_TYPE_METHOD(FileStream::writeLine) {
	FileStreamValue *fsv;
	size_t size = CLEVER_NUM_ARGS();

	if (size != 1) {
		Compiler::error("calling FileStream::writeLine([String])) :"
			"wrong number of arguments given");
	}

	fsv = CLEVER_GET_VALUE(FileStreamValue*, value);

	if (!fsv->m_fstream.is_open()) {
		Compiler::error("calling FileStream::writeLine([Objext]) :"
			"no file stream is open (use Filestream::open() before)");
	}

	// Write the String.
	fsv->m_fstream << CLEVER_ARG_STR(0);

	// Write a new line.
	fsv->m_fstream << ::std::endl;

	retval->setType(Value::NONE);
}

void FileStream::init() {
	const Type* fstream = CLEVER_TYPE("FileStream");
	
	addMethod(
		(new Method(CLEVER_OPERATOR_ASSIGN, (MethodPtr)&FileStream::do_assign, CLEVER_VOID))
			->addArg("rvalue", fstream)
	);

	addMethod(new Method(CLEVER_CTOR_NAME, (MethodPtr)&FileStream::constructor, fstream));
	
	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&FileStream::constructor, fstream))
			->addArg("filename", CLEVER_STR)
	);

	addMethod(
		(new Method(CLEVER_CTOR_NAME, (MethodPtr)&FileStream::constructor, fstream))
			->addArg("filename", CLEVER_STR)
			->addArg("mode", CLEVER_STR)
	);

	addMethod(new Method("toString", (MethodPtr)&FileStream::toString, CLEVER_STR));

	addMethod(
		(new Method("open", (MethodPtr)&FileStream::open, CLEVER_VOID))
			->addArg("filename", CLEVER_STR)
			->addArg("mode", CLEVER_STR)
	);

	addMethod(new Method("close", (MethodPtr)&FileStream::close, CLEVER_VOID));

	addMethod(
		(new Method("read", (MethodPtr)&FileStream::read, CLEVER_VOID))
			->addArg("output", CLEVER_STR)
	);

	addMethod(
		(new Method("write", (MethodPtr)&FileStream::write, CLEVER_VOID))
			->addArg("data", CLEVER_STR)
	);

	addMethod(
		(new Method("writeLine", (MethodPtr)&FileStream::writeLine,CLEVER_VOID))
			->addArg("data", CLEVER_STR)
	);
}

DataValue* FileStream::allocateValue() const {
	return new FileStreamValue;
}

void FileStream::destructor(DataValue* value) const {
	FileStreamValue* fsv = (FileStreamValue*)value;

	// Just close the stream
	if (fsv && fsv->m_fstream.is_open()) {
		fsv->m_fstream.close();
	}
}

}}}} // clever::packages::std::file
