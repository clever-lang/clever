/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/gui/ncurses/module.h"
#include "modules/gui/ncurses/ncurses.h"

namespace clever { namespace modules { namespace gui {

/// Initializes ncurses module

Type* g_key_type_ref;

CLEVER_MODULE_INIT(NCursesModule)
{
	addType(new NCurses);
	addType(g_key_type_ref = new Key);
}

}}} // clever::modules::gui
