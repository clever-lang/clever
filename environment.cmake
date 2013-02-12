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
endif (WIN32)

if (APPLE)
	add_definitions(-DCLEVER_APPLE)
endif (APPLE)

if (CYGWIN)
	add_definitions(-DCLEVER_CYGWIN)
endif (CYGWIN)

if (MSVC)
	add_definitions(-DCLEVER_MSVC)
	add_definitions(-DCLEVER_MSVC_VERSION=${MSVC_VERSION})
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif (MSVC)

if (HAIKU)
	add_definitions(-DCLEVER_HAIKU)
endif (HAIKU)

# Build environment
# ---------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(STATUS "Building in debug mode. Use -DCMAKE_BUILD_TYPE=Release to change")
endif (NOT CMAKE_BUILD_TYPE)

if (MSVC)
	set(CMAKE_CXX_FLAGS         "/DWIN32 /D_WINDOWS /Zm1000 /EHsc- /GR-")
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /W1 /wd4503")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /Zi /D_DEBUG /DCLEVER_DEBUG /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MD")
else (MSVC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -fPIC -Wall -std=c++98 -fno-rtti -fno-exceptions")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEBUG} -Wno-unused-parameter -O0")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -ftrapv -fverbose-asm -finstrument-functions")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -fno-delete-null-pointer-checks -fno-omit-frame-pointer")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -fstack-check -fstack-protector")
	set(CMAKE_CXX_FLAGS_DEVEL   "${CMAKE_CXX_FLAGS_DEVEL} -Wstack-protector -Wextra")
endif (MSVC)

