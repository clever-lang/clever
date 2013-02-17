/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <mysql/mysql.h>
#include "modules/db/mysql/cmysql.h"
#include "modules/std/core/array.h"

namespace clever {

void CMysql::init()
{
	m_connection = mysql_init(m_connection);
}

bool CMysql::connect()
{
	MYSQL* conn;

	conn = mysql_real_connect(m_connection, m_host.c_str(), m_user.c_str(),
		m_passwd.c_str(), m_db.c_str(), m_port, NULL, 0);

	// Clean the password as we do not want to keep this in memory
	m_passwd = "";

	return conn != NULL;
}

int CMysql::query(const char *stmt)
{
	return mysql_query(m_connection, stmt);
}

ArrayObject* CMysql::fetchArray()
{
	return m_result_set;
}

std::string CMysql::dump()
{
	std::stringstream strs;

	strs <<  "Host: '" << m_host << "'; "
		 <<  "User: '" << m_user << "'; "
		 <<  "DB: '"   << m_db   << "'; "
		 <<  "Port: '" << m_port << "'; "
		 ;

	return strs.str();
}

} // clever
