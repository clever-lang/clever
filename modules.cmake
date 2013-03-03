#
# Clever programming language
# Copyright (c) Clever Team
#
# modules.cmake - Module options and other stuff
#

# Modules
# ---------------------------------------------------------------------------
# heuripedes: pay attention to the order in which you check the modules.
#             keep in mind that the check is recursive.

clever_new_module(std.date       ON DOC "enable the date module")
clever_new_module(std.concurrent ON DOC "enable the concurrent module")
clever_new_module(std.net        ON DOC "enable the net module")
clever_new_module(std.clever     ON DOC "enable the clever module")
clever_new_module(std.file       ON DOC "enable the file module")
clever_new_module(std.io         ON DOC "enable the io module")
clever_new_module(std.json       ON DOC "enable the json module")
clever_new_module(std.math       ON DOC "enable the math module")
clever_new_module(std.reflection ON DOC "enable the reflection module")
clever_new_module(std.sys        ON DOC "enable the sys module")
clever_new_module(std.crypto     ON DOC "enable the crypto module")
clever_new_module(std.collection ON DOC "enable the collection module")

clever_new_module(std.regex ON
	DOC"enable the regex module"
	LIBS PCRECPP)

clever_new_module(std.ffi ON
	DOC "enable the ffi module"
	LIBS FFI)

clever_new_module(std.rpc OFF
	DOC "enable the rpc module"
	LIBS PTHREAD FFI)


clever_new_module(std.unicode ON
	DOC	"enable the unicode module"
	LIBS ICU)

clever_new_module(std.fcgi OFF
	DOC	"enable the fcgi module"
	LIBS FCGI)

clever_new_module(std.events ON
	DOC	"enable the event module"
	MODS std.concurrent)

clever_new_module(db.mysql ON
	DOC	"enable the mysql module"
	LIBS MYSQLC)

clever_new_module(db.sqlite3 ON
	DOC	"enable the sqlite3 module"
	LIBS SQLITE3)

clever_new_module(gui.ncurses ON
	DOC "enable the ncurses module"
	LIBS NCURSES
)

# std.concurrent
if(STD_CONCURRENT AND UNIX)
	list(APPEND STD_CONCURRENT_LIB_DEPENDS PTHREAD)
	clever_module_check(std.concurrent)

	add_definitions(-pthread)
	list(APPEND CLEVER_LIBRARIES dl)
endif()

# std.ffi
clever_module_check(std.ffi)
if(STD_FFI)
	add_definitions(-pthread)
	list(APPEND CLEVER_LIBRARIES dl)
endif()

# std.rpc
clever_module_check(std.rpc)
if(STD_RPC)
	add_definitions(-pthread)
	list(APPEND CLEVER_LIBRARIES dl)
endif()

# std.net
clever_module_check(std.net)
if(STD_NET AND MSVC)
	list(APPEND CLEVER_LIBRARIES ws2_32)
endif()


# check the remaining modules
foreach(_modname ${CLEVER_AVAILABLE_MODULES})
	clever_module_check(${_modname})
endforeach()

