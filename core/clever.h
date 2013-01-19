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
#include <vector>
#include <map>

#include "core/platform.h"

namespace clever {

class CException;
class Type;
class Value;

#define CLEVER_THROW(val, ...) exception->setException(val, ##__VA_ARGS__)

extern jmp_buf fatal_error;

// Version macros
#define CLEVER_VERSION 100    // 0.1.0
#define CLEVER_VERSION_STRING "0.1.0-dev"

// Disables copy constructor and copy assignment
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

// Utility functions and macros
#ifdef CLEVER_DEBUG
/**
 * @brief makes an assertion about an expression and aborts the execution on failure
 *
 * @note This function is only available when clever is compiled in debug mode.
 *
 * @note You should use the clever_assert(), clever_assert_null() and clever_assert_not_null()
 *       instead of this function.
 *
 * @param file file to report in the message
 * @param function function to report in the message
 * @param line line to report in the message
 * @param expr expression in string form to report in the message
 * @param hypothesis evaluated expression value (0 or non-0)
 * @param format vsprintf format string
 */
void clever_assert_(const char* file, const char* function, long line, const char* expr,
		int hypothesis, const char* format, ...);

#define clever_assert(hypothesis, format, ...) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis), format, ##__VA_ARGS__)

#define clever_assert_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) == NULL, #hypothesis " must be NULL")

#define clever_assert_not_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) != NULL, #hypothesis " must not be NULL")

/**
 *
 * @brief displays a debug message with file and line information
 *
 * @note This function is only available when clever is compiled in debug mode.
 *
 * @note You should use the clever_debug() macro instead of this function.
 *
 * @code
 *     clever_debug("My debug message.");
 * @endcode
 *
 * @param file file to report in the message
 * @param line the line to report in the message
 * @param format vsprintf format string
 */
void clever_debug_(const char* file, long line, const char* format, ...);
#define clever_debug(format, ...) clever::clever_debug_(__FILE__, __LINE__, format, ##__VA_ARGS__)

#else
#define clever_assert(hypothesis, format, ...)
#define clever_assert_null(hypothesis)
#define clever_assert_not_null(hypothesis)
#define clever_debug(format, ...)
#endif

/**
 * @brief deletes non-null pointers
 *
 * @note When clever is compiled in debug mode, this function will abort the
 *       execution with an assertion error if ptr is null.
 *
 * @param ptr a pointer allocated with the new keyword/operator.
 */
template<typename T>
inline void clever_delete(T* ptr) {
	clever_assert_not_null(ptr);

	if (ptr) {
		delete ptr;
	}
}

/**
 * @brief deletes non-null pointers and sets the variable to NULL
 *
 * @note ptr must be an lvalue otherwise the build will fail
 *
 * @param ptr a pointer allocated with the new keyword/operator.
 *
 * @see clever_delete()
 */
template<typename T>
inline void clever_delete_var(T*& ptr) {
	clever_delete(ptr);
	ptr = NULL;
}

/**
 * @defgroup ErrorReporting Error reporting functions
 * @{
 */

/**
 * @brief displays an error message.
 */
void clever_error(const char* format, ...);

/**
 * @brief displays a fatal error message and aborts the VM execution.
 */
void clever_fatal(const char* format, ...) CLEVER_NO_RETURN;

void vsprintf(std::ostringstream&, const char*, va_list);
void sprintf(std::ostringstream&, const char*, ...);
void printf(const char*, ...);
void vprintfln(const char*, va_list);
void printfln(const char*, ...);

/** @} */

#define clever_check_args(spec) clever::check_args(args, spec, exception, this)
#define clever_static_check_args(spec) clever::check_args(args, spec, exception)
#define clever_check_no_args()  clever_check_args(NULL)
#define clever_static_check_no_args()  clever_static_check_args(NULL)

bool check_args(const ::std::vector<Value*>&, const char*, CException*, const Type* = NULL);

#define CLEVER_GET_OBJECT(t, n) static_cast<t>((n)->getObj())

} // clever

#endif // CLEVER_H
