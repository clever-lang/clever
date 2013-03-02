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
TypeObject* NCurses::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	size_t n_args = args->size();

	int w = 23, h = 7;
	int rows = 25, cols = 80;
	int x = (cols - w)  / 2;
	int y = (rows - h) / 2;
	CNCurses* father = NULL;
	bool m_enable_colors = false;
	int m_sleep_time = 0;

	/*
	Constructors
	NCurses.new(father, x, y, w, h);
	NCurses.new(father, x, y, w, h, sleep_time);
	NCurses.new(enable_colors);
	NCurses.new(sleep_time);
	NCurses.new(enable_colors, sleep_time);
	*/

	if (n_args == 1) {
		Value* v = args->at(0);

		if (v->isBool()) {
			m_enable_colors = v->getBool();
		} else if (v->isInt()) {
			m_sleep_time = v->getInt();
		}
	} else if (n_args == 2) {
		m_enable_colors = args->at(0)->getBool();
		m_sleep_time = args->at(1)->getInt();
	} else if (n_args == 5 || n_args == 6) {
		father = static_cast<NCursesObject*>(args->at(0)->getObj())->getData();
		x = args->at(1)->getInt();
		y = args->at(2)->getInt();
		w = args->at(3)->getInt();
		h = args->at(4)->getInt();
		if (n_args == 6) {
			m_sleep_time = args->at(5)->getInt();
		}
	}

	return new NCursesObject(father, m_enable_colors,
						 w, h, x, y, m_sleep_time);
}

void NCurses::dump(TypeObject* data, ::std::ostream& out) const
{
	NCursesObject* mo = static_cast<NCursesObject*>(data);

	if (mo) {
		//out << mo->getObj().dump();
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

