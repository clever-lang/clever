#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# CMakeLists.depends - 3rd-party library dependency
#

# 3rd-party libraries
# ---------------------------------------------------------------------------
# libpcrecpp
if (PCRECPP_DIR)
	# Manual search.
	find_path(PCRECPP_INCLUDE_DIRS pcrecpp.h "${PCRECPP_DIR}/include"})
	find_library(PCRECPP_LIBS_PCRE NAMES pcre PATHS "${PCRECPP_DIR}/lib")
	find_library(PCRECPP_LIBS_PCRECPP NAMES pcrecpp PATHS "${PCRECPP_DIR}/lib")

	# If we found everything we need, libpcrecpp is available.
	if (PCRECPP_INCLUDE_DIRS AND PCRECPP_LIBS_PCRE AND PCRECPP_LIBS_PCRECPP)
		list(APPEND PCRECPP_LIBRARIES ${PCRECPP_LIBS_PCRE})
		list(APPEND PCRECPP_LIBRARIES ${PCRECPP_LIBS_PCRECPP})
		set(PCRECPP_FOUND TRUE)
		add_definitions(-DPCRE_STATIC)
	endif (PCRECPP_INCLUDE_DIRS AND PCRECPP_LIBS_PCRE AND PCRECPP_LIBS_PCRECPP)
else (PCRECPP_DIR)
	if (NOT MSVC)
		# pkg-config search
		pkg_check_modules(PCRECPP libpcrecpp)
	endif (NOT MSVC)
endif (PCRECPP_DIR)

if (PCRECPP_FOUND)
	add_definitions(-DHAVE_PCRECPP)
endif (PCRECPP_FOUND)

# cgicc
if (CGICC_DIR)
	find_path(CGICC_INCLUDE_DIRS cgicc/Cgicc.h "${CGICC_DIR}/include"})
	find_library(CGICC_LIBRARIES NAMES cgicc PATHS "${CGICC_DIR}/lib")
	find_library(CGICC_LIBRARIES NAMES libcgicc PATHS "${CGICC_DIR}/lib")

	# If we found everything we need, cgicc is available.
	if (CGICC_INCLUDE_DIRS AND CGICC_LIBRARIES)
		set(CGICC_FOUND TRUE)
	endif (CGICC_INCLUDE_DIRS AND CGICC_LIBRARIES)
else (CGICC_DIR)
	find_library(CGICC_LIBRARIES cgicc libcgicc)
	find_path(CGICC_INCLUDE_DIRS cgicc/Cgicc.h)

	if (CGICC_LIBRARIES AND CGICC_INCLUDE_DIRS)
		set(CGICC_FOUND TRUE)
	else (CGICC_LIBRARIES AND CGICC_INCLUDE_DIRS)
		set(CGICC_FOUND FALSE)
	endif (CGICC_LIBRARIES AND CGICC_INCLUDE_DIRS)
endif (CGICC_DIR)	

if (CGICC_FOUND)
	add_definitions(-DHAVE_CGICC)
endif (CGICC_FOUND)

# libpthread
if (LIBPTHREAD_DIR)
	find_path(LIBPTHREAD_INCLUDE_DIRS pthread.h "${LIBPTHREAD_DIR}/include"})
	find_library(LIBPTHREAD_LIBRARIES NAMES pthread PATHS "${LIBPTHREAD_DIR}/lib")
	find_library(LIBPTHREAD_LIBRARIES NAMES libpthread PATHS "${LIBPTHREAD_DIR}/lib")

	# If we found everything we need, libpthread is available.
	if (LIBPTHREAD_INCLUDE_DIRS AND LIBPTHREAD_LIBRARIES)
		set(LIBPTHREAD_FOUND TRUE)
	endif (LIBPTHREAD_INCLUDE_DIRS AND LIBPTHREAD_LIBRARIES)
else (LIBPTHREAD_DIR)
	find_library(LIBPTHREAD_LIBRARIES pthread libpthread)
	find_path(LIBPTHREAD_INCLUDE_DIRS pthread.h)

	if (LIBPTHREAD_LIBRARIES AND LIBPTHREAD_INCLUDE_DIRS)
		set(LIBPTHREAD_FOUND TRUE)
	else (LIBPTHREAD_LIBRARIES AND LIBPTHREAD_INCLUDE_DIRS)
		set(LIBPTHREAD_FOUND FALSE)
	endif (LIBPTHREAD_LIBRARIES AND LIBPTHREAD_INCLUDE_DIRS)
endif (LIBPTHREAD_DIR)

if (LIBPTHREAD_FOUND)
	add_definitions(-DHAVE_LIBPTHREAD)
endif (LIBPTHREAD_FOUND)

# libffi
if (FFI_DIR)
	find_path(FFI_INCLUDE_DIRS ffi.h "${FFI_DIR}/include"})
	find_library(FFI_LIBRARIES NAMES ffi PATHS "${FFI_DIR}/lib")

	# If we found everything we need, libffi is available.
	if (FFI_INCLUDE_DIRS AND FFI_LIBRARIES)
		set(FFI_FOUND TRUE)
	else (FFI_INCLUDE_DIRS AND FFI_LIBRARIES)
		set(FFI_FOUND FALSE)
	endif (FFI_INCLUDE_DIRS AND FFI_LIBRARIES)
else (FFI_DIR)
	# pkg-config search
	pkg_check_modules(FFI libffi QUIET)
endif (FFI_DIR)

if (FFI_FOUND)
	add_definitions(-DHAVE_FFI)
endif (FFI_FOUND)
