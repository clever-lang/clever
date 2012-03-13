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

#include "compiler/value.h"
#include "modules/std/net/net.h"
#include "modules/std/net/tcpsocket.h"
#include "modules/std/rpc/rpc.h"
#include "modules/std/rpc/rpcclass.h"
#include "modules/std/rpc/rpcobject.h"
#include "compiler/compiler.h"
#include "compiler/cstring.h"
#include "types/nativetypes.h"
#include <cstdio>

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

namespace clever { namespace packages { namespace std { namespace rpc {



extern "C" {
	typedef void (*ffi_call_func)();
}

#ifndef CLEVER_WIN32
	ExtMap ext_mod_map;
	FuncMap ext_func_map;
	FuncMap ext_ret_map;
#endif

static ffi_type* _find_rpc_type(const char* tn) {
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

bool send(int m_socket, const char *buffer, int length) {
	int sent = 0;


	// Loop the send() because it might happen to not send all data once.
	do {
		int res = ::send(m_socket, (&buffer[sent]), (length - sent), 0);

		if (res >= 0) {
			sent += res;
		} else {
			return false;
		}
	} while (sent < length);

	return true;
}

class secure_print{

public:

	
	secure_print(){
		pthread_mutex_init (&mut,&mattr);
	}

	void printStr(const char* str){
		pthread_mutex_lock (&mut);
		fprintf(stderr,"String: <%s>\n",str);
		pthread_mutex_unlock (&mut);
	}

	void printMsg(const char* str){
		pthread_mutex_lock (&mut);
		fprintf(stderr,"\t%s\n",str);
		pthread_mutex_unlock (&mut);
	}

	void printInt(int v){	
		pthread_mutex_lock (&mut);
		fprintf(stderr,"Integer: <%d>\n",v);
		pthread_mutex_unlock (&mut);
	} 


private:

	int sc;

	pthread_mutex_t mut;
	pthread_mutexattr_t mattr;

};

secure_print printer;

void* process(void* args) {
	int client_socket_id; 
	
	int type_call=0;
	int len_fname=0;
	int n_args=0;
	char f_rt;
	int size_args=0;
	char* fname;
	char* buffer;
	int ibuffer;

	void* fpf;
	ffi_call_func pf;

	ffi_cif cif;

	ffi_type* ffi_rt;
	ffi_type** ffi_args;

	void** ffi_values;

	client_socket_id = * (reinterpret_cast<int*>(args));
	free(args);

	type_call=len_fname=n_args=size_args=0;
	f_rt = 'v';

	while (true) {
		
		/* First, read the length of the text message from the socket. If
		read returns zero, the client closed the connection. */
		
		if (recv (client_socket_id, &type_call, sizeof (type_call), 0) == 0){
			close (client_socket_id);
			return NULL;
		}

		switch (type_call) {

			case 0x666:
				printer.printMsg("Server died...\n");
				while(recv (client_socket_id, &type_call, sizeof (type_call), 0)!=0);
				close (client_socket_id);
				return NULL;
			break;

			case 0xE1:
				recv (client_socket_id, &len_fname, sizeof (len_fname), 0);
				printer.printInt(len_fname);
			break;

			case 0xEC:
				recv (client_socket_id, &len_fname, sizeof (len_fname), 0);
				
				fname = (char*) malloc ((len_fname+1)*sizeof(char));
				fname[len_fname]='\0';

				recv (client_socket_id, fname, len_fname, 0);

				printer.printStr(fname);
				free(fname);
			break;

			/* function call*/
			case 0xFC: 
				recv (client_socket_id, &len_fname, sizeof (len_fname), 0);

				
				fname = (char*) malloc ((len_fname+1)*sizeof(char));
				fname[len_fname]='\0';

				recv (client_socket_id, fname, len_fname, 0);

				

				fpf = dlsym(ext_mod_map[ext_func_map[fname]], fname);

				if (fpf == NULL) {
					clever_fatal("[RPC] function `%s' not found at `%s'!",
						fname, ext_func_map[fname].c_str());
					free (fname);
					close (client_socket_id);
					return NULL;
				}

				f_rt = ext_ret_map[fname].c_str()[0];
				ffi_rt = _find_rpc_type(&f_rt);

				pf = reinterpret_cast<ffi_call_func>(fpf);

				recv (client_socket_id, &n_args, sizeof(n_args), 0);

				if(n_args>0){
					ffi_args = (ffi_type**) malloc(n_args*sizeof(ffi_type*));
					ffi_values = (void**) malloc(n_args*sizeof(void*));

					recv (client_socket_id, &size_args, sizeof(size_args), 0);

					buffer = (char*) malloc(size_args*sizeof(char));

					recv (client_socket_id, buffer, size_args, 0);
				}

				ibuffer=0;

				for( int i = 0; i < n_args; ++i){
					char type_arg;
					type_arg = buffer[ibuffer]; 
					ibuffer+=sizeof(char);

					ffi_args[i] = _find_rpc_type(&type_arg);

					switch(type_arg) {
						case 'i': 
							{
								int* pi = (int*)malloc(sizeof(int));
								*pi = * ((int*)(buffer+ibuffer));
								ibuffer+=sizeof(int);

								ffi_values[i] = pi;
							}
						break;

						case 'd': 
							{
								double* pd = (double*)malloc(sizeof(double));
								*pd = * ((double*)(buffer+ibuffer));
								ibuffer+=sizeof(double);

								ffi_values[i] = pd;
							}
						break;

						case 'c': case 'b':
							{
								char* pc = (char*)malloc(sizeof(char));
								*pc = * ((char*)(buffer+ibuffer));
								ibuffer+=sizeof(char);

								ffi_values[i] = pc;
							}
						break;

						case 'p': case 's':
							{
								int len_s;
								len_s = * ((int*)(buffer+ibuffer));
								ibuffer+=sizeof(int);

								char** s = (char**)malloc(sizeof(char*));

								if(type_arg == 'p') {
									*s = (char*)malloc(len_s*sizeof(char));
								} else {
									*s = (char*)malloc((1+len_s)*sizeof(char));
									(*s)[len_s]='\0';
								}

								memcpy((*s),buffer+ibuffer,len_s);
								ibuffer+=len_s;

								ffi_values[i] = s;
							}
						break;

					}
				}

				if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, n_args, ffi_rt, ffi_args) != FFI_OK) {
		 			clever_fatal("[RPC] failed to call function `%s'!",
						fname);
					free (fname);

					if(n_args>0){
						free (buffer);
						free(ffi_values);
						free(ffi_args);
					}

					return NULL;
				}

				/*call function*/
				int if_rt=f_rt;
				
				switch ( f_rt ) {
						case 'i': 
							{
								int vi;
								ffi_call(&cif, pf, &vi, ffi_values);

								send(client_socket_id,(char*)(&if_rt),sizeof(int));
								send(client_socket_id,(char*)(&vi),sizeof(int));
							}
						break;

						case 'd': 
							{
								double vd;
								ffi_call(&cif, pf, &vd, ffi_values);

								send(client_socket_id,(char*)(&if_rt),sizeof(int));
								send(client_socket_id,(char*)(&vd),sizeof(double));
							}
						break;

						case 'c': case 'b':
							{
								char vc;
								ffi_call(&cif, pf, &vc, ffi_values);

								send(client_socket_id,(char*)(&if_rt),sizeof(int));
								send(client_socket_id,(char*)(&vc),sizeof(double));
							}
						break;

						case 'p': case 's':
							{
								char* vs[1];
								int size_vs;

								ffi_call(&cif, pf, &vs, ffi_values);

								 size_vs = * ((int*) vs[0]);

								send(client_socket_id,(char*)(&if_rt),sizeof(int));
								send(client_socket_id,(char*)(&size_vs),sizeof(int));
								send(client_socket_id,(char*)(vs[0]+sizeof(int)), size_vs);

								free(vs[0]);
							}
						break;

						case 'v':
							{
								ffi_call(&cif, pf, NULL, ffi_values);

								send(client_socket_id,(char*)(&if_rt),sizeof(int));
							}
						break;
				}

				/*free memory*/

				ibuffer = 0;
				for( int i = 0; i < n_args; ++i){
					char type_arg;
					type_arg = buffer[ibuffer]; ibuffer+=sizeof(char);

					ffi_args[i] = _find_rpc_type(&type_arg);

					if(type_arg == 's' || type_arg == 'p'){
						free(* ((char**)ffi_values[i]));
					}

					free(ffi_values[i]);

					switch(type_arg) {
						case 'i': ibuffer+=sizeof(int); break;
						case 'd': ibuffer+=sizeof(double); break;
						case 'c': case 'b': ibuffer+=sizeof(char); break;
						case 'p': case 's':
							{
								int len_s;
								len_s = * ((int*)(buffer+ibuffer));
								ibuffer+=sizeof(int);
								ibuffer+=len_s;
							}
						break;

					}
				}

				if(n_args>0){
					free(ffi_args);
					free(ffi_values);
					free(buffer);
				}

				free(fname);

			break;
		}
	}

