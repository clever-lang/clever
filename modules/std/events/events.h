/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_EVENTS_H
#define CLEVER_STD_EVENTS_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>

#include "core/cstring.h"
#include "types/type.h"
#include "core/module.h"
#include "core/cthread.h"
#include "core/vm.h"

namespace clever { namespace modules { namespace std {


typedef ::std::vector<Function*> Actions;
typedef ::std::map<CString, Actions> EventMap;

typedef ::std::map<CString, int> Requisitions;
typedef ::std::pair<Requisitions, Function*> RequisitionActionPair;
typedef ::std::vector<RequisitionActionPair> RequisitionActionPairs;
typedef ::std::map<int, RequisitionActionPairs> RequisitionSubMap;
typedef ::std::map<CString, RequisitionSubMap> RequisitionMap;

typedef ::std::vector<Value*> ActionArgs;
typedef ::std::pair<CString, ActionArgs> Signal;
typedef ::std::queue<Signal> EventsQueue;
typedef ::std::queue<CString> SetsQueue;
typedef ::std::queue<ActionArgs> ActionArgsQueue;


struct EventData : public TypeObject {
	EventMap m_event_map;
	Requisitions m_requisitions;
	RequisitionMap m_requisition_map;
	EventsQueue m_event_queue;
	SetsQueue m_sets_queue;
	ActionArgsQueue m_args_queue;

	CThread handler;
	CMutex mutex;

	VM* m_vm;

	int m_sleep_time;

	EventData() {}

	~EventData();
};

class Events : public Type {
public:
	Events()
		: Type("Events") {}

	~Events() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(connect);
	CLEVER_METHOD(emit);
	CLEVER_METHOD(wait);
	CLEVER_METHOD(set);
	CLEVER_METHOD(finalize);
};

class EventsModule : public Module {
public:
	EventsModule()
		: Module("std.events") {}

	~EventsModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(EventsModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_EVENTS_H
