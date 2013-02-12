/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/cthread.h"
#include "core/value.h"
#include "modules/std/core/function.h"
#include "core/modmanager.h"
#include "modules/std/unicode/unicode.h"
#include "modules/std/unicode/string.h"

namespace clever { namespace modules { namespace std {

/// Initializes Standard Unicode module
CLEVER_MODULE_INIT(UnicodeModule)
{
	addType(new UString);
}

}}} // clever::modules::std
