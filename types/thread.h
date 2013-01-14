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
		: ValueObject(), m_name(), m_type(UNDEF), m_environment(NULL) {}

	Thread(std::string name)
		: ValueObject(), m_name(name), m_type(UNDEF), m_environment(NULL) {}

	Thread(std::string name, size_t addr)
		: ValueObject(), m_name(name), m_type(UNDEF), m_environment(NULL)
		{ m_info.addr = addr; }

	~Thread() {}

	void setName(std::string name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setInternal() { m_type = INTERNAL_THREAD; }
	void setUserDefined() { m_type = USER_THREAD; }

	bool isUserDefined() const { return m_type == USER_THREAD; }
	bool isInternal() const { return m_type == INTERNAL_THREAD; }

	size_t getAddr() const { return m_info.addr; }
	size_t getID() const { return m_thread_id; }

	void setAddr(size_t addr) { m_info.addr = addr; }
	void setID(size_t ID) { m_thread_id = ID; }

	Environment* getEnvironment() { return m_environment; }
	void setEnvironment(Environment* e) {
		m_environment = e;
	}
private:
	std::string m_name;
	ThreadKind m_type;
	size_t m_thread_id;

	union {
		size_t addr;
	} m_info;

	Environment* m_environment;

	DISALLOW_COPY_AND_ASSIGN(Thread);
};


/// Thread type
class ThreadType : public Type {
public:
	ThreadType()
		: Type(CSTRING("Thread")) {}

	~ThreadType() {}

	void dump(const void* data) const { dump(data, std::cout); }
	void dump(const void* data, std::ostream& out) const { out << "Thread() {}"; }

	void* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new Thread; }

	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<Thread*>(data); }
};

} // clever

#endif // CLEVER_TYPES_THREAD_H
