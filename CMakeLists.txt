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
if (NOT MSVC)
	pkg_check_modules(PCRECPP libpcrecpp)
else (NOT MSVC)
	# MSVC basic PCRE support.
	if (PCRECPP_DIR)
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
	endif (PCRECPP_DIR)
endif (NOT MSVC)

if (PCRECPP_FOUND)
	add_definitions(-DHAVE_PCRECPP)
endif (PCRECPP_FOUND)

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
	add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
endif (MSVC)

# Build environment
# ---------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(STATUS "No build specified, defaulting to Debug. Use -DCMAKE_BUILD_TYPE=Release to change")
endif (NOT CMAKE_BUILD_TYPE)

if (MSVC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /W1 /wd4503 /GR- /EHsc-")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} /O1 /Zi /D_DEBUG /DCLEVER_DEBUG /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MD")
else (MSVC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -ansi -fno-rtti -fno-exceptions")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
endif (MSVC)

# Parser and Scanner
# ---------------------------------------------------------------------------
BISON_TARGET(CleverParser interpreter/parser.y ${CMAKE_CURRENT_BINARY_DIR}/interpreter/parser.cc)
RE2C_TARGET(CleverScanner interpreter/scanner.re ${CMAKE_CURRENT_BINARY_DIR}/interpreter/scanner.cc
	COMPILE_FLAGS "--case-inverted -bc")

ADD_RE2C_BISON_DEPENDENCY(CleverScanner CleverParser)

# Module options
# ---------------------------------------------------------------------------
include(CMakeLists.modopt)

# Issue #131 fix attempt.
# ---------------------------------------------------------------------------
if (UNIX AND MOD_STD_REGEX)
	set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lpcrecpp")
endif (UNIX AND MOD_STD_REGEX)

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
target_link_libraries(clever ${CLEVER_LIBRARIES})
include_directories(${CLEVER_INCLUDE_DIRS})

# Module trees
# ---------------------------------------------------------------------------
add_subdirectory(modules/std)
add_subdirectory(modules/web)
add_dependencies(clever modules_std modules_web)
target_link_libraries(clever modules_std modules_web)

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

# Files to delete
# ---------------------------------------------------------------------------
set_directory_properties(PROPERTIES
	ADDITIONAL_MAKE_CLEAN_FILES
	"interpreter/stack.hh;interpreter/parser.cc;interpreter/parser.hh;interpreter/location.hh;interpreter/position.hh;interpreter/scanner.cc")

# Packaging
# ---------------------------------------------------------------------------
set(CPACK_GENERATOR "STGZ;TBZ2;TGZ;ZIP")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Clever programming language")
include(CPack)

