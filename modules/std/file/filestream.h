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

#ifndef CLEVER_FILESTREAM_H
#define CLEVER_FILESTREAM_H

#include <fstream>
#include "types/type.h"
#include "compiler/value.h"
#include "modules/std/file/filestreamvalue.h"

namespace clever { namespace packages { namespace std { namespace file {

class FileStream : public Type {
public:
	FileStream() :
		Type(CSTRING("FileStream")) { }

	void init();
	DataValue* allocateValue() const;
	void destructor(Value* value) const;

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(open);
	static CLEVER_METHOD(close);
	static CLEVER_METHOD(read);
	static CLEVER_METHOD(write);
	static CLEVER_METHOD(writeLine);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(do_assign);
private:
	DISALLOW_COPY_AND_ASSIGN(FileStream);

	static ::std::ios::openmode convertOpenMode(const ::std::string& modeString);
};

}}}} // clever::packages::std::file

#endif // CLEVER_INT_H
