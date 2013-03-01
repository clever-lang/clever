#
# Clever programming language
# Copyright (c) 2011-2013 Clever Team
#
# environment.cmake - Platform/Compiler-related configuration
#

# Platform checks
# ---------------------------------------------------------------------------
if (WIN32)
	set(CLEVER_SOURCES ${CLEVER_SOURCES} win32/dirent.h win32/win32.cc win32/win32.h)
	add_definitions(-DCLEVER_WIN32)
endif()

if (APPLE)
	add_definitions(-DCLEVER_APPLE)
endif()

if (CYGWIN)
	add_definitions(-DCLEVER_CYGWIN)
endif()

if (MSVC)
	add_definitions(-DCLEVER_MSVC)
	add_definitions(-DCLEVER_MSVC_VERSION=${MSVC_VERSION})
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif()

if (HAIKU)
	add_definitions(-DCLEVER_HAIKU)
endif()

if ("${CMAKE_CXX_COMPILER}" MATCHES "clang(\\+\\+)?$")
	set(CMAKE_COMPILER_IS_CLANGXX 1)
endif()

# Build environment
# ---------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(STATUS "Building in debug mode. Use -DCMAKE_BUILD_TYPE=Release to change")
endif()

if (MSVC)
	set(CMAKE_CXX_FLAGS         "/DWIN32 /D_WINDOWS /Zm1000 /EHsc- /GR-")
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /W1 /wd4503")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /Zi /D_DEBUG /DCLEVER_DEBUG /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MD")
else()
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -fPIC -Wall -std=c++98 -fno-rtti -fno-exceptions")

	if (ENABLE_WPADDED)
		set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wpadded")
	else()
		message(STATUS "Use -DENABLE_WPADDED=1 to enable padding messages")
	endif()

	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEBUG} -O0 -Wextra -Wno-unused-parameter -Wno-variadic-macros")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -pedantic -fverbose-asm -finstrument-functions")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -fno-omit-frame-pointer -fstack-protector")

	if (CMAKE_COMPILER_IS_CLANGXX)
		#set(CMAKE_CXX_FLAGS_DEVEL "${CMAKE_CXX_FLAGS_DEVEL} -Werror=gnu -DCLEVER_NOGNU")
	endif()
endif()

