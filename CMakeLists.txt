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
find_package(CLEVER)


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
endif (PCRECPP_FOUND)

pkg_check_modules(CGICC libcgicc)
if (CGICC_FOUND)
	add_definitions(-DHAVE_CGICC)
endif (CGICC_FOUND)

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
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif (MSVC)

# Build environment
# ---------------------------------------------------------------------------
set(CMAKE_BUILD_TYPE        "Debug") # default to debug for now
if (MSVC)
	set(CMAKE_CXX_FLAGS         "/W1 /wd4503 /GR- /EHsc-")
	set(CMAKE_CXX_FLAGS_DEBUG   "/O1 /Zi /D_DEBUG /DCLEVER_DEBUG /MTd")
	set(CMAKE_CXX_FLAGS_RELEASE "/O2 /DNDEBUG /MT")
else (MSVC)
	set(CMAKE_CXX_FLAGS         "-Wall -ansi -fno-rtti -fno-exceptions")
	set(CMAKE_CXX_FLAGS_DEBUG   "-fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
endif (MSVC)

set_directory_properties(PROPERTIES
	ADDITIONAL_MAKE_CLEAN_FILES
	"interpreter/stack.hh;interpreter/parser.cc;interpreter/parser.hh;interpreter/location.hh;interpreter/position.hh;interpreter/scanner.cc")

# Modules
# ---------------------------------------------------------------------------
include(CMakeLists.modopt)
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
add_dependencies(clever modules_std modules_web)
target_link_libraries(clever modules_std modules_web)

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
	add_dependencies(testrunner clever)
else(PCRECPP_FOUND)
	message(WARNING "testrunner will not be compiled. reason: libpcrecpp missing")
endif(PCRECPP_FOUND)

# Test runner
# ---------------------------------------------------------------------------
add_custom_target(run-tests
	COMMAND ./testrunner${CMAKE_EXECUTABLE_SUFFIX} -q;./tests
	COMMENT "Running tests")
add_dependencies(run-tests testrunner)

add_custom_target(run-mem-tests
	COMMAND ./testrunner${CMAKE_EXECUTABLE_SUFFIX} -m;./tests
	COMMENT "Running memory leak tests")
add_dependencies(run-mem-tests testrunner)

# Files to install
# ---------------------------------------------------------------------------
install(TARGETS clever RUNTIME DESTINATION bin)

