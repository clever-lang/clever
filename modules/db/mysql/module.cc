/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/db/mysql/module.h"
#include "modules/db/mysql/mysql.h"

namespace clever { namespace modules { namespace db {

/// Initializes Mysql module
CLEVER_MODULE_INIT(MysqlModule)
{
	addType(CSTRING("Mysql"), new Mysql);
}

}}} // clever::modules::db
