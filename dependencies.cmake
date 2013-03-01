#
# Clever programming language
# Copyright (c) 2011-2013 Clever Team
#
# dependencies.cmake - 3rd-party library dependency
#

# 3rd-party libraries
# ---------------------------------------------------------------------------
# TODO(heuripedes): minimize the scope of the add_definitions()
# pthread
clever_add_lib(PTHREAD
	LIBS pthread
	INCS pthread.h)

# libpcrecpp
clever_add_lib(PCRECPP
	INCS pcrecpp.h
	LIBS pcre pcrecpp
	PKGS libpcrecpp)

if (PCRECPP_FOUND)
	add_definitions(-DHAVE_PCRECPP)
endif()

# libicu
clever_add_lib(ICU
	LIBS icuuc
	INCS unicode/ustring.h
	PKGS icu-uc)

# libfcgi
clever_add_lib(FCGI
	LIBS fcgi fcgi++
	INCS fcgi_config.h)

# cgicc
clever_add_lib(CGICC
	LIBS cgicc
	INCS cgicc/Cgicc.h)

# libffi
clever_add_lib(FFI
	LIBS ffi
	INCS ffi.h
	PKGS libffi)

# libmysqlclient
clever_add_lib(MYSQLC
	LIBS mysqlclient
	INCS mysql/mysql.h)

# libsqlite3
clever_add_lib(SQLITE3
	LIBS sqlite3
	INCS sqlite3.h
	PKGS sqlite3)

