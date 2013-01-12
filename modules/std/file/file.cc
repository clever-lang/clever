/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/file/file.h"
#include "modules/std/file/cfile.h"

namespace clever { namespace packages { namespace std {

namespace file {

} // clever::packages::std::file

/// Initializes Standard File module
CLEVER_MODULE_INIT(FileModule) {
	using namespace file;

	addType(CSTRING("File"), new CFile);
}

}}} // clever::packages::std
