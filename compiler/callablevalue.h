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

#ifndef CLEVER_CALLABLEVALUE_H
#define CLEVER_CALLABLEVALUE_H

#include "value.h"

namespace clever {

/**
 * Class that represents the values of functions and methods.
 */
class CallableValue : public Value {
public:
	enum CallType {
		NONE,
		NEAR,    // Invoke compiled functions/methods
		FAR,     // Invoke built-in or loaded functions/methods (probably faster)
		EXTERNAL // External
	};

	enum CallableType {
		FUNCTION,
		METHOD
	};

	/* TODO: generate name for anonymous functions, disable setName(). */
	CallableValue()
		: Value(), m_call_type(NONE), m_context(NULL), m_callable_type(FUNCTION) {
		setType(CALL);
	}

	/**
	 * Create a CallableValue to represent a named function.
	 */
	explicit CallableValue(const CString* const name)
		: Value(), m_call_type(NONE), m_context(NULL),
		  m_callable_type(FUNCTION) {
		setName(name);
		setType(CALL);
	}

	/**
	 * Create a CallableValue able to represent a method.
	 */
	CallableValue(const CString* name, const Type* type)
		: Value(), m_call_type(NONE), m_context(NULL),
		  m_callable_type(METHOD) {
		setName(name);
		setTypePtr(type);
		setType(CALL);
	}

	~CallableValue();

	void setHandler(const Function* handler);

	void setHandler(const Method* const handler) {
		m_call_type = handler->isInternal() ? FAR : NEAR;
		m_handler.method = handler;
	}

	void setContext(Value* value) { m_context = value; }
	Value* getContext() const { return m_context; }

	FunctionPtr getFunctionPtr() const { return m_handler.func->getPtr(); }
	MethodPtr getMethodPtr() const { return m_handler.method->getPtr(); }

	const Function* getFunction() const { return m_handler.func; }
	const Method* getMethod() const { return m_handler.method; }

	bool isCallable() const { return true; }

	void setCallType(CallType type) { m_call_type = type; }

	bool isExternal() const { return m_call_type == EXTERNAL; }
	bool isNearCall() const { return m_call_type == NEAR; }
	bool isFarCall() const { return m_call_type == FAR; }

	/**
	 * Invokes the method/function pointer according with the type.
	 *
	 * Remember to set a context before calling a non-static method.
	 */
	void call(Value* const result, const ValueVector* const args) const CLEVER_HOT_FUNC ;

	void call(size_t& next_op) const {
		next_op = m_handler.func->call();
	}

	void setCallableType(CallableType type) {
		m_callable_type = type;
	}

	bool isFunction() const {
		return m_callable_type == FUNCTION;
	}

	bool isMethod() const {
		return m_callable_type == METHOD;
	}
private:
	union {
		const Function* func;
		const Method* method;
	} m_handler;

	CallType m_call_type;
	Value* m_context;
	CallableType m_callable_type;

	DISALLOW_COPY_AND_ASSIGN(CallableValue);
};

} // namespace clever

#include "callablevalue-inl.h"

#endif // CLEVER_CALLABLEVALUE_H
