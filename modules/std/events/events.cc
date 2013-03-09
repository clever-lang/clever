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

#include <cstdio>

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/events/events.h"
#include "modules/std/core/map.h"
#include "core/type.h"
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

			if (u.first == "set") {
				/*Get current state of the requisitions*/
				Requisitions& req = intern->m_requisitions;

				/*Get current requisitions*/
				RequisitionMap& reqm = intern->m_requisition_map;

				/*Get name and args of the last requisition*/
				CString ls = intern->m_sets_queue.front();
				ActionArgs args = intern->m_args_queue.front();

				intern->m_sets_queue.pop();
				intern->m_args_queue.pop();

				RequisitionMap::iterator it = reqm.find(ls);

				if (it != reqm.end()) {
					RequisitionSubMap& reqsm = it->second;
					RequisitionSubMap::iterator it2 = reqsm.find(req[ls]);

					if (it2 != reqsm.end()) {
						RequisitionActionPairs& actions = it2->second;

						for (size_t i = 0, j = actions.size(); i < j; ++i) {
							RequisitionActionPair& tap = actions[i];
							Requisitions& treq = tap.first;
							Function* func = tap.second;
							Requisitions::iterator it3 = treq.begin(), end = treq.end();
							bool exec = true;

							while (it3 != end) {
								if (req[it3->first] != it3->second) {
									exec = false;
									break;
								}
								++it3;
							}

							if (exec) {
								intern->m_vm->runFunction(func, &args)->delRef();
							}
						}
					}
				}
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

	EventData* intern = new EventData;

	if (args.empty()) {
		intern->m_sleep_time = 500;
	} else {
		intern->m_sleep_time = static_cast<int>(args[0]->getInt());
	}

	intern->handler.create(_events_handler, intern);

	intern->m_vm = new VM();
	intern->m_vm->copy(vm, true);
	intern->m_vm->setChild();

	result->setObj(this, intern);
}

// Events.connect(String name, Function func)
CLEVER_METHOD(Events::connect)
{
	if (!clever_check_args(".f")) {
		return;
	}

	EventData* intern = clever_get_this(EventData*);


	Value* v = args.at(0);

	if (v->isStr()) {
		intern->m_event_map[*v->getStr()]
			.push_back(static_cast<Function*>(args.at(1)->getObj()));
	} else if (v->isMap()) {
		ValueMap& map = static_cast<MapObject*>(v->getObj())->getData();
		RequisitionActionPair action;
		Requisitions& req = action.first;
		ValueMap::const_iterator it(map.begin()), end(map.end());

		while (it != end) {
			req[it->first] = it->second->getInt();
			++it;
		}

		action.second = static_cast<Function*>(args.at(1)->getObj());

		it  = map.begin(); end = map.end();

		RequisitionMap& rmap = intern->m_requisition_map;
		while (it != end) {
			rmap[it->first][it->second->getInt()].push_back(action);
			++it;
		}
	}
}

// Events.emit(String name, ...)
CLEVER_METHOD(Events::emit)
{
	if (!clever_check_args("s*")) {
		return;
	}

	EventData* intern = clever_get_this(EventData*);

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
	EventData* intern = clever_get_this(EventData*);

	intern->handler.wait();
}

// Events.finalize()
CLEVER_METHOD(Events::finalize)
{
	if (!clever_check_no_args()) {
		return;
	}

	EventData* intern = clever_get_this(EventData*);

	intern->mutex.lock();

	Signal s;

	s.first = "exit";

	intern->m_event_queue.push(s);

	intern->mutex.unlock();
	intern->handler.wait();
}

CLEVER_METHOD(Events::set)
{
	if (!clever_check_args("m*")) {
		return;
	}

	EventData* intern = clever_get_this(EventData*);

	Value* v = args.at(0);

	ValueMap& map = static_cast<MapObject*>(v->getObj())->getData();
	ValueMap::iterator it = map.begin(), end = map.end();

	intern->mutex.lock();

	while (it != end) {
		intern->m_requisitions[it->first] = static_cast<int>(it->second->getInt());
		++it;
	}

	Signal s;

	s.first = "set";

	ActionArgs _arg;

	for (size_t i = 1, j = args.size(); i < j; ++i) {
		_arg.push_back(args.at(i));
	}

	intern->m_event_queue.push(s);
	intern->m_sets_queue.push(map.begin()->first);
	intern->m_args_queue.push(_arg);

	intern->mutex.unlock();

}

// Events type initialization
CLEVER_TYPE_INIT(Events::init)
{
	setConstructor((MethodPtr)&Events::ctor);

	addMethod(new Function("connect",    (MethodPtr)&Events::connect));
	addMethod(new Function("emit",       (MethodPtr)&Events::emit));
	addMethod(new Function("wait",       (MethodPtr)&Events::wait));
	addMethod(new Function("finalize",   (MethodPtr)&Events::finalize));
	addMethod(new Function("set",        (MethodPtr)&Events::set));
}

// FFI module initialization
CLEVER_MODULE_INIT(EventsModule)
{
	addType(new Events);
}

}}} // clever::modules::std
