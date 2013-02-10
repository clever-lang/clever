/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_USER_H
#define CLEVER_USER_H

#include "core/module.h"
#include "types/type.h"
#include "core/cstring.h"

namespace clever {

class Environment;

// User object representation
class UserObject {
public:
	UserObject()
		: m_env(NULL) {}

	~UserObject() {}

	void setEnvironment(Environment* env) { m_env = env; }
	Environment* getEnvironment() const { return m_env; }

	void addMember(const CString* name, Value* value) {
		m_members.insert(MemberMap::value_type(name, value));
	}

	Value* getMember(const CString* name) const {
		MemberMap::const_iterator it = m_members.find(name);

		if (it != m_members.end()) {
			return it->second;
		}

		return NULL;
	}
private:
	Environment* m_env;
	MemberMap m_members;

	DISALLOW_COPY_AND_ASSIGN(UserObject);
};

// User type representation
class UserType : public Type {
public:
	UserType(const CString* name)
		: Type(name, USER_TYPE), m_env(NULL) {}

	~UserType() {}

	void setEnvironment(Environment* env) { m_env = env; }
	Environment* getEnvironment() const { return m_env; }

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new UserObject; }

	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<UserObject*>(data); }

	virtual void dump(const void*) const {}
	virtual void dump(const void*, std::ostream& out) const {}

	void init(CLEVER_TYPE_INIT_ARGS) {
		Function* ctor = new Function(*getName(), (MethodPtr) &UserType::ctor);
		setConstructor(ctor);
		addMethod(ctor);
	}

	CLEVER_METHOD(ctor) {
		result->setObj(this, allocData(&args));
	}
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
