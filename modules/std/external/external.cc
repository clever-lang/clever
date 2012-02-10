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


#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <map>
#include <string>
#include <ffi.h>

#ifdef _WIN32
	
	#include <windows.h>
	
#else
	
	#include <dlfcn.h>
	
#endif

#include "modules/std/external/external.h"
#include "types/nativetypes.h"

using std::string;
using std::map;
using std::vector;

namespace clever { namespace packages { namespace std {

namespace external {

	
extern "C"{
	
	typedef void (* ffi_call_func)();
	
};

#ifdef _WIN32

#else
	map< string, void*> ext_mod_map;

#endif

/**
 * call_ext_func(..., str function_name, str library_name)
 * Returns call an external function
 */

ffi_type* find_ffi_type(const char* tn){
	
	if ( tn[0] == 'i' ) {
		return &ffi_type_sint32;
	} else if ( tn[0] == 'd' ) {
		return &ffi_type_double;
	} else if ( tn[0] == 'b' ) {
		return &ffi_type_schar;
	} else if ( tn[0] == 's' ) {
		return &ffi_type_pointer;
	} else if ( tn[0] == 'c' ) {
		return &ffi_type_schar;
	} else if ( tn[0] == 'v' ) {
		return &ffi_type_void;
	}
	
	return NULL;
}


static CLEVER_FUNCTION(call_ext_func) {
	
	size_t size = CLEVER_NUM_ARGS();
	size_t n_args = size - 3;
	
	::std::string lib = CLEVER_ARG_STR(size-3);
	::std::string rt = CLEVER_ARG_STR(size-2);
	::std::string func = CLEVER_ARG_STR(size-1);
	
#ifdef _WIN32
#else
	
	void* fpf;
	ffi_call_func pf;
	
	map<string, void*>::iterator it = ext_mod_map.find(lib), end = ext_mod_map.end();
		
	if ( it == end ) {
		
		string libname=string("./")+lib+".so";
		void* m=ext_mod_map[lib]=dlopen(libname.c_str(), 1);
		
		if ( m == NULL ) {
			
			CLEVER_RETURN_BOOL(false);
			return;
			
		}
		
		it=ext_mod_map.find(lib);
		
	}
	
	fpf = dlsym(it->second, func.c_str());
		
	if ( fpf == NULL ) {
			
		CLEVER_RETURN_BOOL(false);
		return;
			
	}
		
	pf=reinterpret_cast<ffi_call_func>(fpf);
	
#endif

	
	ffi_cif cif;
	
	ffi_type* ffi_rt = find_ffi_type(rt.c_str());
	ffi_type** ffi_args = (ffi_type**) malloc (n_args*sizeof(ffi_type*));
	
	void** ffi_values = (void**) malloc (n_args*sizeof(void*));
	
	for(size_t i=0;i<n_args;i++){
		
		if ( CLEVER_ARG_IS_INT(i) ) {
			
			ffi_args[i] = &ffi_type_sint32;
			
			int* vi= (int*) malloc (sizeof(int));
			
			*vi = CLEVER_ARG_INT(i);
			
			ffi_values[i] =  vi;
			
		}else if ( CLEVER_ARG_IS_BOOL(i) ) {
			
			ffi_args[i] = find_ffi_type("b");
			
			char* b=(char*) malloc (sizeof(char));
			
			*b = CLEVER_ARG_BOOL(i);
			
			ffi_values[i] = b;
			
		}else if ( CLEVER_ARG_IS_STR(i) ) {
			
			const char* st = CLEVER_ARG_STR(i).c_str();
			
			char** s= (char**) malloc (sizeof(char*)); 
			*s = (char*) malloc (sizeof(char)* (strlen(st)+1));
			
			strcpy(*s,st);
			(*s)[strlen(st)]='\0';
			
			ffi_args[i] = find_ffi_type("s");
			
			ffi_values[i] =  s;
			
			
		}else if ( CLEVER_ARG_IS_BYTE(i) ) {
			
			ffi_args[i] = find_ffi_type("c");
			
			char* b = (char*) malloc (sizeof(char));
			*b = CLEVER_ARG_BYTE(i);
			
			ffi_values[i] = b;
			
		}else if ( CLEVER_ARG_IS_DOUBLE(i) ) {
			
			ffi_args[i] = &ffi_type_double;
			
			double* d = (double*)malloc(sizeof(double));
			*d = CLEVER_ARG_DOUBLE(i);
			ffi_values[i] = d;
			
		}else if ( CLEVER_ARG_IS_USER(i) ) {
			//::std::cout<<"Arg "<<i<<" is Bool:";
			//::std::cout<<CLEVER_ARG_BOOL(i)<<::std::endl;
		}else if ( CLEVER_ARG_IS_VECTOR(i) ) {
			//::std::cout<<"Arg "<<i<<" is Bool:";
			//::std::cout<<CLEVER_ARG_BOOL(i)<<::std::endl;
		}
	}
	
	if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, ffi_rt, ffi_args) != FFI_OK) {
		 CLEVER_RETURN_BOOL(false);
	}
	 
	
#ifdef _WIN32
#else	

