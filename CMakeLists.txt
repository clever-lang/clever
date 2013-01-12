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
set(EXTRA_CLEVER_FILES)

# 3rd-party libraries
# ---------------------------------------------------------------------------
include(dependencies.cmake)

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

if (HAIKU)
	add_definitions(-DCLEVER_HAIKU)
endif (HAIKU)

# Build environment
# ---------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Debug)
	message(STATUS "No build specified, defaulting to Debug. Use -DCMAKE_BUILD_TYPE=Release to change")
endif (NOT CMAKE_BUILD_TYPE)

if (MSVC)
	set(CMAKE_CXX_FLAGS			"/DWIN32 /D_WINDOWS /Zm1000 /EHsc- /GR-")
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} /W1 /wd4503")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} /Zi /D_DEBUG /DCLEVER_DEBUG /MDd")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG /MD")
else (MSVC)
	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -ansi -fno-rtti -fno-exceptions")
	set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -fno-inline -ggdb -D_DEBUG -DCLEVER_DEBUG")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2 -DNDEBUG")
endif (MSVC)


if (TCMALLOC)
	set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ltcmalloc")
else (TCMALLOC)
	message(STATUS "Using default allocator. Use -DTCMALLOC=1 to use tcmalloc")
endif (TCMALLOC)

# Parser and Scanner
# ---------------------------------------------------------------------------
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/core)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
BISON_TARGET(CleverParser core/parser.y ${CMAKE_CURRENT_BINARY_DIR}/core/parser.cc)
RE2C_TARGET(CleverScanner core/scanner.re ${CMAKE_CURRENT_BINARY_DIR}/core/scanner.cc
	COMPILE_FLAGS "--case-inverted -bc")

ADD_RE2C_BISON_DEPENDENCY(CleverScanner CleverParser)

# Module options
# ---------------------------------------------------------------------------
include(modules.cmake)

# Issue #131 fix attempt.
# ---------------------------------------------------------------------------
if (UNIX)
	# Detect if this is Ubuntu.
	execute_process(COMMAND lsb_release -s -i
		OUTPUT_VARIABLE LSB_RELEASE OUTPUT_STRIP_TRAILING_WHITESPACE)

	if (${LSB_RELEASE} MATCHES "Ubuntu")
		# Add "-licu" to the end of the linker command line
		if (MOD_STD_UNICODE)
			set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -licuio -licuuc")
		endif (MOD_STD_UNICODE)

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

		if (LIBPTHREAD_FOUND)
			set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} ${LIBPTHREAD_LIBRARIES}")
		endif (LIBPTHREAD_FOUND)

	endif (${LSB_RELEASE} MATCHES "Ubuntu")

endif (UNIX)

# Main executable
# ---------------------------------------------------------------------------
add_executable(clever
	${RE2C_CleverScanner_OUTPUTS}
	${BISON_CleverParser_OUTPUTS}
	core/ast.h
	core/ast.cc
	core/astdump.h
	core/astvisitor.h
	core/astvisitor.cc
	core/asttransformer.h
	core/codegen.h
	core/codegen.cc
	core/clever.cc
	core/cthread.h
	core/cthread.cc
	core/clever.h
	core/compiler.cc
	core/compiler.h
	core/cstring.cc
	core/cstring.h
	core/driver.cc
	core/driver.h
	core/evaluator.cc
	core/evaluator.h
	core/environment.h
	core/ir.h
	core/main.cc
	core/module.h
	core/opcode.cc
	core/opcode.h
	core/pkgmanager.cc
	core/pkgmanager.h
	core/refcounted.h
	core/resolver.cc
	core/resolver.cc
	core/scanner.h
	core/scope.cc
	core/scope.h
	core/value.h
	core/vm.cc
	core/vm.h
	types/double.h
	types/double.cc
	types/int.h
	types/int.cc
	types/str.h
	types/str.cc
	types/native_types.h
	types/type.h
	types/type.cc
	types/function.h
	types/function.cc
	types/thread.h
	types/thread.cc
	types/bool.h
	types/bool.cc
	types/array.h
	types/array.cc
	types/map.h
	types/map.cc
	modules/std/file/file.cc
	modules/std/file/cfile.cc
	${EXTRA_CLEVER_FILES}
)
target_link_libraries(clever ${CLEVER_LIBRARIES})
include_directories(${CLEVER_INCLUDE_DIRS})

# Module trees
# ---------------------------------------------------------------------------
add_subdirectory(modules/std)
#add_subdirectory(modules/web)
add_dependencies(clever modules_std)
#add_dependencies(clever modules_std modules_web)
target_link_libraries(clever modules_std)
#target_link_libraries(clever modules_std modules_web)

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
	"core/stack.hh;core/parser.cc;core/parser.hh;core/location.hh;core/position.hh;core/scanner.cc")

# Packaging
# ---------------------------------------------------------------------------
set(CPACK_GENERATOR "STGZ;TBZ2;TGZ;ZIP;DEB")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Higor Eurípedes heuripedes@gmail.com")
set(CPACK_PACKAGE_CONTACT "Higor Eurípedes heuripedes@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "The Clever programming language")
include(CPack)

