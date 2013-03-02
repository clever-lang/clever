/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifdef CLEVER_WIN32
# include <direct.h>
# include <windows.h>
#else
# include <dirent.h>
# include <unistd.h>
# include <sys/resource.h>
# include <sys/time.h>
#endif
#include "modules/gui/ncurses/cncurses.h"

namespace clever {

void csleep(int sleep_time)
{
#ifdef CLEVER_WIN32
	SleepEx(sleep_time, false);
#else
	usleep(sleep_time * 1000);
#endif
}

bool CNCurses::hasColors()
{
	return has_colors();
}

void CNCurses::addColor(short id, short color_1, short color_2)
{
	init_pair(id, color_1, color_2);
}

void CNCurses::deleteLine()
{
	deleteln();
}

void CNCurses::printStr(int x, int y, const char *str)
{
	if (m_father == NULL) {
		mvprintw(x, y, str);
	} else {
		mvwprintw(m_win, x, y, str);
	}
}

int CNCurses::setColor(short id, void* handler)
{
	return color_set(id, handler);
}

bool CNCurses::isPrintable(int ch)
{
	return ::isprint(ch) && !(ch & KEY_CODE_YES);
}

void CNCurses::enableKeyPad()
{
	keypad(m_win, true);
}

int CNCurses::getKey()
{
	return ::getch();
}

int CNCurses::nColors()
{
	return COLOR_PAIRS;
}

bool CNCurses::status()
{
	return m_status;
}

CNCurses::CNCurses(int sleep_time, WINDOW* father, bool enable_colors,
				   int w, int h, int x, int y, bool enable_keypad)
	: m_sleep_time(sleep_time), m_enable_colors(enable_colors)
{
	m_is_closed = false;
	m_father = father;

	width = w;
	height = h;

	pos_x = x;
	pos_y = y;

	if (father == NULL) {
		//IS MAIN WINDOW
		m_status = (m_win = initscr()) == NULL;
	} else {
		m_win = subwin(father, w, h, x, y);
	}

	if (enable_keypad) {
		keypad(m_win, true);
	}

	if (enable_colors) {
		start_color();
	}
}

void CNCurses::addStr(int x, int y, const char *str)
{
	if (m_father == NULL) {
		mvaddstr(x, y, str);
	} else {
		mvwaddstr(m_father, x, y, str);
	}
}

void CNCurses::refresh()
{
	::refresh();
}

void CNCurses::sleep()
{
	clever::csleep(m_sleep_time);
}

CNCurses::~CNCurses()
{
	if (!m_is_closed) {
		close();
	}
}

void CNCurses::hide()
{
	delwin(m_win);
	m_is_closed = true;
}

void CNCurses::exit()
{
	endwin();
	m_is_closed = true;
}

void CNCurses::close()
{
	delwin(m_win);
	endwin();
	refresh();
	m_is_closed = true;
}

bool CNCurses::isChild()
{
	return m_father != NULL;
}

void CNCurses::box(int x, int y)
{
	::box(m_win, x, y);
}

void CNCurses::move(int x, int y)
{
	mvwin(m_win, x, y);
	pos_x = x;
	pos_y = y;
}

} // clever
