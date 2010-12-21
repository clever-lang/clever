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
#include <iostream>
#include <vector>
#include "compiler.h"

namespace clever {

void Compiler::Init(ast::TreeNode::nodeList nodes) {
	int level = 0;
	ast::TreeNode::nodeList::iterator it = nodes.begin();
	ast::TreeNode::nodeList::reverse_iterator rit = nodes.rbegin();
	std::string prefix("");

	while (it < nodes.end()) {
		if (!(*it)->debug().compare("{")) {
			prefix = std::string(level, ' ');
			++level;
		} else if (!(*it)->debug().compare("}")) {
			--level;
			prefix = std::string(level, ' ');
		}

		std::cout << prefix << "(" << (*it)->refCount() << ") " << (*it)->debug() << std::endl;

		if (!(*it)->delRef()) {
			delete *it;
		}
		++it;
	}
}

} // clever
