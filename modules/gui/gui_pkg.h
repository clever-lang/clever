/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_GUI_PACKAGE_H
#define CLEVER_GUI_PACKAGE_H

#include "core/clever.h"
#include "modules/gui/gui_forwarder.h"
#include "core/module.h"

namespace clever { namespace modules {

class Gui : public Module {
public:
	Gui()
		: Module("gui") {}

	~Gui() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(Gui);
};

}} // clever::modules

#endif // CLEVER_GUI_PACKAGE_H
