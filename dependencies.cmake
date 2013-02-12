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
# XXX(heuripedes): rename to pthread.
clever_add_lib(CONCURRENCY
	LIBS pthread
	INCS pthread.h)

# XXX(heuripedes): kill this
if (CONCURRENCY_FOUND)
	add_definitions(-DHAVE_CONCURRENCY)
endif (CONCURRENCY_FOUND)

# libpcrecpp
clever_add_lib(PCRECPP
	INCS pcrecpp.h
	LIBS pcre pcrecpp
	PKGS libpcrecpp)

if (PCRECPP_FOUND)
	add_definitions(-DHAVE_PCRECPP)
endif (PCRECPP_FOUND)

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

if (CGICC_FOUND)
	add_definitions(-DHAVE_CGICC)
endif (CGICC_FOUND)

# libffi
clever_add_lib(FFI
	LIBS ffi
	INCS ffi.h
	PKGS libffi)

if (FFI_FOUND)
	add_definitions(-DHAVE_FFI)
endif (FFI_FOUND)
