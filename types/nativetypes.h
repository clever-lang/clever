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

#ifndef CLEVER_NATIVE_TYPES_H
#define CLEVER_NATIVE_TYPES_H

#include "types/int.h"
#include "types/double.h"
#include "types/str.h"
#include "types/bool.h"

#define CLEVER_INT_VAR    g_int_type_ptr
#define CLEVER_DOUBLE_VAR g_double_type_ptr
#define CLEVER_STR_VAR    g_str_type_ptr
#define CLEVER_BOOL_VAR   g_bool_type_ptr

#define CLEVER_INT    ::clever::CLEVER_INT_VAR
#define CLEVER_DOUBLE ::clever::CLEVER_DOUBLE_VAR
#define CLEVER_STR    ::clever::CLEVER_STR_VAR
#define CLEVER_BOOL   ::clever::CLEVER_BOOL_VAR
#define CLEVER_VOID	  NULL

namespace clever {
	
extern THREAD_TLS Type* CLEVER_INT_VAR;
extern THREAD_TLS Type* CLEVER_DOUBLE_VAR;
extern THREAD_TLS Type* CLEVER_STR_VAR;
extern THREAD_TLS Type* CLEVER_BOOL_VAR;
	
}

#endif // CLEVER_NATIVE_TYPES_H
