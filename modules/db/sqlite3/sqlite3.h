/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_SQLITE3_H
#define CLEVER_DB_SQLITE3_H

#include <sqlite3.h>
#include "types/type.h"
#include "core/module.h"

namespace clever { namespace modules { namespace db {

struct SQLite3Conn : public TypeObject {
	SQLite3Conn(const std::string& file)
		: fname(file), handle(NULL) {}

	~SQLite3Conn() {
		if (handle) {
			sqlite3_close(handle);
		}
	}

	// File name
	std::string fname;
	// SQLite3 db handle
	sqlite3* handle;
};

class SQLite3 : public Type {
public:
	SQLite3()
		: Type("SQLite3") {}

	~SQLite3() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(exec);
};

}}} // clever::modules::db

#endif // CLEVER_DB_SQLITE3_H
