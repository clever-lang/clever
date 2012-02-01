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

#ifndef CLEVER_FUNCTION_H
#define CLEVER_FUNCTION_H

#include <string>
#include <vector>
#include "types/type.h"

namespace clever {

class Type;
class Value;
class Function;

typedef std::vector<Value*> ValueVector;

/**
 * Macros to help on module function declaration
 */
#define CLEVER_FUNCTION_ARGS const ValueVector* args, Value* retval
#define CLEVER_FUNC_NAME(name) clv_f_##name
#define CLEVER_NS_FNAME(ns, name) ns::clv_f_##name
#define CLEVER_FUNCTION(name) void CLEVER_FASTCALL CLEVER_FUNC_NAME(name)(CLEVER_FUNCTION_ARGS)

typedef void (CLEVER_FASTCALL *FunctionPtr)(CLEVER_FUNCTION_ARGS);
typedef std::tr1::unordered_map<std::string, Function*> FunctionMap;
typedef std::pair<std::string, Function*> FunctionPair;
typedef std::tr1::unordered_map<std::string, const Type*> FunctionArgs;
typedef std::pair<std::string, const Type*> FunctionArgsPair;

/**
 * Function representation
 */
class Function {
public:
	enum FunctionKind { INTERNAL, USER };

	explicit Function(std::string name)
		: m_name(name), m_kind(INTERNAL), m_num_args(0), m_min_args(0), m_rtype(NULL) { }

	Function(std::string name, FunctionPtr ptr)
		: m_name(name), m_kind(INTERNAL), m_num_args(0), m_min_args(0), m_rtype(NULL) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, const Type* rtype)
		: m_name(name), m_kind(INTERNAL), m_num_args(0), m_min_args(0), m_rtype(rtype) { m_info.ptr = ptr; }

	Function(std::string name, FunctionPtr ptr, int numargs, const Type* rtype)
		: m_name(name), m_kind(INTERNAL), m_num_args(numargs), m_min_args(0), m_rtype(rtype) { m_info.ptr = ptr; }

	Function(std::string& name, size_t offset)
		: m_name(name), m_kind(USER), m_num_args(0), m_min_args(0), m_rtype(NULL) { m_info.offset = offset; }

	Function(std::string& name, size_t offset, int numargs)
		: m_name(name), m_kind(USER), m_num_args(numargs), m_min_args(0), m_rtype(NULL) { m_info.offset = offset; }

	virtual ~Function() { }

	Function* addArg(std::string name, const Type* type) {
		m_args.insert(FunctionArgsPair(name, type));
		m_min_args = ++m_num_args;

		return this;
	}

	FunctionArgs& getArgs() { return m_args; }

	int getNumArgs() const { return m_num_args; }
	Function* setVariadic() { m_num_args = -1; return this; }
	bool isVariadic() const { return m_num_args < 0; }

	Function* setMinNumArgs(int nargs) { m_min_args = nargs; return this; }
	int getMinNumArgs() const { return m_min_args; }

	bool isUserDefined() const { return m_kind == USER; }
	bool isInternal() const { return m_kind == INTERNAL; }

	void setUserDefined() { m_kind = USER; }

	void setOffset(size_t num) { m_info.offset = num; m_kind = USER; }
	size_t getOffset() const { return m_info.offset; }

	void setReturnType(const Type* type) { m_rtype = type; }
	const Type* getReturnType() const { return m_rtype; }

	FunctionPtr getPtr() const { return m_info.ptr; }

	const std::string& getName() const { return m_name; }

	void call(const ValueVector* args, Value* result) const {
		m_info.ptr(args, result);
	}

	size_t call() const { return m_info.offset; }

private:
	union {
		FunctionPtr  ptr;
		size_t offset;
	} m_info;

	std::string m_name;
	FunctionKind m_kind;
	int m_num_args, m_min_args;
	const Type* m_rtype;
	FunctionArgs m_args;
};

} // clever

#endif /* CLEVER_FUNCTION_H */
