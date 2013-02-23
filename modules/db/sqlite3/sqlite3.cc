#include "core/cexception.h"
#include "modules/db/sqlite3/sqlite3.h"

namespace clever { namespace modules { namespace db {

TypeObject* SQLite3::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	return new SQLite3Conn(*(*args)[0]->getStr());
}

// SQLite3 constructor
CLEVER_METHOD(SQLite3::ctor)
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

CLEVER_METHOD(SQLite3::exec)
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

// SQLite3 type initialization
CLEVER_TYPE_INIT(SQLite3::init)
{
	setConstructor((MethodPtr)&SQLite3::ctor);

	addMethod(new Function("exec", (MethodPtr)&SQLite3::exec));
}

}}} // clever::modules::std
