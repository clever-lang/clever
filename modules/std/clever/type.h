/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_MOD_CLEVER_TYPE_H
#define CLEVER_MOD_CLEVER_TYPE_H

#include "core/type.h"
#include <iostream>

namespace clever { namespace modules { namespace std {

class CleverType : public Type {
public:
	CleverType()
		: Type("Clever") {}

	~CleverType() {}

	void init();

	CLEVER_METHOD(buildDate);
	CLEVER_METHOD(hasThreads);
	CLEVER_METHOD(getVersion);
	CLEVER_METHOD(getStringVersion);
};

}}} // clever::modules::std

#endif // CLEVER_MOD_CLEVER_TYPE_H
