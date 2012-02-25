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

#ifndef CLEVER_METHOD_H
#define CLEVER_METHOD_H

#include <string>
#include <vector>
#include "compiler/clever.h"
#include "compiler/refcounted.h"

namespace clever {

class Value;
class Type;
class Method;

typedef std::vector<Value*> ValueVector;
typedef std::vector<const Type*> TypeVector;

/**
 * Prototype for class method implementation
 */
#define CLEVER_METHOD_ARGS const ValueVector* args, Value* retval, Value* value
#define CLEVER_METHOD(name) void CLEVER_FASTCALL name(CLEVER_METHOD_ARGS)

/**
 * Character used to mangling the method name with its argument types
 */
#define CLEVER_ARGS_SEPARATOR '#'

/**
 * Pointer to member representing a class method implementation
 */
typedef void (CLEVER_FASTCALL *MethodPtr)(CLEVER_METHOD_ARGS);

typedef std::pair<std::string, const Type*> MethodArgsPair;
typedef std::vector<MethodArgsPair> MethodArgs;

/**
 * Method representation
 */
class Method : public RefCounted {
public:
	enum MethodType { INTERNAL, USER };

	Method(std::string name, MethodPtr ptr, const Type* rtype, bool constness = true)
		: RefCounted(1), m_name(name), m_type(INTERNAL), m_rtype(rtype), m_num_args(0),
		m_min_args(0), m_is_const(constness)
	{
		m_info.ptr = ptr;
	}

	~Method() { }

	const std::string& getName() const { return m_name; }
	MethodPtr getPtr() const { return m_info.ptr; }

	void setInternal() { m_type = INTERNAL; }
	void setUserDefined() { m_type = USER; }

	bool isUserDefined() const { return m_type == USER; }
	bool isInternal() const { return m_type == INTERNAL; }

	void call(const ValueVector* args, Value* result, Value* context) const {
		m_info.ptr(args, result, context);
	}

	long call() const { return m_info.offset; }

	const MethodArgs& getArgs() const { return m_args; }

	void setReturnType(const Type* type) { m_rtype = type; }
	const Type* getReturnType() const { return m_rtype; }

	Method* addArg(std::string name, const Type* type) {
		m_args.push_back(MethodArgsPair(name, type));
		m_min_args = ++m_num_args;

		return this;
	}

	int getNumArgs() const { return m_num_args; }
	Method* setVariadic() { m_num_args = -1; return this; }
	bool isVariadic() const { return m_num_args < 0; }

	Method* setMinNumArgs(int nargs) { m_min_args = nargs; return this; }
	int getMinNumArgs() const { return m_min_args; }

	bool isConst() const {
		return m_is_const;
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

	int m_num_args;
	int m_min_args;
	bool m_is_const;

	DISALLOW_COPY_AND_ASSIGN(Method);
};

} // clever

#endif /* CLEVER_METHOD_H */
