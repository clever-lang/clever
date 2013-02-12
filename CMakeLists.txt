#
# Clever programming language
# Copyright (c) 2011-2013 Clever Team
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
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
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
set(CLEVER_SOURCES)
#set(EXTRA_CLEVER_FILES)

# Platform checks
include(environment.cmake)

# 3rd-party libraries
# ---------------------------------------------------------------------------
include(dependencies.cmake)

if (TCMALLOC)
	set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ltcmalloc")
else (TCMALLOC)
	message(STATUS "Using default allocator. Use -DTCMALLOC=1 to use tcmalloc")
endif (TCMALLOC)

# Parser and Scanner
# ---------------------------------------------------------------------------
if (GEN_PARSER)
	set(re2c_opts)
	list(APPEND re2c_opts "-b")
	list(APPEND re2c_opts "-i")
	list(APPEND re2c_opts "--no-generation-date")

	if (NOT ${BISON_VERSION} VERSION_LESS "2.7.0")
		message(FATAL_ERROR "Clever parsers cannot be generated with Bison 2.7 yet.")
	endif (NOT ${BISON_VERSION} VERSION_LESS "2.7.0")

	message(STATUS "Clever parsers will be generated again.")

	if (${RE2C_VERSION} VERSION_GREATER "0.13.0")
		list(APPEND re2c_opts "-c")
	endif (${RE2C_VERSION} VERSION_GREATER "0.13.0")

	if (${RE2C_VERSION} VERSION_GREATER "0.13.2")
		list(APPEND re2c_opts "--case-inverted")
	endif (${RE2C_VERSION} VERSION_GREATER "0.13.2")

	set(core_dir ${CMAKE_CURRENT_SOURCE_DIR}/core)

	add_custom_command(
		OUTPUT ${core_dir}/parser.cc
		COMMAND ${BISON_EXECUTABLE} -l -o ${core_dir}/parser.cc
			${core_dir}/parser.y
		DEPENDS ${core_dir}/parser.y
		COMMENT "Generating parser from parser.y")

	add_custom_command(
		OUTPUT ${core_dir}/core/scanner.cc
		COMMAND ${RE2C_EXECUTABLE} ${re2c_opts} -o ${core_dir}/scanner.cc
			${core_dir}/scanner.re
		DEPENDS ${core_dir}/parser.cc ${core_dir}/scanner.re
		COMMENT "Generating scanner/lexer from scanner.re")

	set(core_dir)

endif (GEN_PARSER)

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

	endif (${LSB_RELEASE} MATCHES "Ubuntu")

endif (UNIX)

# Main executable
# ---------------------------------------------------------------------------
set(CORE_SOURCE
	core/cexception.h
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
	core/environment.cc
	core/environment.h
	core/ir.h
	core/irbuilder.h
	core/module.h
	core/opcode.cc
	core/opcode.h
	core/parser.cc
	core/platform.h
	core/modmanager.cc
	core/modmanager.h
	core/refcounted.h
	core/resolver.cc
	core/resolver.cc
	core/scanner.cc
	core/scanner.h
	core/scope.cc
	core/scope.h
	core/value.h
	core/value.cc
	core/vm.cc
	core/vm.h
	modules/std/core/double.h
	modules/std/core/double.cc
	modules/std/core/int.h
	modules/std/core/int.cc
	modules/std/core/str.h
	modules/std/core/str.cc
	types/native_types.h
	types/type.h
	types/type.cc
	modules/std/core/function.h
	types/thread.h
	types/thread.cc
	modules/std/core/bool.h
	modules/std/core/bool.cc
	modules/std/core/array.h
	modules/std/core/array.cc
	modules/std/core/map.h
	modules/std/core/map.cc
	modules/std/core/core.h
	modules/std/core/core.cc
	core/user.h
)

add_library(clever-static STATIC ${CORE_SOURCE}	${EXTRA_CLEVER_FILES})
set_target_properties(clever-static PROPERTIES OUTPUT_NAME "clever")
target_link_libraries(clever-static ${CLEVER_LIBRARIES})
include_directories(${CLEVER_STATIC_INCLUDE_DIRS})

add_library(clever-shared SHARED)
set_target_properties(clever-shared PROPERTIES OUTPUT_NAME "clever")
target_link_libraries(clever-shared clever-static)

add_executable(clever-cli core/main.cc)
set_target_properties(clever-cli PROPERTIES OUTPUT_NAME "clever")
target_link_libraries(clever-cli clever-static)

# Module trees
# ---------------------------------------------------------------------------
add_subdirectory(modules/std)
#add_subdirectory(modules/web)
add_dependencies(clever-static modules_std)
#add_dependencies(clever-static modules_std modules_web)
target_link_libraries(clever-static modules_std)
#target_link_libraries(clever-static modules_std modules_web)

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
add_dependencies(run-tests clever-cli)
add_dependencies(run-tests testrunner)

add_custom_target(run-mem-tests
	COMMAND ${TEST_RUNNER_BIN} -m;${CMAKE_CURRENT_SOURCE_DIR}/tests
	COMMENT "Running memory leak tests")
add_dependencies(run-tests clever-cli)
add_dependencies(run-mem-tests testrunner)

# Files to install
# ---------------------------------------------------------------------------
install(TARGETS clever-cli RUNTIME DESTINATION bin)
#install(TARGETS clever-static ARCHIVE DESTINATION lib)
install(TARGETS clever-shared LIBRARY DESTINATION lib)
install(DIRECTORY core/ modules/ types/ win32/
	DESTINATION include/clever FILES_MATCHING PATTERN "*.h")

# Files to delete
# ---------------------------------------------------------------------------
#set_directory_properties(PROPERTIES
#	ADDITIONAL_MAKE_CLEAN_FILES
#	"")

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

