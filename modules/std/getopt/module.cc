/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/std/getopt/module.h"

namespace clever { namespace modules { namespace std {

namespace getopt {

static CLEVER_FUNCTION(getopt)
{

}

} // clever::modules::std::getopt

CLEVER_MODULE_INIT(GetoptModule)
{
	addFunction(new Function("getopt", &CLEVER_NS_FNAME(getopt, getopt)));
}

}}} // clever::modules::std
