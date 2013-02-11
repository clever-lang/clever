/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CFILE_H
#define CLEVER_STD_CFILE_H

#include <fstream>
#include "types/type.h"

namespace clever { namespace modules { namespace std {

class CFileStream : public TypeObject {
public:
	CFileStream(const char* src, ::std::ios_base::openmode mode)
		: m_fstream(src, mode) {}

	~CFileStream() {}

	::std::fstream& getStream() { return m_fstream; }
private:
	::std::fstream m_fstream;

	DISALLOW_COPY_AND_ASSIGN(CFileStream);
};

class CFile : public Type {
public:
	CFile()
		: Type(CSTRING("File")) {}

	~CFile() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*, const VM*, CException*) const {}
	virtual void decrement(Value*, const VM*, CException*) const {}

	void init();

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);
private:
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(read);
	CLEVER_METHOD(readLine);
	CLEVER_METHOD(write);
	CLEVER_METHOD(open);
	CLEVER_METHOD(close);
	CLEVER_METHOD(isOpen);

	DISALLOW_COPY_AND_ASSIGN(CFile);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CFILE_H
