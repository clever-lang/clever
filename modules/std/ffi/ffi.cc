/**
 * Clever programming language
 * Copyright (c) Clever Team
 *
 * This file is distributed under the MIT license. See LICENSE for details.
 */

#include <cmath>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <map>
#include <string>
#ifndef __APPLE__
# include <ffi.h>
#else
# include <ffi/ffi.h>
#endif
#ifdef CLEVER_WIN32
# include <windows.h>
#else
# include <dlfcn.h>
#endif
#include "core/clever.h"
#include "modules/std/core/function.h"
#include "core/type.h"
#include "core/value.h"
#include "modules/std/ffi/ffi.h"
#include "modules/std/ffi/ffistruct.h"
#include "modules/std/ffi/ffitypes.h"

namespace clever { namespace modules { namespace std {

extern "C" {
typedef void (*ffi_call_func)();
}

#if defined(CLEVER_WIN32)
static const char* CLEVER_DYLIB_EXT = ".dll";
#elif defined(CLEVER_APPLE)
static const char* CLEVER_DYLIB_EXT = ".dylib";
#else
static const char* CLEVER_DYLIB_EXT = ".so";
#endif

static ffi_type* _find_ffi_type(FFIType type)
{
	switch (type) {
		case FFIINT:     return &ffi_type_sint32;
		case FFIDOUBLE:  return &ffi_type_double;
		case FFIBOOL:    return &ffi_type_schar;
		case FFIPOINTER: return &ffi_type_pointer;
		case FFIVOID:    return &ffi_type_void;
		case FFISTRUCT:  return &ffi_type_pointer;
		case FFISTRING:  return &ffi_type_pointer;
	}
	return NULL;
}

static bool _load_lib(FFIData* h, const CString* libname)
{
	if (h->m_lib_handler != NULL) {
		dlclose(h->m_lib_handler);
	}

	h->m_lib_name = *libname;
	h->m_lib_handler = dlopen((h->m_lib_name + CLEVER_DYLIB_EXT).c_str(), RTLD_LAZY);

	return h->m_lib_handler != NULL;
}

/* XXX(heuripedes): please use this function instead of directly calling dlsym
 *                  so we don't have to maintain a zilion versions of the same code.
 */
static inline ffi_call_func _ffi_dlsym(void* handler, const char* name)
{
#ifdef CLEVER_WIN32
#  error "Dynamic library symbol loading support is not yet available for windows. Please disable this module."
#endif

	/* XXX(heuripedes): iso c++ forbids casts between pointer-to-function and
	 *                  pointer-to-object as .code and .data pointers are not
	 *                  garanteed to be compatible in some platforms.
	 *                  THE CODE BELLOW IS A HACK TO SHUT THE COMPILER UP.
	 */
	union {
		void *p;
		ffi_call_func fp;
	} u;

	u.p = dlsym(handler, name);

	return u.fp;
}

static inline ffi_call_func _ffi_get_pf(void* lib_handler, const CString* func)
{
	ffi_call_func fpf = _ffi_dlsym(lib_handler, func->c_str());

	if (fpf == NULL) {
		return 0;
	}

	return fpf;
}

static void _ffi_call(Value* result, ffi_call_func pf, size_t n_args,
					  FFIType rt, const ::std::vector<Value*>& args, size_t offset,
					  ExtMemberType* ext_args_types = 0)
{
	ffi_cif cif;
	ffi_type* ffi_rt = _find_ffi_type(rt);
	ffi_type** ffi_args = (ffi_type**) malloc(n_args * sizeof(ffi_type*));
	void** ffi_values = (void**) malloc(n_args * sizeof(void*));

	for (size_t i = 0; i < n_args; ++i) {
		Value* v = args.at(i + offset);
		FFIType arg_type = FFIVOID;

		if (ext_args_types) {
			arg_type = ext_args_types->at(i + 1);
		}

		if (v->isInt()) {
			if (arg_type == FFIVOID or arg_type == FFIINT) {
				ffi_args[i] = _find_ffi_type(FFIINT);

				int* vi= (int*) malloc(sizeof(int));

				*vi = v->getInt();

				ffi_values[i] =  vi;
			} else {
				clever_error("Argument %N isn't a int!\n", i + 1);
				return;
			}
		} else if (v->isBool()) {
			if (arg_type == FFIVOID or arg_type == FFIBOOL) {
				ffi_args[i] = _find_ffi_type(FFIBOOL);

				char* b = (char*) malloc (sizeof(char));

				*b = v->getBool();

				ffi_values[i] = b;
			} else {
				clever_error("Argument %N isn't a bool!\n", i + 1);
				return;
			}
		} else if (v->isStr()) {
			if (arg_type == FFIVOID or arg_type == FFISTRING) {
				const char* st = v->getStr()->c_str();
				char** s = (char**) malloc(sizeof(char*));

				*s = (char*) malloc (sizeof(char) * (strlen(st) + 1));

				strcpy(*s, st);
				(*s)[strlen(st)] = '\0';

				ffi_args[i] = _find_ffi_type(FFISTRING);

				ffi_values[i] =  s;
			} else {
				clever_error("Argument %N isn't a string!\n", i + 1);
				return;
			}
		} else if (v->isDouble()) {
			if (arg_type == FFIVOID or arg_type == FFIDOUBLE) {
				ffi_args[i] = _find_ffi_type(FFIDOUBLE);;

				double* d = (double*) malloc(sizeof(double));

				*d = v->getDouble();

				ffi_values[i] = d;
			} else {
				clever_error("Argument %N isn't a double!\n", i + 1);
				return;
			}
		} else {
			if (arg_type == FFIVOID or arg_type == FFIPOINTER) {
				ffi_args[i] = _find_ffi_type(FFIPOINTER);

				FFIStructData* obj = static_cast<FFIStructData*>(v->getObj());

				ffi_values[i] = &(obj->data);
			} else {
				clever_error("Argument %N isn't a pointer!\n", i + 1);
				return;
			}
		}
	}

	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, ffi_rt, ffi_args) != FFI_OK) {
		result->setBool(false);
		return;
	}

#ifndef CLEVER_WIN32
	if (rt == FFIINT) {
		int vi;

		ffi_call(&cif, pf, &vi, ffi_values);

		result->setInt(vi);
	} else if (rt == FFIDOUBLE) {
		double vd;

		ffi_call(&cif, pf, &vd, ffi_values);

		result->setDouble(vd);
	} else if (rt == FFIBOOL) {
		bool vb;

		ffi_call(&cif, pf, &vb, ffi_values);

		result->setBool(vb);
	} else if (rt == FFISTRING) {
		char* vs[1];

		ffi_call(&cif, pf, &vs, ffi_values);

		result->setStr(CSTRING(*vs));

		free(vs[0]);
	} else if (rt == FFIBOOL) {
		char vc;

		ffi_call(&cif, pf, &vc, ffi_values);

		result->setBool(vc);
	} else if (rt == FFIVOID) {
		ffi_call(&cif, pf, NULL, ffi_values);

		result->setBool(true);
	} else if (rt == FFIPOINTER) {
		//FFIObjectValue* x = static_cast<FFIObjectValue*> (retval->getDataValue());

		//if ( x == NULL ) x = new FFIObjectValue();

		//ffi_call(&cif, pf, &(x->pointer), ffi_values);

		//CLEVER_RETURN_DATA_VALUE(x);
	} else {
		result->setBool(true);
	}
#endif

