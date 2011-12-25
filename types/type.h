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

#ifndef CLEVER_TYPE_H
#define CLEVER_TYPE_H

#include <cstring>
#include <vector>
#include <tr1/unordered_map>
#include "compiler/cstring.h"
#include "compiler/method.h"
#include "compiler/datavalue.h"

namespace clever {

class CString;

/**
 * Type handler definitions
 */
#define CLEVER_TYPE_INC_HANDLER_D Value* increment(Value* value) const throw()
#define CLEVER_TYPE_DEC_HANDLER_D Value* decrement(Value* value) const throw()
#define CLEVER_TYPE_ASSIGN_HANDLER_D void assign(Value* value, Value* newvalue) const throw()
#define CLEVER_TYPE_MOD_HANDLER_D void modulus(Value* value, const Value* op1, const Value* op2) const throw()

/**
 * Prototype for class methods which the class represents a type
 */
#define CLEVER_TYPE_METHOD_ARGS const ValueVector* args, Value* retval, Value* value, Method* clv_method_
#define CLEVER_TYPE_METHOD(name) void CLEVER_FASTCALL name(CLEVER_TYPE_METHOD_ARGS) throw()

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
		const TypeVector* args = method->getArgs();
		
		std::string args_name;
		
		if (args != NULL) {
			for (size_t i = 0; i < args->size(); ++i) {
				args_name += args->at(i)->getName();
				args_name += CLEVER_ARGS_SEPARATOR;
			}
		}
		
		m_methods[method->getName()].insert(MethodPair(args_name, method));
	}

	const Method* getMethod(const CString* name, const TypeVector* args) const throw() {
		MethodMap::const_iterator it = m_methods.find(*name);

		std::string args_name;
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
	virtual CLEVER_TYPE_INC_HANDLER_D = 0;
	virtual CLEVER_TYPE_DEC_HANDLER_D = 0;
	virtual CLEVER_TYPE_ASSIGN_HANDLER_D = 0;
	virtual CLEVER_TYPE_MOD_HANDLER_D { }
private:
	MethodMap m_methods;
	const char* m_name;

	DISALLOW_COPY_AND_ASSIGN(Type);
};

} // clever

#endif // CLEVER_TYPE_H