	if ( rt[0] == 'i' ) {
		int vi;
		
		ffi_call(&cif, pf, &vi, ffi_values);
		
		CLEVER_RETURN_INT(vi);
	} else if ( rt[0] == 'd' ) {
		double vd;
		
		ffi_call(&cif, pf, &vd, ffi_values);
		
		CLEVER_RETURN_DOUBLE(vd);
	} else if ( rt[0] == 'b' ) {
		bool vb;
		
		ffi_call(&cif, pf, &vb, ffi_values);
		
		CLEVER_RETURN_BOOL(vb);
	} else if ( rt[0] == 's' ) {
		char* vs[1];
		vs[0]=0;
		
		ffi_call(&cif, pf, &vs, ffi_values);
		
		//printf("ret=%s<><>\n",*vs);
		
		//string s(*vs);
		//::std::cout<<string(*vs)<<::std::endl;
		
		CLEVER_RETURN_STR(CSTRING(*vs));
	} else if ( rt[0] == 'c' ) {
		char vc;
		
		ffi_call(&cif, pf, &vc, ffi_values);
		
		CLEVER_RETURN_BYTE(vc);
	}else CLEVER_RETURN_BOOL(true);
	
#endif

	for(size_t i=0;i<n_args;i++){
		
		if ( CLEVER_ARG_IS_INT(i) ) {
			free((int*)ffi_values[i]);
		}else if ( CLEVER_ARG_IS_BOOL(i) ) {
			free((char*)ffi_values[i]);
		}else if ( CLEVER_ARG_IS_STR(i) ) {
			char** v=(char**)ffi_values[i];
			free(v[0]);
			free(v);
		}else if ( CLEVER_ARG_IS_BYTE(i) ) {
			free((char*)ffi_values[i]);
		}else if ( CLEVER_ARG_IS_DOUBLE(i) ) {
			free((double*)ffi_values[i]);
		}else if ( CLEVER_ARG_IS_USER(i) ) {
			//::std::cout<<"Arg "<<i<<" is Bool:";
			//::std::cout<<CLEVER_ARG_BOOL(i)<<::std::endl;
		}else if ( CLEVER_ARG_IS_VECTOR(i) ) {
			//::std::cout<<"Arg "<<i<<" is Bool:";
			//::std::cout<<CLEVER_ARG_BOOL(i)<<::std::endl;
		}
	}
	
	free(ffi_args);
	free(ffi_values);

}

}

/**
 * Load module data
 */
void External::init() {
	
	addFunction(new Function("call_ext_func",	&CLEVER_NS_FNAME(external, call_ext_func), CLEVER_BOOL))
		->setVariadic()
		->setMinNumArgs(2);
}

External::~External(){
	
	map< string, void*>::iterator it = external::ext_mod_map.begin(), end = external::ext_mod_map.end();
	
	while ( it != end) {
		if (it->second != NULL) dlclose(it->second);
		++it;
	}
	
}


}}} // clever::packages::std
