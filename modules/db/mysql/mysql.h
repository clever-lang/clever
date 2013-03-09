/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_MYSQL_H
#define CLEVER_DB_MYSQL_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/db/mysql/cmysql.h"

namespace clever { namespace modules { namespace db {

class MysqlObject : public TypeObject {
public:
	MysqlObject() {}

	~MysqlObject() {}

	CMysql& getMysql() { return m_mysql; }

private:
	CMysql m_mysql;

	DISALLOW_COPY_AND_ASSIGN(MysqlObject);
};

class Mysql : public Type {
public:
	Mysql()
		: Type("Mysql") {}

	~Mysql() {}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(connect);
	CLEVER_METHOD(query);
	CLEVER_METHOD(fetchRow);
	CLEVER_METHOD(getErrorNumber);
	CLEVER_METHOD(getError);

private:
	DISALLOW_COPY_AND_ASSIGN(Mysql);
};

}}} // clever::modules::db

#endif // CLEVER_DB_MYSQL_H
