/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_TYPES_THREAD_H
#define CLEVER_TYPES_THREAD_H

#include <vector>
#include "core/clever.h"
#include "core/value.h"
#include "core/environment.h"
#include "types/type.h"

namespace clever {

class Value;
class VM;
class Scope;

class Thread: public ValueObject {
public:
	enum ThreadKind { UNDEF, USER_THREAD, INTERNAL_THREAD };

	Thread()
		: ValueObject(), m_name(), m_type(UNDEF), m_local_vars(NULL), m_environment(NULL) {}

	Thread(std::string name)
		: ValueObject(), m_name(name), m_type(UNDEF), m_local_vars(NULL), m_environment(NULL)
		{ }

	Thread(std::string name, size_t addr)
		: ValueObject(), m_name(name), m_type(UNDEF), m_local_vars(NULL), m_environment(NULL)
		{ m_info.addr = addr; }

	~Thread() {}

	void setName(std::string name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setInternal() { m_type = INTERNAL_THREAD; }
	void setUserDefined() { m_type = USER_THREAD; }

	bool isUserDefined() const { return m_type == USER_THREAD; }
	bool isInternal() const { return m_type == INTERNAL_THREAD; }

	size_t getAddr() const { return m_info.addr; }

	void setAddr(size_t addr) { m_info.addr = addr; }

	Scope* getLocalVars() { return m_local_vars; }


	void setLocalVars(Scope* local_vars) { m_local_vars = local_vars; }

	Environment* getEnvironment() { return m_environment; }
	void setEnvironment(Environment* e) {
		m_environment = e;
	}
private:
	std::string m_name;
	ThreadKind m_type;

	union {
		size_t addr;
	} m_info;

	/// Local variables
	Scope* m_local_vars;

	Environment* m_environment;
};


/// Thread type
class ThreadType : public Type {
public:
	ThreadType() : Type(CSTRING("Thread")) {}
	~ThreadType() {}

	void dump(const void* data) const { dump(data, std::cout); }
	void dump(const void* data, std::ostream& out) const { out << "Thread() { }"; }

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new Thread; }

	void deallocData(void* data) { if (data) { delete static_cast<Thread*>(data); } }

	void increment(Value* value) const {}

	void decrement(Value* value) const {}
};

} // clever

#endif // CLEVER_TYPES_THREAD_H
