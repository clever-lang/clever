/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include "modules/gui/gui_pkg.h"
#include "modules/gui/ncurses/module.h"

namespace clever { namespace modules {

// Initializes Gui package
void Gui::init()
{
#if HAVE_MOD_GUI_NCURSES
	addModule(new gui::NCursesModule);
#endif
}

}} // clever::modules
