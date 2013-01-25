/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_CEXCEPTION_H
#define CLEVER_CEXCEPTION_H

#include "core/value.h"

namespace clever {

class CException {
public:
	CException()
		: m_exception(NULL) {}

	~CException() {
		clever_delref(m_exception);
	}

	void clear() { m_exception = NULL; }

	Value* getException() const { return m_exception; }

	bool hasException() const { return m_exception != NULL; }

	void setException(const char* format, ...) {
		std::ostringstream out;
		va_list args;

		va_start(args, format);
		vsprintf(out, format, args);

		if (UNEXPECTED(m_exception == NULL)) {
			m_exception = new Value;
		}
		m_exception->setStr(new StrObject(out.str()));
	}

	void setException(Value* exception) {
		if (UNEXPECTED(m_exception == NULL)) {
			m_exception = new Value;
		}
		m_exception->copy(exception);
	}
private:
	Value* m_exception;
};

} // clever

#endif // CLEVER_CEXCEPTION_H
