#include "core/cexception.h"
#include "modules/db/sqlite3/sqlite3.h"
#include "modules/std/core/map.h"

namespace clever { namespace modules { namespace db {

TypeObject* SQLite3Type::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new SQLite3Conn(*(*args)[0]->getStr());
}

// SQLite3 constructor
CLEVER_METHOD(SQLite3Type::ctor)
{
	if (!clever_check_args("s")) {
		return;
	}

	SQLite3Conn* conn = static_cast<SQLite3Conn*>(allocData(&args));

	if (sqlite3_open(args[0]->getStr()->c_str(), &conn->handle) != SQLITE_OK) {
		clever_throw("An error occurred when opening database: %s",
			sqlite3_errmsg(conn->handle));

		clever_delref(conn);
		return;
	}

	result->setObj(this, conn);
}

// SQLite3::exec(String pattern)
CLEVER_METHOD(SQLite3Type::exec)
{
	if (!clever_check_args("s")) {
		return;
	}

	SQLite3Conn* conn = CLEVER_GET_OBJECT(SQLite3Conn*, CLEVER_THIS());
	char* errmsg = NULL;

	sqlite3_exec(conn->handle,
		args[0]->getStr()->c_str(),
		NULL,
		NULL,
		&errmsg);

	if (errmsg) {
		clever_throw("An error occurred when executing a statement: %s",
			errmsg);

		sqlite3_free(errmsg);
	}
}

// SQLite3::query(String query)
CLEVER_METHOD(SQLite3Type::query)
{
	if (!clever_check_args("s")) {
		return;
	}

	SQLite3Conn* conn = CLEVER_GET_OBJECT(SQLite3Conn*, CLEVER_THIS());
	sqlite3_stmt* stmt;

	if (sqlite3_prepare_v2(conn->handle,
		args[0]->getStr()->c_str(),
		args[0]->getStr()->size(),
		&stmt,
		NULL) != SQLITE_OK) {
		clever_throw("An error occurred when preparing query: %s",
			sqlite3_errmsg(conn->handle));
		return;
	}

	switch (sqlite3_step(stmt)) {
		case SQLITE_DONE:
		case SQLITE_ROW:
			sqlite3_reset(stmt);
			break;
		case SQLITE_ERROR:
			clever_throw("%s", sqlite3_errmsg(conn->handle));
			return;
	}

	result->setObj(m_module->getResultType(), new SQLite3Result(stmt));
}

static Value* _sqlite_to_value(sqlite3_stmt* stmt, int column)
{
	Value* value = new Value;

	switch (sqlite3_column_type(stmt, column)) {
		case SQLITE_INTEGER:
			value->setInt(sqlite3_column_int64(stmt, column));
			break;
	}

	return value;
}

// SQLite3Result::fetch()
CLEVER_METHOD(SQLite3TypeResult::fetch)
{
	if (!clever_check_no_args()) {
		return;
	}

	SQLite3Result* res = CLEVER_GET_OBJECT(SQLite3Result*, CLEVER_THIS());
	int ret_code = sqlite3_step(res->stmt);

	if (ret_code != SQLITE_ROW) {
		result->setBool(false);
	}

	MapObject* map = new MapObject;

	for (int i = 0, n = sqlite3_data_count(res->stmt); i < n; ++i) {
		std::string name(sqlite3_column_name(res->stmt, i));

		map->getData().insert(MapObjectPair(name, _sqlite_to_value(res->stmt, i)));
	}

	result->setObj(CLEVER_MAP_TYPE, map);
}

// SQLite3 type initialization
CLEVER_TYPE_INIT(SQLite3Type::init)
{
	setConstructor((MethodPtr)&SQLite3Type::ctor);

	addMethod(new Function("exec",  (MethodPtr)&SQLite3Type::exec));
	addMethod(new Function("query", (MethodPtr)&SQLite3Type::query));
}

// SQLite3Stmt type initialization
CLEVER_TYPE_INIT(SQLite3TypeStmt::init)
{
}

// SQLite3Stmt type initialization
CLEVER_TYPE_INIT(SQLite3TypeResult::init)
{
	addMethod(new Function("fetch", (MethodPtr)&SQLite3TypeResult::fetch));
}

}}} // clever::modules::std
