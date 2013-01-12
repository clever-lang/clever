/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CFILE_H
#define CLEVER_STD_CFILE_H

#include "types/type.h"

namespace clever { namespace packages { namespace std {

class CFile : public Type {
public:
	CFile()
		: Type(CSTRING("File")) {}

	~CFile() {}

	void dump(const void* data) const;
	void dump(const void* data, ::std::ostream& out) const;

	virtual void increment(Value*) const {}
	virtual void decrement(Value*) const {}

	void init();

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD_D(read);
	CLEVER_METHOD_D(readLine);
	CLEVER_METHOD_D(write);
	CLEVER_METHOD_D(open);
	CLEVER_METHOD_D(close);
	CLEVER_METHOD_D(isOpen);
};

}}} // clever::packages::std

#endif // CLEVER_STD_CFILE_H
