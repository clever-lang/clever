/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "core/native_types.h"
#include "modules/db/mysql/mysql.h"
#include "modules/db/mysql/cmysql.h"

namespace clever { namespace modules { namespace db {

CLEVER_METHOD(Mysql::ctor)
{
	result->setObj(this, new MysqlObject);
}

CLEVER_METHOD(Mysql::connect)
{
	if (!clever_check_args("ssss|i")) {
		return;
	}

	bool ret = false;
	MysqlObject* mo = clever_get_this(MysqlObject*);
	CMysql& cmysql = mo->getMysql();

	switch (args.size()) {
		case 5:
			cmysql.setPort(args[4]->getInt());
		case 4:
			cmysql.setHost(*args[0]->getStr());
			cmysql.setUser(*args[1]->getStr());
			cmysql.setPasswd(*args[2]->getStr());
			cmysql.setDb(*args[3]->getStr());

			ret = cmysql.connect();
			break;
	}

	result->setBool(ret);
}

CLEVER_METHOD(Mysql::query)
{
	if (!clever_check_args("s")) {
		return;
	}

	MysqlObject* mo = clever_get_this(MysqlObject*);
	CMysql& cmysql = mo->getMysql();

	result->setBool(cmysql.query(args[0]->getStr()->c_str()));
}

CLEVER_METHOD(Mysql::fetchRow)
{
	if (!clever_check_no_args()) {
		return;
	}

	MysqlObject* mo = clever_get_this(MysqlObject*);
	CMysql& cmysql = mo->getMysql();

	MapObject* data = cmysql.fetchRow();

	if(data != NULL) {
		result->setObj(CLEVER_MAP_TYPE, data);
	} else {
		result->setNull();
	}
}

CLEVER_METHOD(Mysql::getErrorNumber)
{
	if (!clever_check_no_args()) {
		return;
	}

	MysqlObject* mo = clever_get_this(MysqlObject*);
	CMysql& cmysql = mo->getMysql();

	result->setInt(cmysql.errno());
}

CLEVER_METHOD(Mysql::getError)
{
	if (!clever_check_no_args()) {
		return;
	}

	MysqlObject* mo = clever_get_this(MysqlObject*);
	CMysql& cmysql = mo->getMysql();

	result->setStr(CSTRING(cmysql.error()));
}

// Type initialization
CLEVER_TYPE_INIT(Mysql::init)
{
	setConstructor((MethodPtr) &Mysql::ctor);

	addMethod(new Function("connect",        (MethodPtr) &Mysql::connect));
	addMethod(new Function("query",          (MethodPtr) &Mysql::query));
	addMethod(new Function("fetchRow",       (MethodPtr) &Mysql::fetchRow));
	addMethod(new Function("getErrorNumber", (MethodPtr) &Mysql::getErrorNumber));
	addMethod(new Function("getError",       (MethodPtr) &Mysql::getError));
}

}}} // clever::modules::db
