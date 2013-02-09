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
 *
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
#include "core/value.h"
#include "modules/std/concurrent/module.h"
#include "modules/std/core/function.h"
#include "types/type.h"

#include "core/value.h"
#include "modules/std/ffi/ffi.h"

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

static ffi_type* _find_ffi_type(const char* tn) {
	switch (tn[0]) {
		case 'i': return &ffi_type_sint32;
		case 'd': return &ffi_type_double;
		case 'b': return &ffi_type_schar;
		case 's': return &ffi_type_pointer;
		case 'c': return &ffi_type_schar;
		case 'v': return &ffi_type_void;
		case 'p': return &ffi_type_pointer;
	}
	return NULL;
}

bool _load_lib(FFIData* h, const CString* libname)
{
	if (h->m_lib_handler != NULL) {
		dlclose(h->m_lib_handler);
	}

	h->m_lib_name = *libname;
	h->m_lib_name += CLEVER_DYLIB_EXT;
	h->m_lib_handler = dlopen(h->m_lib_name.c_str(), RTLD_LAZY);

	if (h->m_lib_handler == NULL) {
		return false;
	}

	return true;
}



void FFI::dump(const void* data) const
{
	dump(data, ::std::cout);
}

void FFI::dump(const void* data, ::std::ostream& out) const
{
	ValueObject* dvalue =
		static_cast<ValueObject*>(const_cast<void*>(data));
	if (dvalue) {

	}
}

void* FFI::allocData(CLEVER_TYPE_CTOR_ARGS) const
{
	FFIData* data = new FFIData();

	if (args->size() == 1) {
		Value* v = args->at(0);
		if (v->isStr()) {
			if (!_load_lib(data, v->getStr())) {
				clever_error("Failed to open %s!", v->getStr()->c_str());
			}
		} else {
			clever_error("Argument 1 must to be a string!");
		}
	} else if (args->size() > 1) {
		clever_error("FFI must to have one or zero arguments!");
	}

	return data;
}

void FFI::deallocData(void* value)
{
	FFIData* data = static_cast<FFIData*>(value);
	if (data->m_lib_handler) {
		dlclose(data->m_lib_handler);
	}
}

CLEVER_METHOD(FFI::ctor)
{
	if (!clever_check_args("s")) {
		return;
	}

	result->setObj(this, allocData(&args));
}

CLEVER_METHOD(FFI::call)
{
	if (!clever_check_args("ss*")) {
		return;
	}

	FFIData* handler = CLEVER_GET_OBJECT(FFIData*, CLEVER_THIS());

	size_t size = args.size();
	size_t n_args = size - 2;

	const CString* func = args.at(0)->getStr();
	const CString* rt = args.at(1)->getStr();

#ifndef CLEVER_WIN32
	void* fpf;
	ffi_call_func pf;

	fpf = dlsym(handler->m_lib_handler, func->c_str());
	if (fpf == NULL) {
		clever_error("FFI::call: function %s doesn't exist!", func->c_str());
		result->setBool(false);
		return;
	}

	pf = reinterpret_cast<ffi_call_func>(fpf);
#endif
	ffi_cif cif;

	ffi_type* ffi_rt = _find_ffi_type(rt->c_str());
	ffi_type** ffi_args = (ffi_type**) malloc(n_args*sizeof(ffi_type*));

	void** ffi_values = (void**) malloc(n_args*sizeof(void*));

	for (size_t i = 2; i < size; ++i) {
		Value* v = args.at(i);

		if (v->isInt()) {
			ffi_args[i - 2] = &ffi_type_sint32;

			int* vi= (int*) malloc(sizeof(int));

			*vi = v->getInt();

			ffi_values[i - 2] =  vi;
		} else if (v->isBool()) {
			ffi_args[i - 2] = _find_ffi_type("b");

			char* b=(char*) malloc (sizeof(char));

			*b = v->getBool();

			ffi_values[i - 2] = b;
		} else if (v->isStr()) {
			const char* st = v->getStr()->c_str();

			char** s= (char**) malloc (sizeof(char*));
			*s = (char*) malloc (sizeof(char)* (strlen(st)+1));

			strcpy(*s,st);
			(*s)[strlen(st)]='\0';

			ffi_args[i - 2] = _find_ffi_type("s");

			ffi_values[i - 2] =  s;
		}  else if (v->isDouble()) {
			ffi_args[i - 2] = &ffi_type_double;

			double* d = (double*)malloc(sizeof(double));

			*d = v->getDouble();

			ffi_values[i - 2] = d;
		} else {
			ffi_args[i - 2] = _find_ffi_type("p");

			//FFIObjectValue* obj = static_cast<FFIObjectValue*>(CLEVER_ARG_DATA_VALUE(i));

			//ffi_values[i] = &(static_cast<FFIObjectValue*>(CLEVER_ARG_DATA_VALUE(i))->pointer);
		}
	}

	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, ffi_rt, ffi_args) != FFI_OK) {
		 result->setBool(false);
		 return;
	}


