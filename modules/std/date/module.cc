/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */
#include "core/value.h"
#include "core/pkgmanager.h"
#include "modules/std/date/module.h"
#include "modules/std/date/date.h"

namespace clever { namespace packages { namespace std {

/// Initializes Standard Date Module
CLEVER_MODULE_INIT(DateModule)
{
	addType(CSTRING("Date"), new Date);
}

}}} // clever::packages::std
