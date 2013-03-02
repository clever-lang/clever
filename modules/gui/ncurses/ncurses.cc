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

CLEVER_METHOD(NCurses::printStr)
{
	if (!clever_check_args("iis")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->printStr(args.at(0)->getInt(), args.at(1)->getInt(), args.at(2)->getStr()->c_str());
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

CLEVER_METHOD(NCurses::hide)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->hide();
}

CLEVER_METHOD(NCurses::close)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->close();
}

CLEVER_METHOD(NCurses::exit)
{
	if (!clever_check_no_args()) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->exit();
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

CLEVER_METHOD(NCurses::isChild)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setBool(o->isChild());
}

CLEVER_METHOD(NCurses::enableKeyPad)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	o->enableKeyPad();
}

CLEVER_METHOD(NCurses::noEcho)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	o->noEcho();
}

CLEVER_METHOD(NCurses::deleteLine)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	o->deleteLine();
}

CLEVER_METHOD(NCurses::getKey)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->getKey());
}

CLEVER_METHOD(NCurses::isPrintable)
{
	if (!clever_check_args("i")) {
		return;
	}
	result->setBool(CNCurses::isPrintable(args.at(0)->getInt()));
}

::std::map<int, CString> NCurses::m_keys;

CLEVER_METHOD(NCurses::getKeyName)
{
	if (!clever_check_args("i")) {
		return;
	}
	result->setStr(&m_keys[args.at(0)->getInt()]);
}

CLEVER_METHOD(NCurses::box)
{
	if (!clever_check_args("ii")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->box(args.at(0)->getInt(), args.at(1)->getInt());
}

CLEVER_METHOD(NCurses::move)
{
	if (!clever_check_args("ii")) {
		return;
	}

	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();

	o->move(args.at(0)->getInt(), args.at(1)->getInt());
}

CLEVER_METHOD(NCurses::posX)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->getPosX());
}

CLEVER_METHOD(NCurses::posY)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->getPosY());
}

CLEVER_METHOD(NCurses::width)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->getWidth());
}

CLEVER_METHOD(NCurses::height)
{
	if (!clever_check_no_args()) {
		return;
	}
	NCursesObject* mo = CLEVER_GET_OBJECT(NCursesObject*, CLEVER_THIS());
	CNCurses* o = mo->getData();
	result->setInt(o->getHeight());
}

