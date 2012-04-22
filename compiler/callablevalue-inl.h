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

#ifndef CLEVER_CALLABLEVALUEINL_H
#define CLEVER_CALLABLEVALUEINL_H

#ifndef CLEVER_CALLABLEVALUE_H
#include "callablevalue.h"
#endif

namespace clever {

inline CallableValue::~CallableValue() {
	if ((isNearCall() || isExternal()) && m_handler.func) {
		delete m_handler.func;
	}
	if (m_context && this != m_context) {
		m_context->delRef();
	}
}

inline void CallableValue::setHandler(Function* handler) {
	if (handler->isInternal()) {
		m_call_type = FAR;
	} else if (handler->isExternal()) {
		m_call_type = EXTERNAL;
	} else {
		m_call_type = NEAR;
	}
	m_handler.func = handler;
}

inline void CallableValue::call(Value* const result, const ValueVector* const args) const {
	clever_assert(m_call_type != NEAR, "Wrong call for user func/method!");

	if (isFunction()) {
		m_handler.func->call(args, result);
	} else {
		m_handler.method->call(args, result, m_context);
	}
}

} // clever

#endif // CALLABLEVALUEINL_H
