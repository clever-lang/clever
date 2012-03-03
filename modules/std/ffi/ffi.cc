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

#include "modules/std/ffi/ffiobject.h"
#include "modules/std/ffi/ffi.h"
#include "types/nativetypes.h"

namespace clever { namespace packages { namespace std { namespace ffi {

extern "C" {
	typedef void (*ffi_call_func)();
}

#ifndef CLEVER_WIN32
	ExtMap ext_mod_map;
#endif

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

/**
 * call_ext_func(..., str function_name, str library_name)
 * Returns call an external function
 */
static CLEVER_FUNCTION(call_ext_func) {
	size_t size = CLEVER_NUM_ARGS();
	size_t n_args = size - 3;

	::std::string lib = CLEVER_ARG_STR(size-3);
	::std::string rt = CLEVER_ARG_STR(size-2);
	::std::string func = CLEVER_ARG_STR(size-1);


#ifndef CLEVER_WIN32
	void* fpf;
	ffi_call_func pf;

	ExtMap::iterator it = ext_mod_map.find(lib),
		end = ext_mod_map.end();

	if (it == end) {
		::std::string libname = lib + CLEVER_DYLIB_EXT;
		void* m = ext_mod_map[lib] = dlopen(libname.c_str(), RTLD_LAZY);

		if (m == NULL) {
			clever_fatal("[FFI] Shared library`%S' not loaded!\n Error: \n %s",
				&CLEVER_ARG_STR(size-3),dlerror());
			CLEVER_RETURN_BOOL(false);
			return;
		}
		it=ext_mod_map.find(lib);
	}

	fpf = dlsym(it->second, func.c_str());

	if (fpf == NULL) {
		clever_fatal("[FFI] function`%S' not found at `%S'!",
			&CLEVER_ARG_STR(size-1), &CLEVER_ARG_STR(size-3));
		CLEVER_RETURN_BOOL(false);
		return;
	}

	pf = reinterpret_cast<ffi_call_func>(fpf);
#endif

	ffi_cif cif;

	ffi_type* ffi_rt = _find_ffi_type(rt.c_str());
	ffi_type** ffi_args = (ffi_type**) malloc(n_args*sizeof(ffi_type*));

	void** ffi_values = (void**) malloc(n_args*sizeof(void*));

	for (size_t i = 0; i < n_args; ++i) {
		if (CLEVER_ARG_IS_INT(i)) {
			ffi_args[i] = &ffi_type_sint32;

			int* vi= (int*) malloc(sizeof(int));

			*vi = CLEVER_ARG_INT(i);

			ffi_values[i] =  vi;
		} else if (CLEVER_ARG_IS_BOOL(i)) {
			ffi_args[i] = _find_ffi_type("b");

			char* b=(char*) malloc (sizeof(char));

			*b = CLEVER_ARG_BOOL(i);

			ffi_values[i] = b;
		} else if (CLEVER_ARG_IS_STR(i)) {
			const char* st = CLEVER_ARG_STR(i).c_str();

			char** s= (char**) malloc (sizeof(char*));
			*s = (char*) malloc (sizeof(char)* (strlen(st)+1));

			strcpy(*s,st);
			(*s)[strlen(st)]='\0';

			ffi_args[i] = _find_ffi_type("s");

			ffi_values[i] =  s;
		} else if (CLEVER_ARG_IS_BYTE(i)) {
			ffi_args[i] = _find_ffi_type("c");

			char* b = (char*) malloc (sizeof(char));
			*b = CLEVER_ARG_BYTE(i);

			ffi_values[i] = b;
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			ffi_args[i] = &ffi_type_double;

			double* d = (double*)malloc(sizeof(double));
			*d = CLEVER_ARG_DOUBLE(i);
			ffi_values[i] = d;
		} else if ( CLEVER_ARG_IS_USER(i) ) {
			ffi_args[i] = _find_ffi_type("p");

			//FFIObjectValue* obj = static_cast<FFIObjectValue*>(CLEVER_ARG_DATA_VALUE(i));

			ffi_values[i] = &(static_cast<FFIObjectValue*>(CLEVER_ARG_DATA_VALUE(i))->pointer);
		}
	}

	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, ffi_rt, ffi_args) != FFI_OK) {
		 CLEVER_RETURN_BOOL(false);
	}

#ifndef CLEVER_WIN32

	if (rt[0] == 'i') {
		int vi;

		ffi_call(&cif, pf, &vi, ffi_values);

		CLEVER_RETURN_INT(vi);
	} else if (rt[0] == 'd') {
		double vd;

		ffi_call(&cif, pf, &vd, ffi_values);

		CLEVER_RETURN_DOUBLE(vd);
	} else if (rt[0] == 'b') {
		bool vb;

		ffi_call(&cif, pf, &vb, ffi_values);

		CLEVER_RETURN_BOOL(vb);
	} else if (rt[0] == 's') {
		char* vs[1];

		ffi_call(&cif, pf, &vs, ffi_values);

		CLEVER_RETURN_STR(CSTRING(*vs));

		free(vs[0]);
	} else if (rt[0] == 'c') {
		char vc;

		ffi_call(&cif, pf, &vc, ffi_values);

		CLEVER_RETURN_BYTE(vc);
	} else if (rt[0] == 'v') {

		ffi_call(&cif, pf, NULL, ffi_values);

		CLEVER_RETURN_BOOL(true);
	} else if (rt[0] == 'p') {
		FFIObjectValue* x = static_cast<FFIObjectValue*> (retval->getDataValue());

		if ( x == NULL ) x = new FFIObjectValue();

		ffi_call(&cif, pf, &(x->pointer), ffi_values);

		CLEVER_RETURN_DATA_VALUE(x);
	} else {
		CLEVER_RETURN_BOOL(true);
	}

#endif

	for (size_t i = 0; i < n_args; ++i) {
		if (CLEVER_ARG_IS_INT(i)) {
			free((int*)ffi_values[i]);
		} else if (CLEVER_ARG_IS_BOOL(i)) {
			free((char*)ffi_values[i]);
		} else if (CLEVER_ARG_IS_STR(i)) {
			char** v=(char**)ffi_values[i];
			free(v[0]);
			free(v);
		} else if (CLEVER_ARG_IS_BYTE(i)) {
			free((char*)ffi_values[i]);
		} else if (CLEVER_ARG_IS_DOUBLE(i)) {
			free((double*)ffi_values[i]);
		} else if (CLEVER_ARG_IS_USER(i)) {
		}
	}

	free(ffi_args);
	free(ffi_values);
}

} // ffi

/**
 * Load module data
 */
void FFI::init() {
	Class* FFIObject = new ffi::FFIObject();

	addClass(FFIObject);

	addFunction(new Function("__call_ext_func__",
		&CLEVER_NS_FNAME(ffi, call_ext_func), CLEVER_BOOL))
		->setVariadic()
		->setMinNumArgs(2);
}

FFI::~FFI() {
	ExtMap::const_iterator it = ffi::ext_mod_map.begin(),
		end = ffi::ext_mod_map.end();

	while (it != end) {
		if (it->second != NULL) {
			dlclose(it->second);
		}
		++it;
	}
}

}}} // clever::packages::std
