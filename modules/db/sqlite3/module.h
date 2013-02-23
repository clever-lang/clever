/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_MOD_SQLITE3_H
#define CLEVER_DB_MOD_SQLITE3_H

#include "core/module.h"

namespace clever { namespace modules { namespace db {

class SQLite3Module : public Module {
public:
	SQLite3Module()
		: Module("db.sqlite3") {}

	~SQLite3Module() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(SQLite3Module);
};

}}} // clever::modules::db

#endif // CLEVER_DB_MOD_SQLITE3_H
