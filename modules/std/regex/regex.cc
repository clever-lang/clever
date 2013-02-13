/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <pcrecpp.h>
#include "modules/std/regex/regex.h"
#include "modules/std/regex/pcre.h"

namespace clever { namespace modules { namespace std {

// Regex module initialization
CLEVER_MODULE_INIT(Regex)
{
	addType(new regex::Pcre);
}

}}} // clever::packages:std
