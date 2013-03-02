/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */


#ifndef CLEVER_STD_FFI_H
#define CLEVER_STD_FFI_H

#include <iostream>
#include <string>
#include <map>
#include "core/cstring.h"
#include "core/type.h"
#include "core/vm.h"
#include "core/module.h"

#ifdef CLEVER_APPLE
# define MACOSX
#endif

namespace clever { namespace modules { namespace std {

class FFI;
typedef void* LibHandler;

typedef ::std::map<CString, Function*> FFIMethodsMap;
typedef ::std::map<CString, bool> FFIMethodsStatus;

struct FFIData : public TypeObject {
	FFIData(const FFI* type)
		: m_lib_handler(NULL), m_ffi(type) {}

	~FFIData();

	virtual Value* getMember(const CString*) const;

	::std::string m_func_name;
	::std::string m_lib_name;
	LibHandler m_lib_handler;
	const FFI* m_ffi;
};

class FFI : public Type {
public:
	FFI()
		: Type("FFILib"), m_call_handler(NULL) {}

	~FFI() {
		clever_delref(m_call_handler);
	}

	virtual void init(CLEVER_TYPE_INIT_ARGS);
	virtual TypeObject* allocData(CLEVER_TYPE_CTOR_ARGS) const;

	Value* getCallHandler() const { return m_call_handler; }

	CLEVER_METHOD(ctor);
	CLEVER_METHOD(call);
	CLEVER_METHOD(exec);
	CLEVER_METHOD(load);
	CLEVER_METHOD(unload);
	CLEVER_METHOD(callThisFunction);
private:
	Value* m_call_handler;

	DISALLOW_COPY_AND_ASSIGN(FFI);
};

class FFIModule : public Module {
public:
	FFIModule()
		: Module("std.ffi") {}

	~FFIModule() {}

	CLEVER_MODULE_VIRTUAL_METHODS_DECLARATION;
private:
	DISALLOW_COPY_AND_ASSIGN(FFIModule);
};

}}} // clever::modules::std

#endif // CLEVER_STD_FFI_H