	for (size_t i = 0; i < n_args; ++i) {
		Value* v = args.at(i + offset);

		if (v->isInt()) {
			free((int*)ffi_values[i]);
		} else if (v->isBool()) {
			free((char*)ffi_values[i]);
		} else if (v->isStr()) {
			char** v= (char**)ffi_values[i];
			free(v[0]);
			free(v);
		} else if (v->isDouble()) {
			free((double*)ffi_values[i]);
		} //else if (CLEVER_ARG_IS_INTERNAL(i)) {
		//}
	}

	free(ffi_args);
	free(ffi_values);
}

// FFILib constructor
CLEVER_METHOD(FFI::ctor)
{
	if (!clever_check_args("s")) {
		return;
	}

	FFIData* data = new FFIData(this);
	const CString* name = args[0]->getStr();

	if (!_load_lib(data, name)) {
		clever_throw("Failed to open %S!", name);
	}

	result->setObj(this, data);
}

FFIData::~FFIData()
{
	if (m_lib_handler) {
		dlclose(m_lib_handler);
	}
}

MemberData FFIData::getMember(const CString* name) const
{
	const_cast<FFIData*>(this)->m_func_name = *name;
	MemberData mdata = TypeObject::getMember(name);

	if (!mdata.value) {
		return m_ffi->getCallHandler();
	}

	return mdata;
}

CLEVER_METHOD(FFI::callThisFunction)
{
	FFIData* handler = clever_get_this(FFIData*);
	const CString func = handler->m_func_name;

	ExtStruct* ext_struct = FFITypes::getStruct(handler->m_lib_name);

	FFIType rt = FFIVOID;

	size_t n_args = args.size();
	size_t offset = 0;
	ExtMemberType* args_types = 0;

	if (ext_struct) {
		args_types = ext_struct->getArgs(func);
		n_args = args_types->size() - 1;
		rt = args_types->at(0);
	} else {
		n_args--;
		offset = 1;
		rt = static_cast<FFIType>(args.at(0)->getInt());
	}

	ffi_call_func pf;

	pf = _ffi_dlsym(handler->m_lib_handler, func.c_str());

	if (pf == NULL) {
		clever_throw("function `%S' don't exist!", &func);
		return;
	}

	_ffi_call(result, pf, n_args, rt, args, offset, args_types);
}

// FFILib.exec()
CLEVER_METHOD(FFI::exec)
{
	if (!clever_check_args("ss*")) {
		return;
	}

	const CString* lib = args.at(0)->getStr();
	const CString* func = args.at(1)->getStr();
	FFIType rt = static_cast<FFIType>(args.at(2)->getInt());
	size_t n_args = args.size() - 3;

#ifndef CLEVER_WIN32
	void* lib_handler = dlopen((*lib + CLEVER_DYLIB_EXT).c_str(), RTLD_LAZY);
	ffi_call_func pf = _ffi_get_pf(lib_handler,
								   func);
	if (pf == 0) {
		clever_throw("function `%S' don't exist!", func);
		return;
	}
#endif

	_ffi_call(result, pf, n_args, rt, args, 3);
	dlclose(lib_handler);
}

// FFILib.call()
CLEVER_METHOD(FFI::call)
{
	if (!clever_check_args("s*")) {
		return;
	}

	FFIData* handler = clever_get_this(FFIData*);

	const CString* func = args.at(0)->getStr();
	FFIType rt = static_cast<FFIType>(args.at(1)->getInt());
	size_t n_args = args.size() - 2;

#ifndef CLEVER_WIN32
	ffi_call_func pf = _ffi_get_pf(handler->m_lib_handler,
								   func);
	if (pf == 0) {
		clever_throw("function `%S' don't exist!", func);
		return;
	}
#endif

	_ffi_call(result, pf, n_args, rt, args, 2);
}

// FFILib.load()
CLEVER_METHOD(FFI::load)
{
	FFIData* data = clever_get_this(FFIData*);

	if (!clever_check_args("s")) {
		return;
	}

	result->setBool(_load_lib(data, args.at(0)->getStr()));
}

// FFILib.unload()
CLEVER_METHOD(FFI::unload)
{
	FFIData* data = clever_get_this(FFIData*);

	if (data->m_lib_handler != NULL) {
		dlclose(data->m_lib_handler);
		data->m_lib_handler = NULL;
	}
}

// FFI type initialization
CLEVER_TYPE_INIT(FFI::init)
{
	setConstructor((MethodPtr) &FFI::ctor);

	addMethod(new Function("callThisFunction", (MethodPtr)&FFI::callThisFunction));
	addMethod(new Function("call",   (MethodPtr)&FFI::call));
	addMethod(new Function("exec",   (MethodPtr)&FFI::exec))->setStatic();
	addMethod(new Function("load",   (MethodPtr)&FFI::load));
	addMethod(new Function("unload", (MethodPtr)&FFI::unload));

	m_call_handler = new Value;
	m_call_handler->setObj(CLEVER_FUNC_TYPE,
		new Function("callThisFunction", (MethodPtr)&FFI::callThisFunction));
}

// FFI module initialization
CLEVER_MODULE_INIT(FFIModule)
{
	addType(new FFI);
	addType(new FFIStruct);
	addType(new FFITypes);
}

}}} // clever::modules::std
