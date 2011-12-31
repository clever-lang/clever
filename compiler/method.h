/**
 * Clever programming language
 * Copyright (c) 2011 Clever Team
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

#ifndef CLEVER_METHOD_H
#define CLEVER_METHOD_H

#include <string>
#include <vector>
#include "compiler/clever.h"

namespace clever {

class Value;
class Type;
class Method;

typedef std::vector<Value*> ValueVector;
typedef std::vector<const Type*> TypeVector;

#define CLEVER_METHOD_ARGS const ValueVector* args, Value* retval, Value* value, Method* clv_method_
#define CLEVER_METHOD_NAME(name) clv_m_##name
#define CLEVER_METHOD(name) void CLEVER_FASTCALL name(CLEVER_METHOD_ARGS) throw()
#define CLEVER_ARGS_SEPARATOR '#'
#define CLEVER_CTOR_NAME "$ctor$"

typedef void (CLEVER_FASTCALL *MethodPtr)(CLEVER_METHOD_ARGS);
typedef std::tr1::unordered_map<std::string, const Type*> MethodArgs;
typedef std::pair<std::string, const Type*> MethodArgsPair;

/**
 * Method representation
 */
class Method {
public:
	enum MethodType { INTERNAL, USER };

	Method(std::string name, MethodPtr ptr, const Type* rtype)
		: m_name(name), m_type(INTERNAL), m_rtype(rtype)
	{
		m_info.ptr = ptr;
	}

	~Method() { }

	const std::string& getName() const throw() { return m_name; }
	MethodPtr getPtr() const throw() { return m_info.ptr; }

	void setInternal() throw() { m_type = INTERNAL; }
	void setUserDefined() throw() { m_type = USER; }

	bool isUserDefined() const throw() { return m_type == USER; }
	bool isInternal() const throw() { return m_type == INTERNAL; }

	void call(const ValueVector* args, Value* result, Value* context) const throw() {
		m_info.ptr(args, result, context, const_cast<Method*>(this));
	}

	long call() const throw() { return m_info.offset; }

	const MethodArgs& getArgs() const throw() { return m_args; }

	const Type* getReturn() const throw() { return m_rtype; }

	Method* addArg(std::string name, const Type* type) throw() {
		m_args.insert(MethodArgsPair(name, type));
		//++m_num_args;

		return this;
	}

private:
	union {
		MethodPtr ptr;
		long offset;
	} m_info;

	std::string m_name;
	MethodType m_type;

	/**
	 * Method arguments. (Lazy)
	 * Check with isArgsInitialized() before using it.
	 */
	MethodArgs m_args;

	/**
	 * Method's return type
	 */
	const Type* m_rtype;
};

} // clever

#endif /* CLEVER_METHOD_H */
