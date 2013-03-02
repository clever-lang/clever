/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_GUI_NCURSES_MODULE_H
#define CLEVER_GUI_NCURSES_MODULE_H

#include "core/module.h"

namespace clever { namespace modules { namespace gui {

/// NCurses Module
class NCursesModule : public Module {
public:
	NCursesModule()
		: Module("gui.ncurses") {}

	~NCursesModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(NCursesModule);
};

}}} // clever::modules::gui

#endif // CLEVER_GUI_NCURSES_MODULE_H
