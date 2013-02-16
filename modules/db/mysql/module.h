/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_MYSQL_MODULE_H
#define CLEVER_DB_MYSQL_MODULE_H

#include "core/module.h"

namespace clever { namespace modules { namespace db {

/// Mysql Module
class MysqlModule : public Module {
public:
	MysqlModule()
		: Module("db.mysql") {}

	~MysqlModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(MysqlModule);
};

}}} // clever::modules::db

#endif // CLEVER_DB_MYSQL_MODULE_H
