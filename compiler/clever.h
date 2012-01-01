/**
 * Clever programming language
 * Copyright (c) 2012 Clever Team
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef CLEVER_H
#define CLEVER_H

#include <iostream>
#include <cstdarg>

namespace clever {

/**
 * Disables copy constructor and copy assignment
 */
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

/**
 * Detecting gcc version
 */
#ifdef __GNUC__
# define CLEVER_GCC_VERSION (__GNUC__ * 1000 + __GNUC_MINOR__)
#else
# define CLEVER_GCC_VERSION 0
#endif

/**
 * Always inline (disregard -O options)
 */
#if defined(__GNUC__) && __GNUC__ >= 3
# define CLEVER_FORCE_INLINE inline __attribute__((always_inline))
#elif defined(_MSC_VER)
# define CLEVER_FORCE_INLINE __forceinline
#else
# define CLEVER_FORCE_INLINE
#endif

/**
 * Attribute for pure function
 */
#ifdef __GNUC__
# define CLEVER_PURE_FUNC __attribute__((pure))
#else
# define CLEVER_PURE_FUNC 
#endif

/**
 * Try to use register to pass parameters
 */
#if defined(__GNUC__) && CLEVER_GCC_VERSION >= 3004 && defined(__i386__)
# define CLEVER_FASTCALL __attribute__((fastcall))
#elif defined(_MSC_VER) && defined(_M_IX86)
# define CLEVER_FASTCALL __fastcall
#else
# define CLEVER_FASTCALL
#endif

/**
 * Disable VTable initialization (Microsoft-specific)
 */
#if defined(_MSC_VER)
# define NO_INIT_VTABLE __declspec(novtable)
#else
# define NO_INIT_VTABLE
#endif

/**
 * GCC built-in function to provide the compiler with branch prediction information
 */
#if (defined (__GNUC__) && __GNUC__ > 2 ) && !defined(DARWIN) && !defined(__hpux) && !defined(_AIX)
# define EXPECTED(cond)   __builtin_expect(cond, 1)
# define UNEXPECTED(cond) __builtin_expect(cond, 0)
#else
# define EXPECTED(cond)   (cond)
# define UNEXPECTED(cond) (cond)
#endif

/**
 * Thread-local storage
 */
#if __GNUC__
# define THREAD_TLS __thread
#elif defined(_MSC_VER)
# define THREAD_TLS __declspec(thread)
#else
# define THREAD_TLS
#endif


/**
 * Utility functions and macros.
 */

#ifdef CLEVER_DEBUG
#define clever_assert(Hypothesis, Format ...) \
	clever::clever_assert_(__FILE__, __LINE__, #Hypothesis, (Hypothesis), Format)
void clever_assert_(const char* file, long line, const char* expr,
		int hypothesis, const char* format, ...) throw();
#else
#define clever_assert(Hypothesis, Format, ...) 
#endif

void clever_fatal(const char* format, ...) throw();

void vsprintf(std::ostringstream&, const char*, va_list) throw();
void sprintf(std::ostringstream&, const char*, ...) throw();
void printf(const char*, ...) throw();
void vprintfln(const char*, va_list) throw();
void printfln(const char*, ...) throw();
} // clever 

#endif /* CLEVER_H */

