/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <fstream>
#include "core/value.h"
#include "core/clever.h"
#include "modules/std/file/cfile.h"
#include "types/type.h"
#include "modules/std/core/function.h"

// @TODO(muriloadriano): make this available and use in all Clever API
#define CLEVER_CAST(Type, obj) (static_cast<Type*>(obj))

using ::std::fstream;

namespace clever { namespace packages { namespace std {

namespace detail {

// Given a mode string returns the according ios flag
::std::ios::openmode convert_open_mode(const CString& mode)
{
	// @TODO(muriloadriano): support binary modes.
	if (mode == "r") {
		return ::std::ios_base::in;
	} else if (mode == "w") {
		return ::std::ios_base::out | ::std::ios_base::trunc;
	} else if (mode == "a") {
		return ::std::ios_base::out | ::std::ios_base::app;
	} else if (mode == "r+") {
		return ::std::ios_base::in | ::std::ios_base::out;
	} else if (mode == "w+") {
		return ::std::ios_base::in | ::std::ios_base::out |
				::std::ios_base::trunc;
	} else if (mode == "a+") {
		return ::std::ios_base::in | ::std::ios_base::out |
				::std::ios_base::app;
	} else {
		// @TODO(muriloadriano): return some kind of error here.
		return ::std::ios_base::in;
	}
}

}

void CFile::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void CFile::dump(const void* data, ::std::ostream& out) const
{
	out << "File class (" << data << ")";
}

// File.new(string fileName, string openMode)
void* CFile::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	// @TODO(muriloadriano): allow object construction with a single argument
	// and check the argument's type
	return new fstream(args->at(0)->getStr()->c_str(),
		detail::convert_open_mode(*(args->at(1)->getStr())));
}

void CFile::deallocData(CLEVER_TYPE_DTOR_ARGS)
{
	delete CLEVER_CAST(fstream*, data);
}

CLEVER_METHOD(CFile::ctor)
{
	if (!clever_check_args("ss")) {
		return;
	}

	result->setObj(this, allocData(&args));
}

// string File.read()
// Return the next token from the current stream
CLEVER_METHOD(CFile::read)
{
	if (!clever_check_no_args()) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());

	CString* token = new CString;
	*file >> *token;

	result->setStr(token);
}

// string File.readLine()
// Return the contents from the current positon until the next line
CLEVER_METHOD(CFile::readLine)
{
	if (!clever_check_no_args()) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());

	CString* token = new CString;
	::std::getline(*file, *token);

	result->setStr(token);
}

// void File.write(String)
// Return the contents from the current positon until the next line
// TODO(muriloadriano): allow use other primitive types as argument
CLEVER_METHOD(CFile::write)
{
	if (!clever_check_args("s")) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());

	*file << *(args[0]->getStr());
}

// void File.open(string fileName, string openMode)
CLEVER_METHOD(CFile::open)
{
	if (!clever_check_args("ss")) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());

	file->open(args[0]->getStr()->c_str(),
		detail::convert_open_mode(*(args[1]->getStr())));
}

// void File.close()
CLEVER_METHOD(CFile::close)
{
	if (!clever_check_no_args()) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());
	file->close();
}

// bool File.isOpen()
CLEVER_METHOD(CFile::isOpen)
{
	if (!clever_check_no_args()) {
		return;
	}

	fstream* file = CLEVER_GET_OBJECT(fstream*, CLEVER_THIS());
	result->setBool(file->is_open());
}

CLEVER_TYPE_INIT(CFile::init)
{
	Function* ctor = new Function("File", (MethodPtr)&CFile::ctor);

	setConstructor(ctor);
	addMethod(ctor);
	addMethod(new Function("read",		(MethodPtr)&CFile::read));
	addMethod(new Function("readLine",	(MethodPtr)&CFile::readLine));
	addMethod(new Function("write",		(MethodPtr)&CFile::write));
	addMethod(new Function("open",		(MethodPtr)&CFile::open));
	addMethod(new Function("close",		(MethodPtr)&CFile::close));
	addMethod(new Function("isOpen",	(MethodPtr)&CFile::isOpen));

	addProperty(CSTRING("in"), new Value(long(::std::ios_base::in), true));
	addProperty(CSTRING("out"), new Value(long(::std::ios_base::out), true));
}

}}} // clever::packages::std