	close (client_socket_id);
	return NULL;
}

RPCValue::~RPCValue() { 
	if(socket) delete socket; 

	ExtMap::const_iterator it = ext_mod_map.begin(),
		end = ext_mod_map.end();

	while (it != end) {
		if (it->second != NULL) {
			dlclose(it->second);
		}
		++it;
	}
}

void RPCValue::addFunction(const char* libname, const char* funcname, const char* rettype){
	ext_func_map[funcname] = libname;
	ext_ret_map[funcname] = rettype;
}

void RPCValue::loadLibrary(const char* libname) {
	void* m = dlopen(libname, RTLD_LAZY);
	ext_mod_map[libname] = m;
	if (m == NULL) {
		clever_fatal("[RPC] Shared library `%s' not loaded!\n Error: \n %s",
			libname, dlerror());
		return;
	}

}


void RPCValue::createConnection(int client_socket_id) {
	//Create thread to manage connection
	pthread_attr_t attr;
	pthread_t thread;

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	int * cp = (int*)malloc(sizeof(int)); 
	*cp = client_socket_id;

	pthread_create (&thread, &attr, &process, (void*)(cp));

	pthread_attr_destroy (&attr);

}


void RPCValue::createServer(int port, int connections) {
	sockaddr_in sa;

	memset(&sa, 0, sizeof(sa));

	sa.sin_family = PF_INET;
	sa.sin_port = ::htons(port);
	int m_socket = ::socket(AF_INET, SOCK_STREAM, 0);

	bind(m_socket, (sockaddr *)&sa, sizeof(sockaddr_in));
	
	listen(m_socket, connections);

	int kill_me=0;

	do {
		struct sockaddr client_name;
		socklen_t client_name_len;
		int client_socket_id;
		client_name_len=0;

		sleep(0.5);

		memset(&client_name, 0, sizeof(client_name));
		client_socket_id = accept (m_socket, &client_name, &client_name_len);
		
		createConnection(client_socket_id);
		
	} while (!kill_me);

	close (m_socket);

}

void RPCValue::createClient(const char* host, const int port, const int time) {
	socket = new CSocket;

	socket->setHost(host);
	socket->setPort(port);
	socket->setTimeout(time);

	int t=0;

	fprintf(stderr,"Connecting.");
	while (t<time) {
		if (socket->connect()) {
			fprintf(stderr,"\n");
			return;
		}
		fprintf(stderr,".");
		sleep(1);
	}
	clever_fatal("[RPC] Failed to connect with RPC server!");
}

void RPCValue::sendString(const char* s, int len) {
	int id=0xEC;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&len),sizeof(int));
	socket->send(s,len);
}

void RPCValue::sendInteger(int v) {
	int id=0xE1;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&v),sizeof(int));
}

