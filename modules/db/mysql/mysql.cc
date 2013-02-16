/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "types/native_types.h"
#include "modules/db/mysql/mysql.h"

namespace clever { namespace modules { namespace db {

// Simple constructor for now
// TODO: Build a constructor that can accept the host, port, user and password
TypeObject* Mysql::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	MysqlObject* obj = new MysqlObject();

	return obj;
}

void Mysql::deallocData(void *data)
{
	MysqlObject* intern = static_cast<MysqlObject*>(data);

	if (intern) {
		delete intern;
	}
}

void Mysql::dump(TypeObject* data, ::std::ostream& out) const
{
	const MysqlObject* uvalue = static_cast<const MysqlObject*>(data);

	if (uvalue) {
		out << "Dump for mysql object should go here Mysql::dump";
	}
}

CLEVER_METHOD(Mysql::ctor)
{
	result->setObj(this, allocData(&args));
}

CLEVER_METHOD(Mysql::connect)
{
	::std::cout << "Called connect!";
}

// Type initialization
CLEVER_TYPE_INIT(Mysql::init)
{
	setConstructor((MethodPtr) &Mysql::ctor);

	addMethod(new Function("connect",  (MethodPtr) &Mysql::connect));
}

}}} // clever::modules::db
