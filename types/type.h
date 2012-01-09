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
 * Operator helpers
 */
#define CLEVER_OPERATOR_PLUS    "$+$"
#define CLEVER_OPERATOR_MINUS   "$-$"
#define CLEVER_OPERATOR_DIV     "$/$"
#define CLEVER_OPERATOR_MULT    "$*$"
#define CLEVER_OPERATOR_MOD     "$%$"
#define CLEVER_OPERATOR_BW_XOR  "$^$"
#define CLEVER_OPERATOR_BW_AND  "$&$"
#define CLEVER_OPERATOR_BW_OR   "$|$"
#define CLEVER_OPERATOR_NE      "$!=$"
#define CLEVER_OPERATOR_LE      "$<=$"
#define CLEVER_OPERATOR_GE      "$>=$"
#define CLEVER_OPERATOR_EQUAL   "$==$"
#define CLEVER_OPERATOR_LESS    "$<$"
#define CLEVER_OPERATOR_GREATER "$>$"

/**
 * Type handler definitions
 */
#define CLEVER_TYPE_INC_HANDLER_D    Value* increment(Value* value) const throw()
#define CLEVER_TYPE_DEC_HANDLER_D    Value* decrement(Value* value) const throw()
#define CLEVER_TYPE_ASSIGN_HANDLER_D void assign(Value* value, Value* newvalue) const throw()

/**
 * Prototype for class methods which the class represents a type
 */
#define CLEVER_TYPE_METHOD_ARGS const ValueVector* args, Value* retval, Value* value, Method* clv_method_
#define CLEVER_TYPE_METHOD(name) void CLEVER_FASTCALL name(CLEVER_TYPE_METHOD_ARGS) throw()

/**
 * Utils for handling TemplatedType
 */
#define CLEVER_TPL_ARG(arg) (getTypeArg(arg))

typedef ::std::vector<const Type*> TemplateArgs;

/**
 * Type representation
 */
class Type {
public:
	typedef std::tr1::unordered_map<std::string, Method*> OverloadMethodMap;
	typedef std::tr1::unordered_map<std::string, OverloadMethodMap> MethodMap;
	typedef std::pair<std::string, Method*> MethodPair;

	explicit Type(const char* name)
		: m_name(name) { }

	virtual ~Type() {
		MethodMap::const_iterator it = m_methods.begin(), end = m_methods.end();

		while (it != end) {
			OverloadMethodMap::const_iterator be = it->second.begin(),
				ed = it->second.end();

			while (be != ed) {
				delete be->second;
				++be;
			}

			++it;
		}
	}

	void addMethod(Method* method) throw() {
		const MethodArgs& args = method->getArgs();
		MethodArgs::const_iterator it = args.begin();
		std::string args_name;

		for (; it != args.end(); ++it) {
			args_name += it->second->getName();
			args_name += CLEVER_ARGS_SEPARATOR;
		}

		m_methods[method->getName()].insert(MethodPair(args_name, method));
	}

	const Method* getMethod(const CString* name, const TypeVector* args) const throw() {
		MethodMap::const_iterator it = m_methods.find(*name);
		std::string args_name;

		if (it == m_methods.end()) return NULL;

		if (args != NULL) {
			for (size_t i = 0; i < args->size(); ++i) {
				args_name += args->at(i)->getName();
				args_name += CLEVER_ARGS_SEPARATOR;
			}
		}

		OverloadMethodMap::const_iterator method_it = it->second.find(args_name);

		if (method_it != it->second.end()) {
			return method_it->second;
		}

		return NULL;
	}

	const char* getName() const throw() {
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
	 * Type handlers
	 */
	virtual CLEVER_TYPE_INC_HANDLER_D    = 0;
	virtual CLEVER_TYPE_DEC_HANDLER_D    = 0;
	virtual CLEVER_TYPE_ASSIGN_HANDLER_D = 0;

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
	const char* m_name;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

class TemplatedType : public Type {
public:
	explicit TemplatedType(const char* name, int num_args)
		: Type(name), m_num_args(num_args) {}

	virtual bool isTemplatedType() const {
		return true;
	}

	size_t getNumArgs() const {
		return m_num_args;
	}

	const Type* getTypeArg(int index) const {
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
	const int m_num_args;
	::std::vector<const Type*> m_type_args;

protected:
	void addArg(const Type* type) {
		m_type_args.push_back(type);
	}
};

} // clever

#endif // CLEVER_TYPE_H
