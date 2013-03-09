/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_SQLITE3_H
#define CLEVER_DB_SQLITE3_H

#include <utility>
#include <string>
#include <sqlite3.h>
#include "core/type.h"
#include "core/module.h"
#include "modules/db/sqlite3/module.h"

namespace clever { namespace modules { namespace db {

class SQLite3Type;
struct SQLite3Conn;

struct SQLite3Result : public TypeObject {
	SQLite3Result(sqlite3_stmt* stmt_)
		: stmt(stmt_) {}

	~SQLite3Result() {
		sqlite3_finalize(stmt);
	}

	sqlite3_stmt* stmt;
};

typedef std::pair<int, Value*> BoundParamPair;

struct SQLite3Stmt : public TypeObject {
	SQLite3Stmt(sqlite3_stmt* stmt_, SQLite3Conn* conn_)
		: stmt(stmt_), conn(conn_) {}

	~SQLite3Stmt() {
		sqlite3_finalize(stmt);
	}

	void clear() {
		std::vector<BoundParamPair>::const_iterator it(bound_params.begin()),
			end(bound_params.end());

		for (; it != end; ++it) {
			clever_delref(it->second);
		}
		bound_params.clear();
	}

	sqlite3_stmt* stmt;
	SQLite3Conn* conn;
	std::vector<BoundParamPair> bound_params;
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
	std::vector<TypeObject*> results;
};

class SQLite3TypeResult : public Type {
public:
	SQLite3TypeResult(const SQLite3Type* parent_type)
		: Type("SQLite3Result"), m_sqlite3_type(parent_type) {}

	~SQLite3TypeResult() {}

	virtual void init();

	const SQLite3Type* getParentType() const { return m_sqlite3_type; }

	// Methods
	CLEVER_METHOD(fetch);
	CLEVER_METHOD(finalize);
private:
	const SQLite3Type* m_sqlite3_type;
};

class SQLite3TypeStmt : public Type {
public:
	SQLite3TypeStmt(const SQLite3Type* parent_type)
		: Type("SQLite3Stmt"), m_sqlite3_type(parent_type) {}

	~SQLite3TypeStmt() {}

	virtual void init();

	const SQLite3Type* getParentType() const { return m_sqlite3_type; }

	// Methods
	CLEVER_METHOD(bindValue);
	CLEVER_METHOD(execute);
private:
	const SQLite3Type* m_sqlite3_type;
};

class SQLite3Type: public Type {
public:
	SQLite3Type()
		: Type("SQLite3") {}

	~SQLite3Type() {}

	virtual void init();

	SQLite3TypeResult* result_type;
	SQLite3TypeStmt* stmt_type;

	SQLite3TypeResult* getResultType() const { return result_type; }
	SQLite3TypeStmt* getStmtType() const { return stmt_type; }

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(exec);
	CLEVER_METHOD(query);
	CLEVER_METHOD(prepare);
	CLEVER_METHOD(getLastId);
	CLEVER_METHOD(close);
};

}}} // clever::modules::db

#endif // CLEVER_DB_SQLITE3_H
