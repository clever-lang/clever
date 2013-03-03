/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <stack>
#include "core/type.h"

namespace clever { namespace modules { namespace std {

struct CStackObject : public TypeObject {
	::std::stack<Value*> stack;
};

class CStack : public Type {
public:
	CStack()
		: Type("Stack") {}

	~CStack() {}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	// Methods
	CLEVER_METHOD(ctor);
	CLEVER_METHOD(push);
	CLEVER_METHOD(pop);
	CLEVER_METHOD(top);
};

}}} // clever::modules::std
