/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_SQLITE3_H
#define CLEVER_DB_SQLITE3_H

#include <utility>
#include <sqlite3.h>
#include "types/type.h"
#include "core/module.h"
#include "modules/db/sqlite3/module.h"

namespace clever { namespace modules { namespace db {

struct SQLite3Result : public TypeObject {
	SQLite3Result(sqlite3_stmt* stmt_)
		: stmt(stmt_) {}

	~SQLite3Result() {
		sqlite3_finalize(stmt);
	}

	sqlite3_stmt* stmt;
};

struct SQLite3Stmt : public TypeObject {
	sqlite3_stmt* stmt;
};

struct SQLite3Conn : public TypeObject {
	SQLite3Conn(const std::string& file)
		: fname(file), handle(NULL) {}

	~SQLite3Conn() {
		close();
	}

	int close() {
		int result = SQLITE_OK;

		if (handle) {
			std::for_each(results.begin(), results.end(), clever_delref);
			result = sqlite3_close(handle);
			handle = NULL;
		}

		return result;
	}

	// File name
	std::string fname;
	// SQLite3 db handle
	sqlite3* handle;
	// Vector of results
	std::vector<SQLite3Result*> results;
};

class SQLite3TypeResult : public Type {
public:
	SQLite3TypeResult()
		: Type("SQLite3Result") {}

	~SQLite3TypeResult() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }

	// Methods
	CLEVER_METHOD(fetch);
	CLEVER_METHOD(finalize);
};

class SQLite3TypeStmt : public Type {
public:
	SQLite3TypeStmt()
		: Type("SQLite3Stmt") {}

	~SQLite3TypeStmt() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return NULL; }
};

class SQLite3Type: public Type {
public:
	SQLite3Type(SQLite3Module* mod)
		: Type("SQLite3"), m_module(mod) {}

	~SQLite3Type() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(exec);
	CLEVER_METHOD(query);
	CLEVER_METHOD(getLastId);
	CLEVER_METHOD(close);
private:
	SQLite3Module* m_module;
};

}}} // clever::modules::db

#endif // CLEVER_DB_SQLITE3_H
