/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/db/sqlite3/module.h"
#include "modules/db/sqlite3/sqlite3.h"

namespace clever { namespace modules { namespace db {

CLEVER_MODULE_INIT(SQLite3Module)
{
	addType(new SQLite3);
}

}}} // clever::modules::db
