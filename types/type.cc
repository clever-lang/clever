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

	if (min_args != num_args && num_args != -1) {
		method->setReference(0);
	}

	std::vector<const Type*> v_args;
	for (int n = 1; it != args.end(); ++it, ++n) {
		v_args.push_back(it->second);
		if (min_args != num_args && n >= min_args) {
			m_methods[method->getName()].insert(MethodPair(v_args, method));
			method->addRef();
		}
	}/*
		if (method->getName() == "call") {
			std::cout << "aqui " << min_args  << " " << num_args << std::endl;
		}
		*/
	if (min_args == num_args || num_args == -1) {
		m_methods[method->getName()].insert(MethodPair(v_args, method));
	}
}

const Method* Type::getMethod(const CString* name, const TypeVector* args) const {
	MethodMap::const_iterator it1 = m_methods.find(*name);
	
	if (it1 == m_methods.end() && name != CSTRING(CLEVER_CTOR_NAME)) {
		// Looking up for super type's methods
		if (getSuperType()) {
			return getSuperType()->getMethod(name, args);
		}

		return NULL;
	}

	size_t num_args = (args ? args->size() : 0);

	OverloadMethodMap::const_iterator it = it1->second.begin(),
		itend = it1->second.end();

	while (it != itend) {
		const std::vector<const Type*>& vet = it->first;

		if (vet.size() == num_args) {
			bool found = true;

			for (size_t i = 0; i < num_args; ++i) {
				if (!args->at(i)->isConvertibleTo(vet[i])) {
					found = false;
					break;
				}
			}

			if (found) {
				return it->second;
			}
		} else if (it->second->isVariadic()
			&& num_args >= size_t(it->second->getMinNumArgs())) {
			// Variadic method
			return it->second;
		}
		++it;
	}

	// If we didn't find the method yet, look for it in the super type
	if (getSuperType() && name != CSTRING(CLEVER_CTOR_NAME)) {
		return getSuperType()->getMethod(name, args);
	}

	return NULL;
}

} // clever
