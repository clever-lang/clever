/*
 * Clever language
 * Copyright (c) 2010 Clever Team
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
 *
 * $Id$
 */

#ifndef CLEVER_TYPES_H
#define CLEVER_TYPES_H

#include <sstream>
#include <string>
#include <vector>
#include "refcounted.h"
#include "cstring.h"
#include "values.h"
#include "opcodes.h"
#include "symboltable.h"

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
	TypeName(const TypeName&);             \
	void operator=(const TypeName&)

namespace clever {

class Method;

class Type {
public:
	typedef std::map<CString, Method*> MethodTable;

	enum {
		ABSTRACT  = 0x0,
		CONCRETE  = 0x1,
		INTERFACE = 0x1 << 1,
		BUILT_IN  = 0x1 << 2
	};

	Type(const CString& name, int kind)
		: m_name(name), m_kind(kind) {};

	Type(const CString& package, const CString& name, int kind)
		: m_package(name), m_name(name), m_kind(kind) {};

	virtual ~Type();

	virtual void Init();

	inline const CString& package() const { return m_package; };
	inline const CString& name() const { return m_name; };
	inline bool isInterface() const { return m_kind & INTERFACE; };
	inline bool isAbstract() const { return m_kind & ABSTRACT; };
	inline bool isConcrete() const { return m_kind & CONCRETE; };
	inline bool isBuilt_in() const { return m_kind & BUILT_IN; };

private:
	Type() {};
	DISALLOW_COPY_AND_ASSIGN(Type);

	CString m_package;
	CString m_name;
	int m_kind;
	Type* m_parent;
	MethodTable m_methods;
};

/**
 * This data structure represents a virtual parameter of
 * 	a method declaration
 */
struct Parameter {
	const Type* m_type;
	const CString* m_name;

	Parameter(const Type* type, const CString* name) :
		m_type(type), m_name(name) {}
};

/**
 * Checks if the type 'from' can be converted in type 'to'
 * 	(is 'to' is equal 'from' or inherited from 'from'?)
 *
 * @TODO: add verification
 */
inline bool isTypeConvertible(const Type* from, const Type* to)
{
	return true;
}

/**
 * This class is a representation of a class method.
 */
class Method {
public:
	/**
	 * Constructor.
	 * @param return_type: the method's return type
	 * @param parameters: the parameter
	 * @param opcodes: the method's body
	 */
	Method(Type* return_type, std::vector<Parameter*> parameters,
		std::vector<Opcode*> opcodes) :
			m_return_type(return_type),
			m_parameters(parameters),
			m_opcodes(opcodes) {}

	/**
	 * Do a verification if the type of values passed by parameter match with
	 * 	method's parameters types.
	 * This verification can be done in parsing time to show the error to the user.
	 *
	 * @param parameters: a vector with Value* passed to the method
	 * @param error: (OUT) error variable is not NULL before this function call
	 * 	means that the parameters do not match.
	 * @return: true if the parameters given match with this method
	 */
	bool verify(std::vector<Value*>* parameters, CString* error)
	{
		error = NULL;
		if (parameters->size() != m_parameters.size()) {
			error = new CString("Number of arguments mismatch");
			return false;
		}

		int sz = parameters->size();

		for (int i = 0; i < sz; ++i) {
			if (!isTypeConvertible(parameters->at(i)->getType(),
				m_parameters[i]->m_type)) {

				error = new CString("Argument type mismatch");
				return false;
			}
		}

		return true;
	}

	/**
	 * This method performs a Clever's method call
	 *
	 * @param parameters: the value of the parameters passed to this method
	 * @param error: if this CString* is not null, an error occurred
	 * @return: a Value* with the method's return value
	 */
	Value* run(std::vector<Value*>* parameters, CString* error)
	{
		int sz = m_parameters.size();

		SymbolTable::var_map method_scope;

		// Fills the map with pair [parameter_name, value]
		for (int i = 0; i < sz; ++i) {
			method_scope[m_parameters[i]->m_name] = parameters->at(i);
		}

		/**
		 * @TODO: We need to push the scope and run the opcodes
		 */

		return NULL;
	}

private:
	const Type* m_return_type;
	const std::vector<Parameter*> m_parameters;
	const std::vector<Opcode*> m_opcodes;
};

} // Clever

#endif // CLEVER_TYPES_H
