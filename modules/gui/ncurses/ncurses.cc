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

CLEVER_METHOD(NCurses::addStr)
{
	if (!clever_check_args("iis")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->addStr(args.at(0)->getInt(), args.at(1)->getInt(), args.at(2)->getStr()->c_str());
}

CLEVER_METHOD(NCurses::refresh)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->refresh();
}

CLEVER_METHOD(NCurses::sleep)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->sleep();
}

CLEVER_METHOD(NCurses::startColor)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->startColor();
}

CLEVER_METHOD(NCurses::setColor)
{
	if (!clever_check_args("i")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->setColor(args.at(0)->getInt(), NULL);
}

CLEVER_METHOD(NCurses::addColor)
{
	if (!clever_check_args("iii")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->addColor(args.at(0)->getInt(), args.at(1)->getInt(), args.at(2)->getInt());
}

CLEVER_METHOD(NCurses::nColors)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->nColors());
}

CLEVER_METHOD(NCurses::hasColors)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setBool(o->hasColors());
}

// Type initialization
CLEVER_TYPE_INIT(NCurses::init)
{
	setConstructor((MethodPtr) &NCurses::ctor);

	addMethod(new Function("addStr",        (MethodPtr) &NCurses::addStr));
	addMethod(new Function("refresh",       (MethodPtr) &NCurses::refresh));
	addMethod(new Function("sleep",         (MethodPtr) &NCurses::sleep));

	addMethod(new Function("addColor",     (MethodPtr) &NCurses::addColor));
	addMethod(new Function("startColor",   (MethodPtr) &NCurses::startColor));
	addMethod(new Function("setColor",     (MethodPtr) &NCurses::setColor));
	addMethod(new Function("hasColors",    (MethodPtr) &NCurses::hasColors));
	addMethod(new Function("nColors",      (MethodPtr) &NCurses::nColors));

	/*COLORS*/

	addProperty(CSTRING("RED"),        new Value(long(COLOR_RED),          true));
	addProperty(CSTRING("BLACK"),      new Value(long(COLOR_BLACK),        true));
	addProperty(CSTRING("GREEN"),      new Value(long(COLOR_GREEN),        true));
	addProperty(CSTRING("YELLOW"),     new Value(long(COLOR_YELLOW),       true));
	addProperty(CSTRING("BLUE"),       new Value(long(COLOR_BLUE),         true));
	addProperty(CSTRING("MAGENTA"),    new Value(long(COLOR_MAGENTA),      true));
	addProperty(CSTRING("CYAN"),       new Value(long(COLOR_CYAN),         true));
	addProperty(CSTRING("WHITE"),      new Value(long(COLOR_WHITE),        true));
}

}}} // clever::modules::gui

