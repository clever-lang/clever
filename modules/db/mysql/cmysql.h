/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_DB_CMYSQL_H
#define CLEVER_DB_CMYSQL_H

#include <iostream>

#include <mysql/mysql.h>

#include "core/cstring.h"
#include "core/value.h"
#include "types/type.h"
#include "modules/std/core/map.h"


namespace clever {


class CMysql {
public:
	CMysql()
		: m_connection(NULL), m_port(3306), m_resultset(NULL) { init(); }

	~CMysql() {}

	void setHost(const std::string& host)     { m_host = host;     }
	void setUser(const std::string& user)     { m_user = user;     }
	void setPasswd(const std::string& passwd) { m_passwd = passwd; }
	void setDb(const std::string& db)         { m_db = db;         }
	void setPort(int port)                    { m_port = port;     }

	bool connect();
	int query(const char *stmt);
	MapObject* fetchRow();
	std::string dump();
private:

	void init();

	MYSQL* m_connection;

	std::string m_host;
	std::string m_user;
	std::string m_passwd;
	std::string m_db;

	int m_port;

	MYSQL_RES* m_resultset;

	DISALLOW_COPY_AND_ASSIGN(CMysql);
};

} // clever

#endif // CLEVER_DB_CMYSQL_H
