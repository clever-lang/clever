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
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
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

# 3rd-party libraries
# ---------------------------------------------------------------------------
include(CMakeLists.depends)

# Environment checks
# ---------------------------------------------------------------------------
if (WIN32)
	set(EXTRA_CLEVER_FILES win32/dirent.h win32/win32.cc win32/win32.h)
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
	set(CMAKE_CXX_FLAGS			"/DWIN32 /D_WINDOWS /Zm1000 /EHsc- /GR-")
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /W1 /wd4503")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} /Zi /D_DEBUG /DCLEVER_DEBUG /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MD")
else (MSVC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -ansi -fno-rtti -fno-exceptions")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
endif (MSVC)


if (TCMALLOC)
	set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ltcmalloc")
else (TCMALLOC)
	message(STATUS "Using default allocator. Use -DTCMALLOC=1 to use tcmalloc")
endif (TCMALLOC)

# Parser and Scanner
# ---------------------------------------------------------------------------
BISON_TARGET(CleverParser interpreter/parser.y ${CMAKE_SOURCE_DIR}/interpreter/parser.cc)
RE2C_TARGET(CleverScanner interpreter/scanner.re ${CMAKE_SOURCE_DIR}/interpreter/scanner.cc
	COMPILE_FLAGS "--case-inverted -bc")

ADD_RE2C_BISON_DEPENDENCY(CleverScanner CleverParser)

# Module options
# ---------------------------------------------------------------------------
include(CMakeLists.modopt)

# Issue #131 fix attempt.
# ---------------------------------------------------------------------------
if (UNIX)
	# Detect if this is Ubuntu.
	execute_process(COMMAND lsb_release -s -i
		OUTPUT_VARIABLE LSB_RELEASE OUTPUT_STRIP_TRAILING_WHITESPACE)

	if (${LSB_RELEASE} MATCHES "Ubuntu")
		# Add "-lpcrecpp" to the end of the linker command line.
		if (MOD_STD_REGEX)
			set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lpcrecpp")
		endif (MOD_STD_REGEX)

		# Add "-lcgicc" to the end of the linker command line.
		if (MOD_WEB_REQUEST OR MOD_WEB_SESSION)
			set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lcgicc")
		endif (MOD_WEB_REQUEST OR MOD_WEB_SESSION)

		# Add "-lffi -ld" to the end of the linker command line.
		if (MOD_STD_FFI)
			set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lffi -ldl")
		endif (MOD_STD_FFI)
	endif (${LSB_RELEASE} MATCHES "Ubuntu")

endif (UNIX)

# Main executable
# ---------------------------------------------------------------------------
add_executable(clever
	${RE2C_CleverScanner_OUTPUTS}
	${BISON_CleverParser_OUTPUTS}
	compiler/cached_ptrs.h
	compiler/callablevalue.cc
	compiler/callablevalue.h
	compiler/callablevalue-inl.h
	compiler/cgvisitor.cc
	compiler/cgvisitor.h
	compiler/clever.cc
	compiler/clever.h
	compiler/compiler.cc
	compiler/compiler.h
	compiler/cstring.cc
	compiler/cstring.h
	compiler/datavalue.h
	compiler/function.h
	compiler/method.h
	compiler/module.cc
	compiler/module.h
	compiler/pkgmanager.cc
	compiler/pkgmanager.h
	compiler/refcounted.h
	compiler/scope.cc
	compiler/scope.h
	compiler/scope-inl.h
	compiler/symbol.h
	compiler/typechecker.cc
	compiler/typechecker.h
	compiler/value.cc
	compiler/value.h
	interpreter/ast.cc
	interpreter/ast.h
	interpreter/asttransformer.h
	interpreter/astvisitor.h
	interpreter/driver.cc
	interpreter/driver.h
	interpreter/main.cc
	interpreter/scanner.h
	types/array.cc
	types/array.h
	types/arrayvalue.h
	types/bool.cc
	types/bool.h
	types/byte.cc
	types/byte.h
	types/double.cc
	types/double.h
	types/function.cc
	types/function.h
	types/functionvalue.h
	types/int.cc
	types/int.h
	types/iterator.cc
	types/iterator.h
	types/map.cc
	types/map.h
	types/mapvalue.h
	types/mapiterator.cc
	types/mapiterator.h
	types/mapiteratorvalue.h
	types/nativetypes.h
	types/object.cc
	types/object.h
	types/pair.cc
	types/pair.h
	types/pairvalue.h
	types/str.cc
	types/str.h
	types/type.cc
	types/type.h
	vm/opcode.cc
	vm/opcode.h
	vm/operand.h
	vm/vm.cc
	vm/vm.h
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
set(TEST_RUNNER_BIN ${CMAKE_BINARY_DIR}/testrunner${CMAKE_EXECUTABLE_SUFFIX})
add_custom_target(run-tests
	COMMAND ${TEST_RUNNER_BIN} -q;${CMAKE_CURRENT_SOURCE_DIR}/tests
	COMMENT "Running tests")
add_dependencies(run-tests testrunner)

add_custom_target(run-mem-tests
	COMMAND ${TEST_RUNNER_BIN} -m;${CMAKE_CURRENT_SOURCE_DIR}/tests
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
set(CPACK_GENERATOR "STGZ;TBZ2;TGZ;ZIP;DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Higor Eurípedes heurípedes@gmail.com")
set(CPACK_PACKAGE_CONTACT "Higor Eurípedes heuripedes@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Clever programming language")
include(CPack)

