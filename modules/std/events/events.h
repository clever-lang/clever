/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_EVENTS_H
#define CLEVER_STD_EVENTS_H

#include <iostream>

#include "core/cstring.h"
#include "types/type.h"
#include "core/module.h"

namespace clever { namespace modules { namespace std {

struct EventData : public TypeObject {
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
