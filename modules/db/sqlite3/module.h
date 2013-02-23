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
		: Module("db.sqlite3"), m_result(NULL), m_stmt(NULL) {}

	~SQLite3Module() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;

	const Type* getResultType() const { return m_result; }
	const Type* getStmtType() const { return m_stmt; }
private:
	Type* m_result;
	Type* m_stmt;

	DISALLOW_COPY_AND_ASSIGN(SQLite3Module);
};

}}} // clever::modules::db

#endif // CLEVER_DB_MOD_SQLITE3_H
