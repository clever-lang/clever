/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/cthread.h"
#include "core/value.h"
#include "types/function.h"
#include "core/pkgmanager.h"
#include "modules/std/unicode/unicode.h"
#include "modules/std/unicode/string.h"

namespace clever { namespace packages { namespace std {

/// Initializes Standard Unicode module
CLEVER_MODULE_INIT(UnicodeModule)
{
	addType(CSTRING("UString"), new UString);
}

}}} // clever::packages::std
