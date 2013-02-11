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

class Thread : public TypeObject {
public:
	enum ThreadKind { UNDEF, USER_THREAD, INTERNAL_THREAD };

	Thread()
		: m_name(), m_type(UNDEF), m_environment(NULL) {}

	Thread(std::string name)
		: m_name(name), m_type(UNDEF), m_environment(NULL) {}

	Thread(std::string name, size_t addr)
		: m_name(name), m_type(UNDEF), m_environment(NULL) { m_addr = addr; }

	~Thread() {}

	void setName(std::string name) { m_name = name; }
	const std::string& getName() const { return m_name; }

	void setInternal() { m_type = INTERNAL_THREAD; }
	void setUserDefined() { m_type = USER_THREAD; }

	bool isUserDefined() const { return m_type == USER_THREAD; }
	bool isInternal() const { return m_type == INTERNAL_THREAD; }

	size_t getAddr() const { return m_addr; }
	size_t getID() const { return m_thread_id; }
	size_t getNThreads() const { return m_n_threads; }

	void setAddr(size_t addr) { m_addr = addr; }
	void setID(size_t id) { m_thread_id = id; }
	void setNThreads(size_t n) { m_n_threads = n; }

	Environment* getEnvironment() const { return m_environment; }
	void setEnvironment(Environment* e) { m_environment = e; }
private:
	std::string m_name;
	ThreadKind m_type;
	size_t m_thread_id;
	size_t m_n_threads;
	size_t m_addr;

	Environment* m_environment;

	DISALLOW_COPY_AND_ASSIGN(Thread);
};

/// Thread type
class ThreadType : public Type {
public:
	ThreadType()
		: Type(CSTRING("Thread")) {}

	~ThreadType() {}

	void init();

	void dump(TypeObject* data, std::ostream& out) const { out << "Thread() {}"; }

	TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const { return new Thread; }

	void deallocData(CLEVER_TYPE_DTOR_ARGS) { delete static_cast<Thread*>(data); }

	CLEVER_METHOD(run);
	CLEVER_METHOD(wait);
	CLEVER_METHOD(toString);
private:
	DISALLOW_COPY_AND_ASSIGN(ThreadType);
};

} // clever

#endif // CLEVER_TYPES_THREAD_H
