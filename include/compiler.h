/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_COMPILER_H
#define CLEVER_COMPILER_H

#include "ast.h"
#include "opcodes.h"

namespace clever {

#define GET_CONST_TYPE(x)         (x)->get_kind()
#define SAME_CONST_TYPE(x, y, t)  (GET_CONST_TYPE(x) == (t) && GET_CONST_TYPE(y) == (t))
#define HAS_SAME_CONST_TYPE(x, y) (GET_CONST_TYPE(x) == GET_CONST_TYPE(y))

class Compiler {
public:
	Compiler() { }

	void Init(ast::TreeNode::nodeList);
	void dumpAST(void);
	void buildIR(void);

	static void error(const char*);
	static bool checkCompatibleTypes(Value*, Value*);
	static ConstantValue* constantFolding(char, Value*, Value*);

	DISALLOW_COPY_AND_ASSIGN(Compiler);
private:
	ast::TreeNode::nodeList m_ast;
	VM::OpcodeList m_opcodes;
};

} // clever

#endif // CLEVER_COMPILER_H
