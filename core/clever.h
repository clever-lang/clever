/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_H
#define CLEVER_H

#include <sstream>
#include <cstdarg>
#include <setjmp.h>

namespace clever {

extern jmp_buf fatal_error;

// Version macros
#define CLEVER_VERSION 100    // 0.1.0
#define CLEVER_VERSION_STRING "0.1.0-dev"

// Macro to abort execution
#ifndef CLEVER_APPLE
# define CLEVER_EXIT_FATAL() longjmp(fatal_error, 1)
#else
# define CLEVER_EXIT_FATAL() exit(1)
#endif

// Macro to delete pointer after checking for not null
#define CLEVER_SAFE_DELETE(x) do { if (x) { delete x; } } while (0)

// Disables copy constructor and copy assignment
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

// Detecting gcc version
#ifdef __GNUC__
# define CLEVER_GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
# define CLEVER_GCC_VERSION 0
#endif

// Compiler hint for unreachable code
#ifdef CLEVER_WIN
# define EMPTY_SWITCH_DEFAULT_CASE() default: __assume(0); break
#elsif defined(__GNUC__) && CLEVER_GCC_VERSION >= 40500
# define EMPTY_SWITCH_DEFAULT_CASE() __builtin_unreachable()
#else
# define EMPTY_SWITCH_DEFAULT_CASE() default: break
#endif

// Always inline (disregard -O options)
#if defined(__GNUC__) && __GNUC__ >= 3
# define CLEVER_FORCE_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
# define CLEVER_FORCE_INLINE __forceinline
#else
# define CLEVER_FORCE_INLINE
#endif

// Attribute for pure function
#ifdef __GNUC__
# define CLEVER_PURE_FUNC __attribute__((pure))
#else
# define CLEVER_PURE_FUNC
#endif

// Attribute for hot functions
#if defined(__GNUC__) && (CLEVER_GCC_VERSION >= 40300)
# define CLEVER_HOT_FUNC __attribute__((hot))
#else
# define CLEVER_HOT_FUNC
#endif

// No return attribute
#ifdef __GNUC__
# define CLEVER_NO_RETURN __attribute__((noreturn))
#else
# define CLEVER_NO_RETURN
#endif

// Try to use register to pass parameters
#if defined(__GNUC__) && CLEVER_GCC_VERSION >= 30040 && defined(__i386__)
# define CLEVER_FASTCALL __attribute__((fastcall))
#elif defined(_MSC_VER) && defined(_M_IX86)
# define CLEVER_FASTCALL __fastcall
#else
# define CLEVER_FASTCALL
#endif

// Disable VTable initialization (Microsoft-specific)
#if defined(_MSC_VER)
# define NO_INIT_VTABLE __declspec(novtable)
#else
# define NO_INIT_VTABLE
#endif

// GCC built-in function to provide the compiler with branch prediction information
#if (defined (__GNUC__) && __GNUC__ > 2 ) && !defined(DARWIN) && !defined(__hpux) && !defined(_AIX)
# define EXPECTED(cond)   __builtin_expect(!!(cond), 1)
# define UNEXPECTED(cond) __builtin_expect(!!(cond), 0)
#else
# define EXPECTED(cond)   (cond)
# define UNEXPECTED(cond) (cond)
#endif

// Thread-local storage
#if (defined(__GNUC__) && !defined(__APPLE__))
# define THREAD_TLS __thread
#elif defined(_MSC_VER)
# define THREAD_TLS __declspec(thread)
#else
# define THREAD_TLS
#endif

// Current function's name (based on BOOST's)
#if defined(__GNUC__)
# define CLEVER_CURRENT_FUNCTION __PRETTY_FUNCTION__
#elif defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 199901)
# define CLEVER_CURRENT_FUNCTION __func__
#else
# define CLEVER_CURRENT_FUNCTION "(unknown)"
#endif

// Utility functions and macros
#ifdef CLEVER_DEBUG
#define clever_assert(hypothesis, format, ...) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis), format)

#define clever_assert_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) == NULL, #hypothesis " must be NULL")

#define clever_assert_not_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) != NULL, #hypothesis " cannot be NULL")

void clever_assert_(const char* file, const char* function, long line, const char* expr,
		int hypothesis, const char* format, ...);
#else
#define clever_assert(hypothesis, format, ...)
#define clever_assert_null(hypothesis)
#define clever_assert_not_null(hypothesis)
#endif

void clever_error(const char* format, ...);
void clever_fatal(const char* format, ...) CLEVER_NO_RETURN;

void vsprintf(std::ostringstream&, const char*, va_list);
void sprintf(std::ostringstream&, const char*, ...);
void printf(const char*, ...);
void vprintfln(const char*, va_list);
void printfln(const char*, ...);

} // clever

#endif // CLEVER_H