// Type initialization
CLEVER_TYPE_INIT(NCurses::init)
{
	setConstructor((MethodPtr)&NCurses::ctor);

	addMethod(new Function("addStr",       (MethodPtr)&NCurses::addStr));
	addMethod(new Function("printStr",     (MethodPtr)&NCurses::printStr));

	addMethod(new Function("refresh",      (MethodPtr)&NCurses::refresh));
	addMethod(new Function("sleep",        (MethodPtr)&NCurses::sleep));

	addMethod(new Function("hide",         (MethodPtr)&NCurses::hide));
	addMethod(new Function("close",        (MethodPtr)&NCurses::close));
	addMethod(new Function("exit",         (MethodPtr)&NCurses::exit));

	addMethod(new Function("addColor",     (MethodPtr)&NCurses::addColor));
	addMethod(new Function("startColor",   (MethodPtr)&NCurses::startColor));
	addMethod(new Function("setColor",     (MethodPtr)&NCurses::setColor));
	addMethod(new Function("hasColors",    (MethodPtr)&NCurses::hasColors));
	addMethod(new Function("nColors",      (MethodPtr)&NCurses::nColors));

	addMethod(new Function("enableKeyPad", (MethodPtr)&NCurses::enableKeyPad));
	addMethod(new Function("noEcho",       (MethodPtr)&NCurses::noEcho));
	addMethod(new Function("deleteLine",   (MethodPtr)&NCurses::deleteLine));
	addMethod(new Function("getKey",       (MethodPtr)&NCurses::getKey));
	addMethod(new Function("isPrintable",  (MethodPtr)&NCurses::isPrintable))
			->setStatic();
	addMethod(new Function("getKeyName",   (MethodPtr)&NCurses::getKeyName))
			->setStatic();

	addMethod(new Function("isChild",      (MethodPtr)&NCurses::isChild));

	addMethod(new Function("box",          (MethodPtr)&NCurses::box));
	addMethod(new Function("move",         (MethodPtr)&NCurses::move));
	addMethod(new Function("posX",         (MethodPtr)&NCurses::posX));
	addMethod(new Function("posY",         (MethodPtr)&NCurses::posY));
	addMethod(new Function("width",        (MethodPtr)&NCurses::width));
	addMethod(new Function("height",       (MethodPtr)&NCurses::height));

	// COLORS
	addProperty(CSTRING("RED"),        new Value(long(COLOR_RED),        true));
	addProperty(CSTRING("BLACK"),      new Value(long(COLOR_BLACK),      true));
	addProperty(CSTRING("GREEN"),      new Value(long(COLOR_GREEN),      true));
	addProperty(CSTRING("YELLOW"),     new Value(long(COLOR_YELLOW),     true));
	addProperty(CSTRING("BLUE"),       new Value(long(COLOR_BLUE),       true));
	addProperty(CSTRING("MAGENTA"),    new Value(long(COLOR_MAGENTA),    true));
	addProperty(CSTRING("CYAN"),       new Value(long(COLOR_CYAN),       true));
	addProperty(CSTRING("WHITE"),      new Value(long(COLOR_WHITE),      true));

	// KEYS
	addProperty(CSTRING("KEY_UP"),        new Value(long(KEY_UP),        true));
	addProperty(CSTRING("KEY_DOWN"),      new Value(long(KEY_DOWN),      true));
	addProperty(CSTRING("KEY_LEFT"),      new Value(long(KEY_LEFT),      true));
	addProperty(CSTRING("KEY_RIGHT"),     new Value(long(KEY_RIGHT),     true));
	addProperty(CSTRING("KEY_HOME"),      new Value(long(KEY_HOME),      true));
	addProperty(CSTRING("KEY_END"),       new Value(long(KEY_END),       true));
	addProperty(CSTRING("KEY_BACKSPACE"), new Value(long(KEY_BACKSPACE), true));
	addProperty(CSTRING("KEY_IC"),        new Value(long(KEY_IC),        true));
	addProperty(CSTRING("KEY_DC"),        new Value(long(KEY_DC),        true));
	addProperty(CSTRING("KEY_NPAGE"),     new Value(long(KEY_NPAGE),     true));
	addProperty(CSTRING("KEY_PPAGE"),     new Value(long(KEY_PPAGE),     true));
	addProperty(CSTRING("KEY_F1"),        new Value(long(KEY_F(1)),      true));
	addProperty(CSTRING("KEY_F2"),        new Value(long(KEY_F(2)),      true));
	addProperty(CSTRING("KEY_F3"),        new Value(long(KEY_F(3)),      true));
	addProperty(CSTRING("KEY_F4"),        new Value(long(KEY_F(4)),      true));
	addProperty(CSTRING("KEY_F5"),        new Value(long(KEY_F(5)),      true));
	addProperty(CSTRING("KEY_F6"),        new Value(long(KEY_F(6)),      true));
	addProperty(CSTRING("KEY_F7"),        new Value(long(KEY_F(7)),      true));
	addProperty(CSTRING("KEY_F8"),        new Value(long(KEY_F(8)),      true));
	addProperty(CSTRING("KEY_F9"),        new Value(long(KEY_F(9)),      true));
	addProperty(CSTRING("KEY_F10"),       new Value(long(KEY_F(10)),     true));
	addProperty(CSTRING("KEY_F11"),       new Value(long(KEY_F(11)),     true));
	addProperty(CSTRING("KEY_F12"),       new Value(long(KEY_F(12)),     true));

	m_keys[KEY_UP] =        "Up arrow";
	m_keys[KEY_DOWN] =      "Down arrow";
	m_keys[KEY_LEFT] =      "Left arrow";
	m_keys[KEY_RIGHT] =     "Right arrow";
	m_keys[KEY_HOME] =      "Home";
	m_keys[KEY_END] =       "End";
	m_keys[KEY_BACKSPACE] = "Backspace";
	m_keys[KEY_IC] =        "Insert";
	m_keys[KEY_DC] =        "Delete";
	m_keys[KEY_NPAGE] =     "Page down";
	m_keys[KEY_PPAGE] =     "Page up";
	m_keys[KEY_F(1)] =      "Function key 1";
	m_keys[KEY_F(2)] =      "Function key 2";
	m_keys[KEY_F(3)] =      "Function key 3";
	m_keys[KEY_F(4)] =      "Function key 4";
	m_keys[KEY_F(5)] =      "Function key 5";
	m_keys[KEY_F(6)] =      "Function key 6";
	m_keys[KEY_F(7)] =      "Function key 7";
	m_keys[KEY_F(8)] =      "Function key 8";
	m_keys[KEY_F(9)] =      "Function key 9";
	m_keys[KEY_F(10)] =     "Function key 10";
	m_keys[KEY_F(11)] =     "Function key 11";
	m_keys[KEY_F(12)] =     "Function key 12";
	m_keys[-1       ] =     "<unsupported>";
}

}}} // clever::modules::gui

