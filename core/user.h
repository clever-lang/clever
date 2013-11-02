/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_USER_H
#define CLEVER_USER_H

#include "core/module.h"
#include "core/type.h"
#include "core/cstring.h"

namespace clever {

class Environment;

// User object representation
class UserObject : public TypeObject {
public:
	UserObject()
		: m_env(NULL) {}

	~UserObject() {}

	void setEnvironment(Environment* env) { m_env = env; }
	Environment* getEnvironment() const { return m_env; }
private:
	Environment* m_env;

	DISALLOW_COPY_AND_ASSIGN(UserObject);
};

// User type representation
class UserType : public Type {
public:
	UserType(const CString* name)
		: Type(*name, USER_TYPE), m_env(NULL) {}

	~UserType() {}

	virtual void init() {
		setConstructor((MethodPtr)&UserType::ctor);
		setDestructor((MethodPtr)&UserType::dtor);
	}

	void setEnvironment(Environment* env) { m_env = env; }
	Environment* getEnvironment() const { return m_env; }

	CLEVER_METHOD(ctor) {
		result->setObj(this, new UserObject);
	}

	CLEVER_METHOD(dtor) {}
private:
	Environment* m_env;

	DISALLOW_COPY_AND_ASSIGN(UserType);
};

// User module representation
class UserModule: public Module {
public:
	UserModule()
		: Module("_user") {}

	~UserModule() {}

	void init() {}
private:
	DISALLOW_COPY_AND_ASSIGN(UserModule);
};

} // clever

#endif // CLEVER_USER_H
