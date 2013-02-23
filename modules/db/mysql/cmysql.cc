/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <stdio.h>
#include <stdlib.h>

#include <mysql/mysql.h>
#include "modules/db/mysql/cmysql.h"
#include "modules/std/core/map.h"

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
	
	int ret = mysql_query(m_connection, stmt);

	m_resultset = mysql_use_result(m_connection);
	if(m_resultset == NULL) {
		// TODO: What to do here?
		
		if(mysql_errno(m_connection) != 0) {
			printf("Houston la casa callou!\n");
		}

		// Finished reading the data
		return -1;
	}

	return ret;
}

MapObject* CMysql::fetchRow()
{

	MapObject* map = new MapObject;
	Value* value;

	MYSQL_FIELD* fields;
	MYSQL_ROW row;
	
	unsigned int cnt_cols;
	unsigned long* lengths;
	char* str;

	row = mysql_fetch_row(m_resultset);

	// No more data or no data at all!
	if(row == NULL) {
		m_resultset = NULL;
		return NULL;
	}

	cnt_cols = mysql_num_fields(m_resultset);
	lengths = mysql_fetch_lengths(m_resultset);
	fields = mysql_fetch_fields(m_resultset);
	
	for(unsigned int i = 0; i < cnt_cols; i++) {

		str = new char[lengths[i]+1];
		snprintf(str, lengths[i]+1, "%.*s", (int)lengths[i], row[i]);

		switch(fields[i].type) {
			case MYSQL_TYPE_TINY:
			case MYSQL_TYPE_SHORT:
			case MYSQL_TYPE_LONG:
			case MYSQL_TYPE_INT24:
			case MYSQL_TYPE_TIMESTAMP:
				value = new Value(long(strtol((char *)str, NULL, 10)), false);
				break;

			case MYSQL_TYPE_DATE:
			case MYSQL_TYPE_TIME:
			case MYSQL_TYPE_DATETIME:
			case MYSQL_TYPE_YEAR:
			case MYSQL_TYPE_BLOB:
			case MYSQL_TYPE_SET:
			case MYSQL_TYPE_ENUM:
			case MYSQL_TYPE_GEOMETRY:
			case MYSQL_TYPE_NULL:
			case MYSQL_TYPE_NEWDATE:
			case MYSQL_TYPE_VARCHAR:
			case MYSQL_TYPE_STRING:
			case MYSQL_TYPE_VAR_STRING:
				value = new Value(CSTRING(str), false);
				break;

			case MYSQL_TYPE_LONGLONG:
				// handle as long long
				break;

			case MYSQL_TYPE_DECIMAL:
			case MYSQL_TYPE_NEWDECIMAL:
			case MYSQL_TYPE_FLOAT:
			case MYSQL_TYPE_DOUBLE:
				// handle as double
				break;

			case MYSQL_TYPE_BIT:
				// handle as bool
				break;

			
			
			case MYSQL_TYPE_TINY_BLOB:
			case MYSQL_TYPE_MEDIUM_BLOB:
			case MYSQL_TYPE_LONG_BLOB:
				// handle as byte array?
				break;

		}

		if(value != NULL) {
			map->getData().insert(MapObjectPair(fields[i].name, value));
		}

		value = NULL;
		delete str;
	}

	return map;
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
