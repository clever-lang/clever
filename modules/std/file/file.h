/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FILE_H
#define CLEVER_STD_FILE_H

#include "core/module.h"

namespace clever { namespace packages { namespace std {

/// Standard File Module
class FileModule : public Module {
public:
	FileModule()
		: Module("file") { }

	~FileModule() {
	}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(FileModule);
};

}}} // clever::packages::std

#endif // CLEVER_STD_FILE_H
