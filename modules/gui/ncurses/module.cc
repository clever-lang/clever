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
CLEVER_MODULE_INIT(NCursesModule)
{
	addType(new NCurses);
}

}}} // clever::modules::gui
