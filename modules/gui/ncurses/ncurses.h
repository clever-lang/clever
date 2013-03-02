/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_GUI_NCURSES_H
#define CLEVER_GUI_NCURSES_H

#include <iostream>
#include "core/cstring.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/gui/ncurses/cncurses.h"

namespace clever { namespace modules { namespace gui {

class NCursesObject : public TypeObject {
public:
	NCursesObject() {}

	~NCursesObject() {}

private:
	
	DISALLOW_COPY_AND_ASSIGN(NCursesObject);
};

class NCurses : public Type {
public:
	NCurses()
		: Type("NCurses") {}

	~NCurses() {}

	void init();

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	void dump(TypeObject*, std::ostream&) const;

	CLEVER_METHOD(ctor);

private:
	DISALLOW_COPY_AND_ASSIGN(NCurses);
};

}}} // clever::modules::gui

#endif // CLEVER_GUI_NCURSES_H

