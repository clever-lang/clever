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
	SQLite3Type* sqlite_type       = new SQLite3Type();
	SQLite3TypeStmt* stmt_type     = new SQLite3TypeStmt(sqlite_type);
	SQLite3TypeResult* result_type = new SQLite3TypeResult(sqlite_type);

	addType(sqlite_type);
	addType(stmt_type);
	addType(result_type);

	sqlite_type->result_type = result_type;
	sqlite_type->stmt_type = stmt_type;
}

}}} // clever::modules::db
