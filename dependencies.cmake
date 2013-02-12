#
# Clever programming language
# Copyright (c) 2011-2013 Clever Team
#
# dependencies.cmake - 3rd-party library dependency
#

# 3rd-party libraries
# ---------------------------------------------------------------------------
# pthread
if (USE_THREADS)
	find_path(CONCURRENCY_INCLUDES pthread.h)
	find_library(CONCURRENCY_LIBRARIES NAMES pthread)

	if (CONCURRENCY_INCLUDES AND CONCURRENCY_LIBRARIES)
		set(HAVE_CONCURRENCY TRUE)
	else (CONCURRENCY_INCLUDES AND CONCURRENCY_LIBRARIES)
		set(HAVE_CONCURRENCY FALSE)
	endif (CONCURRENCY_INCLUDES AND CONCURRENCY_LIBRARIES)

	if (HAVE_CONCURRENCY)
		add_definitions(-DHAVE_CONCURRENCY)
	endif (HAVE_CONCURRENCY)

	list(APPEND CONCURRENCY_INCLUDES ${CONCURRENCY_INCLUDES})
	list(APPEND CONCURRENCY_LIBRARIES ${CONCURRENCY_LIBRARIES})
else (USE_THREADS)
	set(HAVE_CONCURRENCY FALSE)
endif (USE_THREADS)

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

# libicu
if (ICU_DIR)
	find_path(ICU_INCLUDE_DIR ustring.h "${ICU_DIR}/include/unicode")
	find_library(ICU_LIBS NAMES icuuc PATHS "${ICU_DIR}/lib")

	if (ICU_INCLUDE_DIR AND ICU_LIBS)
		list (APPEND ICU_INCLUDE_DIR ${ICU_INCLUDE_DIR})
		list (APPEND ICU_LIBS ${ICU_LIBS})
		set (ICU_FOUND TRUE)
	endif (ICU_INCLUDE_DIR AND ICU_LIBS)
else (ICU_DIR)
	find_path(ICU_INCLUDE_DIR unicode/uchar.h)
	find_library(ICU_LIBS NAMES icuuc libicu)
	set (ICU_FOUND FALSE)

	if (ICU_INCLUDE_DIR AND ICU_LIBS)
		list (APPEND ICU_INCLUDE_DIR ${ICU_INCLUDE_DIR})
		list (APPEND ICU_LIBS ${ICU_LIBS})
		set (ICU_FOUND TRUE)
	endif (ICU_INCLUDE_DIR AND ICU_LIBS)
endif (ICU_DIR)

# libfcgi
if (FCGI_DIR)
	find_path(FCGI_INCLUDE_DIR fcgi_config.h "${FCGI_DIR}/include")
	find_library(FCGI_LIBS NAMES fcgi++ PATHS "${FCGI_DIR}/lib")
	find_library(FCGI_LIBS NAMES fcgi PATHS "${FCGI_DIR}/lib")

	if (FCGI_INCLUDE_DIR AND FCGI_LIBS)
		list (APPEND FCGI_INCLUDE_DIR ${FCGI_INCLUDE_DIR})
		list (APPEND FCGI_LIBS ${FCGI_LIBS})
		set (FCGI_FOUND TRUE)
	endif (FCGI_INCLUDE_DIR AND FCGI_LIBS)
else (FCGI_DIR)
	find_path(FCGI_INCLUDE_DIR fcgi_config.h)

	set (FCGI_FOUND FALSE)

	if (FCGI_INCLUDE_DIR)
		list (APPEND FCGI_INCLUDE_DIR ${FCGI_INCLUDE_DIR})
		set (FCGI_FOUND TRUE)
	endif (FCGI_INCLUDE_DIR)

	set (FCGI_LIB_FOUND FALSE)

	if (FCGI_FOUND)
		find_library(FCGI_LIB NAMES fcgi)
		if (FCGI_LIB)
			list (APPEND FCGI_LIBS ${FCGI_LIB})
		set (FCGI_LIB_FOUND TRUE)
		endif(FCGI_LIB)
	endif(FCGI_FOUND)

	if (FCGI_LIB_FOUND)
		find_library(FCGI_LIBPP NAMES fcgi++)
		if (FCGI_LIBPP)
			list (APPEND FCGI_LIBS ${FCGI_LIBPP})
		set (FCGI_LIBPP_FOUND TRUE)
		endif(FCGI_LIBPP)
	endif(FCGI_LIB_FOUND)

endif (FCGI_DIR)

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
