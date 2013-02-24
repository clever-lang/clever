/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/db/db_pkg.h"

namespace clever { namespace modules {

// Initializes Db package
void Db::init()
{
#ifdef HAVE_MOD_DB_MYSQL
	addModule(new db::MysqlModule);
#endif

#ifdef HAVE_MOD_DB_SQLITE3
	addModule(new db::SQLite3Module);
#endif
}

}} // clever::modules
