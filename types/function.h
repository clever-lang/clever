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

#ifndef CLEVER_FUNCTIONTYPE_H
#define CLEVER_FUNCTIONTYPE_H

#include "compiler/scope.h"
#include "types/type.h"
#include "types/functionvalue.h"
#include "compiler/value.h"

namespace clever {

class FunctionType : public TemplatedType {
public:
	FunctionType()
		: TemplatedType(CSTRING("Function"), CLEVER_OBJECT) {
		addArg(NULL);
	}

	FunctionType(const CString* name, const TemplateArgs& args) :
		TemplatedType(name, CLEVER_OBJECT) {

			for (size_t i = 0, sz = args.size(); i < sz; ++i) {
				addArg(args[i]);
			}
	}

 	const std::string* checkTemplateArgs(const TemplateArgs& args) const {
		if (args.size() < 1) {
			std::ostringstream oss;
			sprintf(oss, "Wrong number of template arguments given. "
				"`%S' requires at least the return type and no return type was given.",
				this->getName(), 0
			);

			return new std::string(oss.str());
		}

		return NULL;
	}

	virtual const Type* getTemplatedType(const TemplateArgs& args) const {
		std::string name = getName()->str() + "<";
		
		if (args[0]) {
			name += args[0]->getName()->str();
		}
		else {
			name += "Void";
		}

		for (size_t i = 1, sz = args.size(); i < sz; ++i) {
			name += ", ";
			if (args[i]) {
				name += args[i]->getName()->str();
			}
			else {
				// The type is Void
				name += "Void";
			}
		}

		name += ">";

		const CString* cname = CSTRING(name);
		const Type* type = g_scope.getType(cname);

		if (type == NULL) {
			Type* ntype = new FunctionType(cname, args);
			g_scope.pushType(cname, ntype);
			ntype->init();

			return ntype;
		}

		return type;
	}

	/**
	 * Virtual methods
	 */
	void init();
	DataValue* allocateValue() const;
	DataValue* copy(const Value*, bool) const;

	void destructor(Value* value) const { }

	/**
	 * Type methods
	 */
	static CLEVER_METHOD(do_assign);
	static CLEVER_METHOD(toString);
	static CLEVER_METHOD(call);
	static CLEVER_METHOD(constructor);
	static CLEVER_METHOD(valid);
private:
	DISALLOW_COPY_AND_ASSIGN(FunctionType);
};

} // clever

#endif // CLEVER_FUNCTIONTYPE_H