#ifndef CLEVER_WIN32

	if (rt->at(0) == 'i') {
		int vi;

		ffi_call(&cif, pf, &vi, ffi_values);

		result->setInt(vi);
	} else if (rt->at(0) == 'd') {
		double vd;

		ffi_call(&cif, pf, &vd, ffi_values);

		result->setDouble(vd);
	} else if (rt->at(0) == 'b') {
		bool vb;

		ffi_call(&cif, pf, &vb, ffi_values);

		result->setBool(vb);
	} else if (rt->at(0) == 's') {
		char* vs[1];

		ffi_call(&cif, pf, &vs, ffi_values);

		result->setStr(CSTRING(*vs));

		free(vs[0]);
	} else if (rt->at(0) == 'c') {
		char vc;

		ffi_call(&cif, pf, &vc, ffi_values);

		result->setBool(vc);
	} else if (rt->at(0) == 'v') {

		ffi_call(&cif, pf, NULL, ffi_values);

		result->setBool(true);
	} else if (rt->at(0) == 'p') {
		//FFIObjectValue* x = static_cast<FFIObjectValue*> (retval->getDataValue());

		//if ( x == NULL ) x = new FFIObjectValue();

		//ffi_call(&cif, pf, &(x->pointer), ffi_values);

		//CLEVER_RETURN_DATA_VALUE(x);
	} else {
		result->setBool(true);
	}

#endif

	for (size_t i = 0; i < n_args; ++i) {
		Value* v = args.at(i + 2);

		if (v->isInt()) {
			free((int*)ffi_values[i]);
		} else if (v->isBool()) {
			free((char*)ffi_values[i]);
		} else if (v->isStr()) {
			char** v=(char**)ffi_values[i];
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

CLEVER_METHOD(FFI::load)
{
	FFIData* data = CLEVER_GET_OBJECT(FFIData*, CLEVER_THIS());

	if (!clever_check_args("s")) {
		return;
	}

	result->setBool(_load_lib(data, args.at(0)->getStr()));
}

CLEVER_METHOD(FFI::unload)
{
	FFIData* data = CLEVER_GET_OBJECT(FFIData*, CLEVER_THIS());

	if (data->m_lib_handler != NULL) {
		dlclose(data->m_lib_handler);
		data->m_lib_handler = NULL;
	}
}

/**
 * Load module data
 */
CLEVER_TYPE_INIT(FFI::init)
{
	Function* ctor = new Function("FFILib", (MethodPtr) &FFI::ctor);

	setConstructor(ctor);

	addMethod(ctor);

	addMethod(new Function("call",			(MethodPtr)&FFI::call));
	addMethod(new Function("load",			(MethodPtr)&FFI::load));
	addMethod(new Function("unload",		(MethodPtr)&FFI::unload));
}

CLEVER_MODULE_INIT(FFIModule)
{
	addType(CSTRING("FFILib"),     new FFI);
}


}}} // clever::packages::std
