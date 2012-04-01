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
#include <map>
#include <vector>

#ifdef CLEVER_MSVC
# include <unordered_map>
# include <unordered_set>
#else
# include <tr1/unordered_map>
# include <tr1/unordered_set>
#endif

#include "compiler/cstring.h"
#include "compiler/method.h"
#include "compiler/datavalue.h"

namespace clever {

extern const CString* g_cstring_cached_ptrs[25];

void init_type_cached_ptrs();

#define CLEVER_TYPE_CACHE_PTR(x, ptr) g_cstring_cached_ptrs[x] = ptr
#define CLEVER_TYPE_CACHED_PTR(name)  g_cstring_cached_ptrs[name]

/**
 * Global native type pointers
 */
#define CLEVER_INT_VAR    g_int_type_ptr
#define CLEVER_DOUBLE_VAR g_double_type_ptr
#define CLEVER_STR_VAR    g_str_type_ptr
#define CLEVER_BOOL_VAR   g_bool_type_ptr
#define CLEVER_BYTE_VAR   g_byte_type_ptr
#define CLEVER_ARRAY_VAR  g_array_type_ptr
#define CLEVER_MAP_VAR    g_map_type_ptr
#define CLEVER_OBJ_VAR    g_obj_type_ptr

#define CLEVER_INT    ::clever::CLEVER_INT_VAR
#define CLEVER_DOUBLE ::clever::CLEVER_DOUBLE_VAR
#define CLEVER_STR    ::clever::CLEVER_STR_VAR
#define CLEVER_BOOL   ::clever::CLEVER_BOOL_VAR
#define CLEVER_BYTE   ::clever::CLEVER_BYTE_VAR
#define CLEVER_ARRAY  ::clever::CLEVER_ARRAY_VAR
#define CLEVER_MAP    ::clever::CLEVER_MAP_VAR
#define CLEVER_OBJECT ::clever::CLEVER_OBJ_VAR
#define CLEVER_VOID	  NULL

extern Type* CLEVER_OBJ_VAR;

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

#define CLEVER_OPERATOR_AT      "__at__"

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
 * Internal constructor method name
 */
#define CLEVER_CTOR_NAME "$ctor$"

/**
 * Internal clone method name
 */
#define CLEVER_COPY_NAME "__copy__"
#define CLEVER_DEEP_COPY_NAME "__deep_copy__"

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
	typedef std::map<std::vector<const Type*>, Method*> OverloadMethodMap;
	typedef std::tr1::unordered_map<std::string, OverloadMethodMap> MethodMap;
	typedef std::pair<std::vector<const Type*>, Method*> MethodPair;
	typedef std::tr1::unordered_set<const Type*> InterfaceSet;

	explicit Type(const CString* name, const Type* super = CLEVER_OBJECT)
		: RefCounted(1), m_name(name), m_super(super) {}

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
	 * Checks if this type is an interface
	 */
	virtual bool isInterfaceType() const {
		return false;
	}

	/**
	 * Returns the super type of this type or NULL if none
	 */
	const Type* getSuperType() const {
		return m_super;
	}

	/**
	 * Returns true if this type is convertible to the type given
	 */
	bool isConvertibleTo(const Type* type) const {
		if (this == type) {
			return true;
		}

		if (getSuperType()) {
			return getSuperType()->isConvertibleTo(type);
		}

		return false;
	}

	/**
	 * Adds a interface to this type
	 */
	void addInterface(const Type* interface) {
		m_interfaces.insert(interface);
	}

	/**
	 * Returns a boolean indicating if the type implements this interface
	 */
	bool implementsInterface(const Type* interface) const {
		return (m_interfaces.find(interface) != m_interfaces.end());
	}

	/**
	 * Copy method
	 * This method will be called when making a shallow and deep copy of a Value
	 * pointer.
	 */
	virtual DataValue* copy(const Value* orig, bool deep) const { return NULL; }

	/**
	 * Destructor method
	 * This method will be called when after a variable gets
	 * out of scope. This method should be overwritten for every type
	 * who needs some handling before a variable of this type get out
	 * of scope.
	 */
	virtual void destructor(Value* value) const {}

protected:
	// Methods belonging this type
	MethodMap m_methods;

	// This type's name
	const CString* const m_name;

	// Type which this type is directly inherited
	const Type* const m_super;

	// Interfaces implemented
	InterfaceSet m_interfaces;

private:
	DISALLOW_COPY_AND_ASSIGN(Type);
};

class TemplatedType : public Type {
public:
	explicit TemplatedType(const CString* name, const Type* super)
		: Type(name, super) {}

	virtual bool isTemplatedType() const {
		return true;
	}

	const Type* getTypeArg(size_t index) const {
		return m_type_args[index];
	}

	size_t getNumArgs() const {
		return m_type_args.size();
	}

	virtual const std::string* checkTemplateArgs(const TemplateArgs& args) const = 0;
	virtual const Type* getTemplatedType(const Type*) const { return NULL; };
	virtual const Type* getTemplatedType(const Type*, const Type*) const { return NULL; };
	virtual const Type* getTemplatedType(const TemplateArgs& args) const { return NULL; };
private:
	std::vector<const Type*> m_type_args;

protected:
	void addArg(const Type* type) {
		m_type_args.push_back(type);
	}
};

class InterfaceType : public Type {
public:
	InterfaceType(const CString* name)
		: Type(name) {}

	~InterfaceType() {}

	virtual bool isInterfaceType() const {
		return true;
	}
};

} // clever

#endif // CLEVER_TYPE_H
