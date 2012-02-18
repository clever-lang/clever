#
# Clever programming language
# Copyright (c) 2011-2012 Clever Team
#
# CMakeLists - CMake recipe
#

cmake_minimum_required(VERSION 2.6)

# Project details
# ---------------------------------------------------------------------------
project(Clever)

# Include directories
# ---------------------------------------------------------------------------
include_directories(.)

# Packages
# ---------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} .)
find_package(BISON)
find_package(RE2C)
find_package(PkgConfig)

# Options
# ---------------------------------------------------------------------------
option(MODREGEX "enable the regex module" ON)
option(MODFFI   "enable the ffi module" ON)

# Some variables
# ---------------------------------------------------------------------------
set(CLEVER_CFLAGS)
set(CLEVER_LDFLAGS)
set(CLEVER_LIBRARIES)
set(CLEVER_INCLUDE_DIRS)

# Libraries
# ---------------------------------------------------------------------------
pkg_check_modules(PCRECPP libpcrecpp)
if (PCRECPP_FOUND)
	add_definitions(-DHAVE_PCRECPP)
	if (MODREGEX)
		list(APPEND CLEVER_INCLUDE_DIRS ${PCRECPP_INCLUDE_DIRS})
		list(APPEND CLEVER_LIBRARIES ${PCRECPP_LIBRARIES})
		#list(APPEND CLEVER_CFLAGS ${PCRECPP_CFLAGS})
		#list(APPEND CLEVER_LDFLAGS ${PCRECPP_LDFLAGS})
	endif (MODREGEX)
endif (PCRECPP_FOUND)

if (MODFFI)
	if (NOT WIN32)
		pkg_check_modules(FFI libffi)

		if (FFI_FOUND)
			add_definitions(-DHAVE_FFI)
			list(APPEND CLEVER_INCLUDE_DIRS ${FFI_INCLUDE_DIRS})
			list(APPEND CLEVER_LIBRARIES ${FFI_LIBRARIES} dl)
			#list(APPEND CLEVER_CFLAGS ${FFI_CFLAGS})
			#list(APPEND CLEVER_LDFLAGS ${FFI_LDFLAGS})
		endif (FFI_FOUND)
	endif (NOT WIN32)
endif (MODFFI)

# Environment checks
if (WIN32)
	set(EXTRA_CLEVER_FILES win32/win32.cc)
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
endif (MSVC)

# Build environment
# ---------------------------------------------------------------------------
set(CMAKE_BUILD_TYPE        "Debug") # default to debug for now
set(CMAKE_CXX_FLAGS         "-Wall -ansi -fno-rtti -fno-exceptions")
set(CMAKE_CXX_FLAGS_DEBUG   "-O1 -ggdb -D_DEBUG -DCLEVER_DEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set_directory_properties(PROPERTIES
	ADDITIONAL_MAKE_CLEAN_FILES 
	"interpreter/stack.hh;interpreter/parser.cc;interpreter/parser.hh;interpreter/location.hh;interpreter/position.hh;interpreter/scanner.cc")

# Modules
# ---------------------------------------------------------------------------
add_subdirectory(modules/std)

# Parser and Scanner
# ---------------------------------------------------------------------------
BISON_TARGET(CleverParser interpreter/parser.y interpreter/parser.cc)
RE2C_TARGET(CleverScanner interpreter/scanner.re interpreter/scanner.cc
	COMPILE_FLAGS "--case-insensitive -bc")

ADD_RE2C_BISON_DEPENDENCY(CleverScanner CleverParser)

# Main executable
# ---------------------------------------------------------------------------
add_executable(clever
	${RE2C_CleverScanner_OUTPUTS}
	${BISON_CleverParser_OUTPUTS}
	types/map.cc
	types/bool.cc
	types/pair.cc
	types/type.cc
	types/double.cc
	types/byte.cc
	types/array.cc
	types/object.cc
	types/str.cc
	types/int.cc
	interpreter/main.cc
	interpreter/driver.cc
	compiler/cgvisitor.cc
	compiler/compiler.cc
	compiler/typechecker.cc
	compiler/clever.cc
	compiler/cstring.cc
	compiler/scope.cc
	compiler/pkgmanager.cc
	vm/vm.cc
	vm/opcode.cc
	${EXTRA_CLEVER_FILES}
)
add_dependencies(clever modules_std)
target_link_libraries(clever modules_std)

#set(clvcflags "")
#set(clvldflags "")
#foreach(flag ${CLEVER_CFLAGS})
#	set(clvcflags "${clvcflags} ${flag}")
#endforeach(flag)
#foreach(flag ${CLEVER_LDFLAGS})
#	set(clvcflags "${clvldflags} ${flag}")
#endforeach(flag)
#
#set_target_properties(clever
#	PROPERTIES
#	COMPILE_FLAGS "${clvcflags}"
#	LINK_FLAGS    "${clvldflags}"
#)
target_link_libraries(clever ${CLEVER_LIBRARIES})
include_directories(${CLEVER_INCLUDE_DIRS})

# Test runner
# ---------------------------------------------------------------------------
if(PCRECPP_FOUND)
	add_executable(testrunner
		extra/testrunner.cc
	)
	target_link_libraries(testrunner ${PCRECPP_LIBRARIES})
else(PCRECPP_FOUND)
	message(WARNING "testrunner will not be compiled. reason: libpcrecpp missing")
endif(PCRECPP_FOUND)


