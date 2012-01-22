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

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <cstring>
#include <vector>
#include <tr1/unordered_map>
#include "compiler/cstring.h"
#include "compiler/method.h"
#include "compiler/datavalue.h"

namespace clever {

/**
 * Global native type pointers
 */
#define CLEVER_INT_VAR    g_int_type_ptr
#define CLEVER_DOUBLE_VAR g_double_type_ptr
#define CLEVER_STR_VAR    g_str_type_ptr
#define CLEVER_BOOL_VAR   g_bool_type_ptr
#define CLEVER_BYTE_VAR   g_byte_type_ptr
#define CLEVER_ARRAY_VAR  g_array_type_ptr

#define CLEVER_INT    ::clever::CLEVER_INT_VAR
#define CLEVER_DOUBLE ::clever::CLEVER_DOUBLE_VAR
#define CLEVER_STR    ::clever::CLEVER_STR_VAR
#define CLEVER_BOOL   ::clever::CLEVER_BOOL_VAR
#define CLEVER_BYTE   ::clever::CLEVER_BYTE_VAR
#define CLEVER_ARRAY  ::clever::CLEVER_ARRAY_VAR
#define CLEVER_VOID	  NULL

#define CLEVER_GET_ARRAY_TEMPLATE ((const TemplatedType*)CLEVER_ARRAY)

/**
 * Arithmetic and assign operator method names
 */
#define CLEVER_OPERATOR_PLUS    "__plus__"
#define CLEVER_OPERATOR_MINUS   "__minus__"
#define CLEVER_OPERATOR_DIV     "__div__"
#define CLEVER_OPERATOR_MULT    "__mult__"
#define CLEVER_OPERATOR_MOD     "__mod__"
#define CLEVER_OPERATOR_ASSIGN  "__assign__"

/**
 * Bitwise operator method names
 */
#define CLEVER_OPERATOR_BW_XOR  "__bw_xor__"
#define CLEVER_OPERATOR_BW_AND  "__bw_and__"
#define CLEVER_OPERATOR_BW_OR   "__bw_or__"
#define CLEVER_OPERATOR_BW_NOT  "__bw_not__"
#define CLEVER_OPERATOR_LSHIFT  "__lshift__"
#define CLEVER_OPERATOR_RSHIFT  "__rshift__"

/**
 * Logical operator method names
 */
#define CLEVER_OPERATOR_NE      "__ne__"
#define CLEVER_OPERATOR_LE      "__le__"
#define CLEVER_OPERATOR_GE      "__ge__"
#define CLEVER_OPERATOR_EQUAL   "__equal__"
#define CLEVER_OPERATOR_LESS    "__less__"
#define CLEVER_OPERATOR_GREATER "__greater__"
#define CLEVER_OPERATOR_NOT     "__not__"

/**
 * Pre/pos inc dec operator method names
 */
#define CLEVER_OPERATOR_PRE_INC "__pre_inc__"
#define CLEVER_OPERATOR_POS_INC "__pos_inc__"
#define CLEVER_OPERATOR_PRE_DEC "__pre_dec__"
#define CLEVER_OPERATOR_POS_DEC "__pos_dec__"

/**
 * Prototype for class methods which the class represents a type
 */
#define CLEVER_TYPE_METHOD_ARGS const ValueVector* args, Value* retval, Value* value
#define CLEVER_TYPE_METHOD(name) void CLEVER_FASTCALL name(CLEVER_TYPE_METHOD_ARGS)

/**
 * Utils for handling TemplatedType
 */
#define CLEVER_TPL_ARG(arg) (getTypeArg(arg))

typedef ::std::vector<const Type*> TemplateArgs;

/**
 * Type representation
 */
class Type : public RefCounted {
public:
	typedef std::tr1::unordered_map<std::string, Method*> OverloadMethodMap;
	typedef std::tr1::unordered_map<std::string, OverloadMethodMap> MethodMap;
	typedef std::pair<std::string, Method*> MethodPair;

	explicit Type(const CString* name)
		: RefCounted(1), m_name(name) { }

	virtual ~Type();

	void addMethod(Method*);

	const Method* getMethod(const CString*, const TypeVector*) const;

	const CString* getName() const {
		return m_name;
	}

	/**
	 * Pure virtual methods
	 */
	virtual void init() = 0;

	/**
	 * Allocate a buffer for the type's attributes (if the type is not String, Double, Int, etc.)
	 */
	virtual DataValue* allocateValue() const = 0;

	/**
	 * Checks if this type accepts arguments
	 */
	virtual bool isTemplatedType() const {
		return false;
	}

	/**
	 * Destructor method. This method will be called when after a variable gets
	 * out of scope. This method should be overwritten for every type who needs
	 * some handling before a variable of this type get out of scope.
	 */
	virtual void destructor(Value* value) const {}
private:
	MethodMap m_methods;
	const CString* m_name;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

class TemplatedType : public Type {
public:
	explicit TemplatedType(const CString* name, size_t num_args)
		: Type(name), m_num_args(num_args) {}

	virtual bool isTemplatedType() const {
		return true;
	}

	size_t getNumArgs() const {
		return m_num_args;
	}

	const Type* getTypeArg(size_t index) const {
		return m_type_args[index];
	}

	virtual const Type* getTemplatedType(const Type*) const {
		return NULL;
	};

	virtual const Type* getTemplatedType(const Type*, const Type*) const {
		return NULL;
	};

	virtual const Type* getTemplatedType(const TemplateArgs&) const {
		return NULL;
	}
private:
	const size_t m_num_args;
	::std::vector<const Type*> m_type_args;

protected:
	void addArg(const Type* type) {
		m_type_args.push_back(type);
	}
};

} // clever

#endif // CLEVER_TYPE_H
