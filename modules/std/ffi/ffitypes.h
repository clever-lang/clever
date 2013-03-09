/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#ifndef CLEVER_STD_FFITYPES_H
#define CLEVER_STD_FFITYPES_H

#include <string>
#include "core/type.h"

namespace clever { namespace modules { namespace std {

class FFITypesBuilder : public TypeObject {
public:
	FFITypesBuilder() {}

	FFITypesBuilder(const ::std::string& name)
		: m_name(name) {}

	~FFITypesBuilder() {}

	const CString& getName() { return m_name; }
private:
	::std::string m_name;

	DISALLOW_COPY_AND_ASSIGN(FFITypesBuilder);
};

class FFITypes : public Type {
public:
	FFITypes()
		: Type("FFITypes") {}

	~FFITypes() {
		ExtStructs::iterator it(m_structs.begin()), end(m_structs.end());

		while (it != end) {
			if (it->second) {
				delete it->second;
			}
			++it;
		}
	}

	virtual void init();

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(addMember);
	CLEVER_METHOD(addFunction);

	static ExtStruct* getStruct(const CString& name);

	static ExtStructs m_structs;

private:
	DISALLOW_COPY_AND_ASSIGN(FFITypes);
};

}}} // clever::modules::std

#endif // CLEVER_STD_FFITYPES_H
