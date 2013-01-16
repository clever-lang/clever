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
#define clever_assert(hypothesis, format, ...) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis), format)

#define clever_assert_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) == NULL, #hypothesis " must be NULL")

#define clever_assert_not_null(hypothesis) \
	clever::clever_assert_(__FILE__, CLEVER_CURRENT_FUNCTION, __LINE__, #hypothesis, (hypothesis) != NULL, #hypothesis " must not be NULL")

void clever_assert_(const char* file, const char* function, long line, const char* expr,
		int hypothesis, const char* format, ...);
#else
#define clever_assert(hypothesis, format, ...)
#define clever_assert_null(hypothesis)
#define clever_assert_not_null(hypothesis)
#endif

// Macros to safely increase or decrease the reference count of an object
#define CLEVER_SAFE_ADDREF(x) do { if (x) { (x)->addRef(); } } while (0)
#define CLEVER_SAFE_DELREF(x) do { if (x) { (x)->delRef(); } } while (0)

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
 * @brief displays an error message and aborts the VM execution.
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

/* {{{ CString */
#define CLEVER_ARG_CSTR(index)	args[index]->getStr()
/* }}} */

/* {{{ String Pointer */
#define CLEVER_ARG_PSTR(index)	CLEVER_ARG_CSTR(index)->c_str() /* }}} */
#define CLEVER_ARG_DBL(index)	args[index]->getDouble()
#define CLEVER_ARG_INT(index)	args[index]->getInt()
#define CLEVER_ARG_BOOL(index)	args[index]->getBool()
#define CLEVER_ARG_OBJ(index)	args[index]->getObj()
#define CLEVER_ARG_DATA(index)	args[index]->getData()
#define CLEVER_ARG_TYPE(index)	args[index]->getType()
#define CLEVER_ARG_DUMP(index) 	args[index]->dump()
#define CLEVER_ARG_DUMPTO(index, stream) args[index]->dump(stream)
#define CLEVER_ARG_ISSET(index)	args->size() > index
#define CLEVER_ARG_ISTYPE(index, type) (args[index]->getType() == type)
/* }}} */

/* {{{ Return value setters */
#define CLEVER_RETURN_STR(c)	result->setStr(c)
#define CLEVER_RETURN_CSTR(c)	result->setStr(CSTRING(c))
#define CLEVER_RETURN_DBL(d)	result->setDouble(d)
#define CLEVER_RETURN_INT(i)	result->setInt(i)
#define CLEVER_RETURN_OBJ(o)	result->setObj(o)
#define CLEVER_RETURN_DATA(d)	result->setData(d)
#define CLEVER_RETURN_BOOL(b)   result->setBool(b)
#define CLEVER_RETURN_MAP(m)	\
	result->setType(CLEVER_MAP_TYPE);\
	result->setObj(m)
#define CLEVER_RETURN_ARRAY(m)	\
	result->setType(CLEVER_ARRAY_TYPE);\
	result->setObj(m)
/* }}} */

} // clever

#endif // CLEVER_H