void RPCValue::sendKill() {
	int id=0x666;

	socket->send((char*)(&id),sizeof(int));
}

void RPCValue::sendFunctionCall(const char* fname, const char* args, int len_fname, int n_args, int len_args){
	int id=0xFC;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&len_fname),sizeof(int));
	socket->send(fname,len_fname);
	socket->send((char*)(&n_args),sizeof(int));

	if(n_args>0){
		socket->send((char*)(&len_args),sizeof(int));
		socket->send(args,len_args);
	}

}

RPCObjectValue* RPCValue::receiveObject(){
	RPCObjectValue* obj =  new RPCObjectValue;

	int* type = (int*)malloc(sizeof(int));
	int len=sizeof(int), len_s;
	int* vi;
	char* vc, *buffer;
	double* vd;

	socket->receive((char*)type,len);

	obj->type = *type;

	obj->pointer = 0;

	switch(*type){
		case 'i':
			{
				vi = (int*) malloc(sizeof(int));
				socket->receive((char*)vi,sizeof(int));
				obj->pointer=vi;
			}
		break;

		case 'd':
			{
				vd = (double*) malloc(sizeof(double));
				socket->receive((char*)vd,sizeof(double));
				obj->pointer=vd;
			}
		break;

		case 'c': case 'b':
			{
				vc = (char*) malloc(sizeof(char));
				socket->receive((char*)vc,sizeof(char));
				obj->pointer=vc;
			}
		break;

		case 'p': case 's':
			{
				socket->receive((char*)(&len_s),sizeof(int));

				buffer = (char*) malloc(len_s*sizeof(char));

				socket->receive(buffer,len_s);

				obj->pointer=buffer;
			}
		break;
	}

	free(type);

	return obj;
}

}}}} // clever::packages::std::rpc


