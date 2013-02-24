/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/clever.h"
#include "core/value.h"
#include "modules/std/events/events.h"
#include "types/type.h"

namespace clever { namespace modules { namespace std {


TypeObject* Events::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
}

EventData::~EventData()
{

}

// Events.new()
// Constructs a new Events handler object to manage some events
CLEVER_METHOD(Events::ctor)
{

}

CLEVER_TYPE_INIT(Events::init)
{
	setConstructor((MethodPtr) &Events::ctor);
}


// FFI module initialization
CLEVER_MODULE_INIT(EventsModule)
{
	addType(new Events);
}


}}} // clever::modules::std
