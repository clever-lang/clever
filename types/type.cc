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

#include "types/type.h"

namespace clever {

Type::~Type() {
	MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

	while (it != end) {
		OverloadMethodMap::const_iterator be = it->second.begin(),
			ed = it->second.end();

		while (be != ed) {
			be->second->delRef();
			++be;
		}

		++it;
	}
}

void Type::addMethod(Method* method) {
	const MethodArgs& args = method->getArgs();
	MethodArgs::const_iterator it = args.begin();
	int min_args = method->getMinNumArgs();
	int num_args = method->getNumArgs();
	std::string args_name;

	if (min_args != num_args) {
		method->setReference(0);
	}

	for (int n = 1; it != args.end(); ++it, ++n) {
		args_name += it->second->getName()->str();
		args_name += CLEVER_ARGS_SEPARATOR;
		if (min_args != num_args && n >= min_args) {
			m_methods[method->getName()].insert(MethodPair(args_name, method));
			method->addRef();
		}
	}
	if (min_args == num_args) {
		m_methods[method->getName()].insert(MethodPair(args_name, method));
	}
}

const Method* Type::getMethod(const CString* name, const TypeVector* args) const {
	MethodMap::const_iterator it = m_methods.find(*name);

	if (it == m_methods.end()) return NULL;

	std::string args_name;

	if (args != NULL) {
		for (size_t i = 0, j = args->size(); i < j; ++i) {
			args_name += args->at(i)->getName()->str();
			args_name += CLEVER_ARGS_SEPARATOR;
		}
	}

	OverloadMethodMap::const_iterator method_it = it->second.find(args_name);

	if (method_it != it->second.end()) {
		return method_it->second;
	}

	return NULL;
}

} // clever
