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
#include "types/type.h"

#include "core/vm.h"
#include "core/module.h"

#ifdef CLEVER_APPLE
# define MACOSX
#endif

namespace clever { namespace modules { namespace std {

typedef void* LibHandler;

struct FFIData {
	FFIData()
		: m_lib_handler(NULL) {}

	::std::string m_lib_name;
	LibHandler m_lib_handler;
};

class FFI : public Type {
public:
	FFI()
		: Type(CSTRING("FFILib")) {}

	~FFI() {}

	void init();

	void dump(const void* data, ::std::ostream& out) const {}

	virtual void increment(Value*, const VM*, CException*) const {}
	virtual void decrement(Value*, const VM*, CException*) const {}

	virtual void* allocData(CLEVER_TYPE_CTOR_ARGS) const;
	virtual void deallocData(void* data);

	CLEVER_METHOD(ctor);

	CLEVER_METHOD(call);
	CLEVER_METHOD(exec);
	CLEVER_METHOD(load);
	CLEVER_METHOD(unload);
private:
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
