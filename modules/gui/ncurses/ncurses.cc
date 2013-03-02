/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "core/value.h"
#include "core/native_types.h"
#include "modules/gui/ncurses/ncurses.h"
#include "modules/gui/ncurses/cncurses.h"

namespace clever { namespace modules { namespace gui {

// Simple constructor for now
// TODO: Build a constructor that can accept the host, port, user and password
TypeObject* NCurses::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	NCursesObject* obj = new NCursesObject();

	return obj;
}

void NCurses::dump(TypeObject* data, ::std::ostream& out) const
{
	NCursesObject* mo = static_cast<NCursesObject*>(data);

	if (mo) {
		//out << mo->getMysql().dump();
	}
}

CLEVER_METHOD(NCurses::ctor)
{
	result->setObj(this, allocData(&args));
}

// Type initialization
CLEVER_TYPE_INIT(NCurses::init)
{
	setConstructor((MethodPtr) &NCurses::ctor);
}

}}} // clever::modules::gui

