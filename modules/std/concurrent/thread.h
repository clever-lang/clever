/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_CONCURRENT_THREAD_H
#define CLEVER_STD_CONCURRENT_THREAD_H

#include <iostream>

#include "core/cstring.h"
#include "types/type.h"

namespace clever { namespace modules { namespace std {

class Thread : public Type {
public:
	Thread()
		: Type("Thread") {}

	~Thread() {}

	void init();
	void dump(TypeObject* data, ::std::ostream& out) const {}

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);

	CLEVER_METHOD(start);
	CLEVER_METHOD(wait);
};

}}} // clever::modules::std

#endif // CLEVER_STD_CONCURRENT_THREAD_H
