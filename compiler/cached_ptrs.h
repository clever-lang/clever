/**
 * Clever programming language
 * Copyright (c) 2011-2012 Clever Team
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

#ifndef CLEVER_CACHE_PTR
#define CLEVER_CACHE_PTR

namespace clever {

class CString;

/**
 * Id to access the cache pointers
 */
enum {
	CLEVER_OP_PLUS,
	CLEVER_OP_MINUS,
	CLEVER_OP_DIV,
	CLEVER_OP_MULT,
	CLEVER_OP_MOD,
	CLEVER_OP_ASSIGN,
	CLEVER_OP_AT,
	CLEVER_OP_BW_XOR,
	CLEVER_OP_BW_AND,
	CLEVER_OP_BW_OR,
	CLEVER_OP_BW_NOT,
	CLEVER_OP_LSHIFT,
	CLEVER_OP_RSHIFT,
	CLEVER_OP_NE,
	CLEVER_OP_LE,
	CLEVER_OP_GE,
	CLEVER_OP_NOT,
	CLEVER_OP_EQUAL,
	CLEVER_OP_LESS,
	CLEVER_OP_GREATER,
	CLEVER_OP_PRE_INC,
	CLEVER_OP_POS_INC,
	CLEVER_OP_PRE_DEC,
	CLEVER_OP_POS_DEC,
	CLEVER_CTOR,
	CLEVER_CLONE,
	CLEVER_EMPTY_STR,
	CLEVER_VOID_STR,
	NUM_CACHED_PTRS
};

extern const CString* g_cache_ptrs[NUM_CACHED_PTRS];

#define CACHED_PTR(x)   g_cache_ptrs[x]
#define CACHE_PTR(x, y) (g_cache_ptrs[x] ? CACHED_PTR(x) : g_cache_ptrs[x] = CSTRING(y))

} // clever

#endif // CLEVER_CACHE_PTR
