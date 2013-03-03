/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_GUI_NCURSES_H
#define CLEVER_GUI_NCURSES_H

#include <iostream>
#include <map>
#include "core/cstring.h"
#include "core/value.h"
#include "core/type.h"
#include "modules/gui/ncurses/cncurses.h"

namespace clever { namespace modules { namespace gui {

class KeyObject : public TypeObject {
public:
	KeyObject(int value = 0)
		: value(value) {}

	~KeyObject() { }

	char getChar() { return static_cast<char>(value); }
	int  getInt()  { return value; }

private:
	int value;
};

class Key : public Type {
public:
	Key()
		: Type("Key") {}

	~Key() {}

	void init(){}

	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const{}

	void dump(TypeObject*, std::ostream&) const{}

	CLEVER_METHOD(ctor){}

	CLEVER_METHOD(getChar){}
	CLEVER_METHOD(getInt) {}

private:
	DISALLOW_COPY_AND_ASSIGN(Key);
};

class NCursesObject : public TypeObject {
public:
	NCursesObject(CNCurses* father = NULL, bool m_enable_colors = false,
				  int w = 0, int h = 0, int x = 0, int y = 0, int m_sleep_time = 0)
		: m_ncurses_obj(m_sleep_time, father == NULL? NULL : father->getWindow(),
						m_enable_colors, w, h, x, y) {

	}

	~NCursesObject() {}

	CNCurses* getData() { return &m_ncurses_obj; }

private:
	CNCurses m_ncurses_obj;
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

	CLEVER_METHOD(isChild);

	CLEVER_METHOD(addStr);
	CLEVER_METHOD(addChar);
	CLEVER_METHOD(printStr);

	CLEVER_METHOD(hide);
	CLEVER_METHOD(close);
	CLEVER_METHOD(exit);

	CLEVER_METHOD(refresh);
	CLEVER_METHOD(sleep);

	CLEVER_METHOD(startColor);
	CLEVER_METHOD(setColor);
	CLEVER_METHOD(addColor);
	CLEVER_METHOD(nColors);
	CLEVER_METHOD(hasColors);

	CLEVER_METHOD(enableKeyPad);
	CLEVER_METHOD(noEcho);
	CLEVER_METHOD(deleteLine);
	CLEVER_METHOD(getKey);
	CLEVER_METHOD(isPrintable);
	CLEVER_METHOD(getKeyName);

	CLEVER_METHOD(box);
	CLEVER_METHOD(move);

	CLEVER_METHOD(posX);
	CLEVER_METHOD(posY);
	CLEVER_METHOD(width);
	CLEVER_METHOD(height);

private:
	static ::std::map<int, CString> m_keys;

	DISALLOW_COPY_AND_ASSIGN(NCurses);
};

}}} // clever::modules::gui

#endif // CLEVER_GUI_NCURSES_H

