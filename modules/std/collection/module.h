/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_COLLECTION_H
#define CLEVER_STD_COLLECTION_H

#include "core/module.h"

namespace clever { namespace modules { namespace std {

/// Standard Collection Module
class CollectionModule : public Module {
public:
	CollectionModule()
		: Module("std.collection") {}

	~CollectionModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(CollectionModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_COLLECTION_H
