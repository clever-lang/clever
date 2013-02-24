/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifdef CLEVER_WIN32
# include <direct.h>
# include <windows.h>
#else
# include <dirent.h>
# include <unistd.h>
# include <sys/resource.h>
# include <sys/time.h>
#endif

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/events/events.h"
#include "types/type.h"
#include "core/vm.h"

namespace clever { namespace modules { namespace std {

CLEVER_THREAD_FUNC(_events_handler)
{
	EventData* intern = static_cast<EventData*>(arg);

	while (true) {
		intern->mutex.lock();

		while (!intern->m_event_queue.empty()) {
			Signal u = intern->m_event_queue.front();
			intern->m_event_queue.pop();

			Actions& a = intern->m_event_map[u.first];

			for (Actions::iterator it = a.begin(); it != a.end(); ++it) {
				intern->m_vm->runFunction(*it, &u.second)->delRef();
			}

			if (u.first == "exit") {
				intern->mutex.unlock();
				return NULL;
			}
		}

		intern->mutex.unlock();

#ifdef CLEVER_WIN32
			SleepEx(intern->m_sleep_time, false);
#else
			usleep(intern->m_sleep_time * 1000);
#endif
	}

	return NULL;
}

TypeObject* Events::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	EventData* intern = new EventData;

	if (args->size() > 0) {
		intern->m_sleep_time = static_cast<int>(args->at(0)->getInt());
	} else {
		intern->m_sleep_time = 500;
	}

	intern->handler.create(_events_handler, intern);
	return intern;
}

EventData::~EventData()
{
	if (handler.isRunning()) {
		mutex.lock();

		Signal s;

		s.first = "exit";

		m_event_queue.push(s);

		mutex.unlock();
		handler.wait();
	}

	if (m_vm) {
		delete m_vm;
		m_vm = 0;
	}
}

// Events.new([Int sleep_time])
// Constructs a new Events handler object to manage some events
CLEVER_METHOD(Events::ctor)
{
	if (!clever_check_args("|i")) {
		return;
	}

	EventData* intern = static_cast<EventData*>(allocData(&args));

	intern->m_vm = new VM();
	intern->m_vm->copy(vm, true);
	intern->m_vm->setChild();

	result->setObj(this, intern);
}

// Events.connect(String name, Function func)
CLEVER_METHOD(Events::connect)
{
	if (!clever_check_args("sf")) {
		return;
	}

	EventData* intern = CLEVER_GET_OBJECT(EventData*, CLEVER_THIS());

	intern->m_event_map[*args.at(0)->getStr()]
			.push_back(static_cast<Function*>(args.at(1)->getObj()));
}

// Events.emit(String name, ...)
CLEVER_METHOD(Events::emit)
{
	if (!clever_check_args("s*")) {
		return;
	}

	EventData* intern = CLEVER_GET_OBJECT(EventData*, CLEVER_THIS());

	intern->mutex.lock();

	Signal s;

	s.first = *args.at(0)->getStr();

	for (size_t i = 1, j = args.size(); i < j; ++i) {
		s.second.push_back(args.at(i));
	}
	intern->m_event_queue.push(s);

	intern->mutex.unlock();
}

// Events.wait()
CLEVER_METHOD(Events::wait)
{
	if (!clever_check_no_args()) {
		return;
	}
	EventData* intern = CLEVER_GET_OBJECT(EventData*, CLEVER_THIS());

	intern->handler.wait();
}

// Events.finalize()
CLEVER_METHOD(Events::finalize)
{
	if (!clever_check_no_args()) {
		return;
	}

	EventData* intern = CLEVER_GET_OBJECT(EventData*, CLEVER_THIS());

	intern->mutex.lock();

	Signal s;

	s.first = "exit";

	intern->m_event_queue.push(s);

	intern->mutex.unlock();
	intern->handler.wait();
}

// Events type initialization
CLEVER_TYPE_INIT(Events::init)
{
	setConstructor((MethodPtr)&Events::ctor);

	addMethod(new Function("connect",    (MethodPtr)&Events::connect));
	addMethod(new Function("emit",      (MethodPtr)&Events::emit));
	addMethod(new Function("wait",       (MethodPtr)&Events::wait));
	addMethod(new Function("finalize",   (MethodPtr)&Events::finalize));
}

// FFI module initialization
CLEVER_MODULE_INIT(EventsModule)
{
	addType(new Events);
}

}}} // clever::modules::std
