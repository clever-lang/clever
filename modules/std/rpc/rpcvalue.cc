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
#include <map>

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

bool send(int m_socket, const char *buffer, int length);

ffi_type* _find_rpc_type(const char* tn) {
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

class Mutex {

public:

	
	Mutex() {}

	void init() {
		pthread_mutex_init (&mut,&mattr);
	}

	void lock() {
		pthread_mutex_lock (&mut);
	}

	void unlock() {
		pthread_mutex_unlock (&mut);
	}


private:
	pthread_mutex_t mut;
	pthread_mutexattr_t mattr;
};

Mutex g_mutex, send_mutex, time_mutex;

class WaitProcess {

public:

	
	WaitProcess(){
		np=0;
		mut.init();
	}

	void init() {
		np=0;
		mut.init();
	}

	void inc(){
		mut.lock();
		np++;
		mut.unlock();
	}

	void dec(){
		mut.lock();
		np--;
		mut.unlock();
	}

	void wait(){
		while(true) {

			sleep(1);
			
			mut.lock();
			int p=np;
			mut.unlock();
			if(p==0) return;
		}
	} 


private:

	int np;

	Mutex mut;
};

class SecurePrint{

public:

	
	SecurePrint(){
		mut.init();
	}

	void printStr(const char* str){
		mut.lock();
		fprintf(stderr,"String: <%s>\n",str);
		mut.unlock();
	}

	void printMsg(const char* str){
		mut.lock();
		fprintf(stderr,"\t%s\n",str);
		mut.unlock();
	}

	void printInt(int v){	
		mut.lock();
		fprintf(stderr,"Integer: <%d>\n",v);
		mut.unlock();
	} 


private:

	int sc;

	Mutex mut;
};

struct RPCData{

	RPCData(int client_socket_id=0, int type=0, int size=0, char* buffer=0):
		client_socket_id(client_socket_id),type(type),size(size),buffer(buffer) {}

	int client_socket_id;
	int type;
	int size;
	char* buffer;
};

class RetMap{

public:

	
	RetMap(){
		mut.init();
	}

	void insert(int client_socket_id, int id, int type, int size, char* b){
		mut.lock();
		ret_map[client_socket_id][id]= RPCData(client_socket_id,type,size,b);
		mut.unlock();
	}

	void sendData(int client_socket_id, int id, double timeout=0.1) {
		RPCData r;
		::std::map<int, ::std::map<int,RPCData> >::iterator it;
		::std::map<int,RPCData>::iterator it2;
		bool ok=false;

		while(true){
			mut.lock();
			it=ret_map.find(client_socket_id);
			if(it != ret_map.end()) {
				it2 = it->second.find(id);
				if(it2!=it->second.end()) {
					r=it2->second;
					ok=true;
				}
			}
			mut.unlock();

			if(ok) {
				int client_socket_id = r.client_socket_id;
				int type = r.type;
				char f_rt = (char) (type);
				int size = r.size;	
				char* b = r.buffer;

				send(client_socket_id,(char*)(&type),sizeof(int));
				if(f_rt != 'v'){
					if(f_rt == 's' || f_rt == 'p') send(client_socket_id,(char*)(&size),sizeof(int));
					if(size>0){
						send(client_socket_id,b,size);
						free(b);
					}
				}
				return;
			}
			sleep(timeout);
		}
	}


private:

	::std::map<int, ::std::map<int,RPCData> > ret_map;

	Mutex mut;

};

class DataMap{

public:

	
	DataMap(){
		mut.init();
	}

	void insert(int client_socket_id, int id, int type, int size, char* b) {
		mut.lock();
		::std::map<int,RPCData>::iterator it=data_map.find(id);
		RPCData r;
		if(it != data_map.end()) {
			r = it->second;
			if(r.buffer) {
				free(r.buffer);
				r.buffer=0;
			}
		}
		data_map[id]= RPCData(client_socket_id,type,size,b);
		mut.unlock();
	}

	void sendData(int client_socket_id, int id, double timeout=0.1) {
		RPCData r;
		::std::map<int,RPCData>::iterator it;
		bool ok=false;

		while(true){
			mut.lock();
			it=data_map.find(id);
			if(it != data_map.end()) {
				r=it->second;
				ok=true;
			}
			mut.unlock();

			if(ok) {
				int type = r.type;
				char f_rt = (char) (type);
				int size = r.size;
				char* b = r.buffer;

				send(client_socket_id,(char*)(&type),sizeof(int));
				if(f_rt != 'v'){
					if(f_rt == 's' || f_rt == 'p') {
						send(client_socket_id,(char*)(&size),sizeof(int));
					}

					if(size>0) {
						send(client_socket_id,b,size);
					}
				}
				return;
			}

			sleep(timeout);

		}
	}


private:

	::std::map<int, RPCData> data_map;

	Mutex mut;

};


struct FCallArgs {

	int len_fname;
	char* fname;
	int n_args;
	int size_args;
	char* args;

	FCallArgs(int len_fname=0, char* fname=0, int n_args=0, int size_args=0, char* args=0):
		len_fname(len_fname), fname(fname), n_args(n_args), size_args(size_args), args(args) {
	}

	void receive (int client_socket_id) {
		
		recv (client_socket_id, &len_fname, sizeof (len_fname), 0);
		

		g_mutex.lock();

		fname = (char*) malloc ((len_fname+1)*sizeof(char));

		fname[len_fname]='\0';

		g_mutex.unlock();

		
		recv (client_socket_id, fname, len_fname, 0);
		recv (client_socket_id, &n_args, sizeof(n_args), 0);
		

		if(n_args>0){
			
			recv (client_socket_id, &size_args, sizeof(size_args), 0);
			

			g_mutex.lock();

			args = (char*) malloc(size_args*sizeof(char));

			g_mutex.unlock();

			
			recv (client_socket_id, args, size_args, 0);
			
		}


	}

	~FCallArgs() {}
};


DataMap data_map;
RetMap ret_map;
SecurePrint printer;
WaitProcess wait_process;

bool send(int m_socket, const char *buffer, int length) {
	int sent = 0;

	// Loop the send() because it might happen to not send all data once.
	do {
		send_mutex.lock();

		int res = ::send(m_socket, (&buffer[sent]), (length - sent), 0);

		send_mutex.unlock();

		if (res >= 0) {
			sent += res;
		} else {
			return false;
		}
	} while (sent < length);

	return true;
}

bool function_call(FCallArgs* f_call_args, int client_socket_id, bool send_result=true, int id_process=0){

	int n_args = f_call_args->n_args;
	char f_rt;
	char* fname = f_call_args->fname;
	char* buffer = f_call_args->args;
	int ibuffer;

	delete f_call_args;

	void* fpf;
	ffi_call_func pf;

	ffi_cif cif;

	ffi_type* ffi_rt;
	ffi_type** ffi_args;

	void** ffi_values;


	g_mutex.lock();
	fpf = dlsym(ext_mod_map[ext_func_map[fname]], fname);

	if (fpf == NULL) {
		clever_fatal("[RPC] function `%s' not found at `%s'!",
			fname, ext_func_map[fname].c_str());
		free (fname);
		close (client_socket_id);
		wait_process.dec();

		g_mutex.unlock();

		return false;
	}

	f_rt = ext_ret_map[fname].c_str()[0];


	ffi_rt = _find_rpc_type(&f_rt);

	pf = reinterpret_cast<ffi_call_func>(fpf);
	g_mutex.unlock();

	if(n_args>0){
		g_mutex.lock();
		ffi_args = (ffi_type**) malloc(n_args*sizeof(ffi_type*));
		ffi_values = (void**) malloc(n_args*sizeof(void*));
		g_mutex.unlock();
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
					g_mutex.lock();
					int* pi = (int*)malloc(sizeof(int));
					g_mutex.unlock();

					*pi = * ((int*)(buffer+ibuffer));
					ibuffer+=sizeof(int);

					ffi_values[i] = pi;
				}
			break;

			case 'd': 
				{
					g_mutex.lock();
					double* pd = (double*)malloc(sizeof(double));
					g_mutex.unlock();

					*pd = * ((double*)(buffer+ibuffer));
					ibuffer+=sizeof(double);

					ffi_values[i] = pd;
				}
			break;

			case 'c': case 'b':
				{
					g_mutex.lock();
					char* pc = (char*)malloc(sizeof(char));
					g_mutex.unlock();

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

					g_mutex.lock();
					char** s = (char**)malloc(sizeof(char*));

					if(type_arg == 'p') {
						*s = (char*)malloc(len_s*sizeof(char));
					} else {
						*s = (char*)malloc((1+len_s)*sizeof(char));
						(*s)[len_s]='\0';
					}
					g_mutex.unlock();

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

		g_mutex.lock();

		free (fname);

		if(n_args>0){
			free (buffer);
			free(ffi_values);
			free(ffi_args);
		}

		g_mutex.unlock();

		wait_process.dec();

		return false;
	}

	/*call function*/
	int if_rt=f_rt;
	
	
	switch ( f_rt ) {
			case 'i': 
				{
					int vi;
					ffi_call(&cif, pf, &vi, ffi_values);

					if (send_result) {
						send(client_socket_id,(char*)(&if_rt),sizeof(int));
						send(client_socket_id,(char*)(&vi),sizeof(int));
					} else {
						g_mutex.lock();

						char* b = (char*) malloc (sizeof(int));
						memcpy(b,&vi,sizeof(int));

						g_mutex.unlock();

						ret_map.insert(client_socket_id, id_process, if_rt, sizeof(int),b);
					}
				}
			break;

			case 'd': 
				{
					double vd;
					ffi_call(&cif, pf, &vd, ffi_values);
					if (send_result) {
						send(client_socket_id,(char*)(&if_rt),sizeof(int));
						send(client_socket_id,(char*)(&vd),sizeof(double));
					} else {
						g_mutex.lock();

						char* b = (char*) malloc (sizeof(double));
						memcpy(b,&vd,sizeof(double));

						g_mutex.unlock();

						ret_map.insert(client_socket_id, id_process, if_rt, sizeof(double),b);
					}
				}
			break;

			case 'c': case 'b':
				{
					char vc;
					ffi_call(&cif, pf, &vc, ffi_values);

					if (send_result) {
						send(client_socket_id,(char*)(&if_rt),sizeof(int));
						send(client_socket_id,(char*)(&vc),sizeof(char));
					} else {
						g_mutex.lock();

						char* b = (char*) malloc (sizeof(char));
						memcpy(b,&vc,sizeof(char));

						g_mutex.unlock();

						ret_map.insert(client_socket_id, id_process, if_rt, sizeof(char),b);
					}
				}
			break;

			case 'p': case 's':
				{
					char* vs[1];
					int size_vs;

					ffi_call(&cif, pf, &vs, ffi_values);

					 size_vs = * ((int*) vs[0]);

					if (send_result) {
						send(client_socket_id,(char*)(&if_rt),sizeof(int));
						send(client_socket_id,(char*)(&size_vs),sizeof(int));
						send(client_socket_id,(char*)(vs[0]+sizeof(int)), size_vs);
						free(vs[0]);
					} else {

						g_mutex.lock();

						char* b = (char*) malloc (size_vs*sizeof(char));
						memcpy(b,(char*)(vs[0]+sizeof(int)),size_vs);

						g_mutex.unlock();

						ret_map.insert(client_socket_id, id_process, if_rt, size_vs*sizeof(char),b);
					}

				}
			break;

			case 'v':
				{
					ffi_call(&cif, pf, NULL, ffi_values);

					if (send_result) {
						send(client_socket_id,(char*)(&if_rt),sizeof(int));
					} else {
						ret_map.insert(client_socket_id, id_process, if_rt, 0,0);
					}
				}
			break;
	}

	/*free memory*/

	ibuffer = 0;
	for( int i = 0; i < n_args; ++i){
		char type_arg;
		type_arg = buffer[ibuffer]; ibuffer+=sizeof(char);

		ffi_args[i] = _find_rpc_type(&type_arg);

		g_mutex.lock();

		if(type_arg == 's' || type_arg == 'p'){
			free(* ((char**)ffi_values[i]));
		}

		free(ffi_values[i]);

		g_mutex.unlock();


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

	g_mutex.lock();

	if(n_args>0){
		free(ffi_args);
		free(ffi_values);
		free(buffer);
	}

	free(fname);

	g_mutex.unlock();

	return true;
}

struct ProcessArgs {
	FCallArgs* f_call_args;
	int client_socket_id;
	int id_process;

	ProcessArgs(FCallArgs* f_call_args=0, int c=0, int id=0):
		f_call_args(f_call_args), client_socket_id(c), id_process(id) {}
};

void* call_process_thread(void* args) {
	ProcessArgs* m_args = reinterpret_cast<ProcessArgs*> (args);

	int id_process = m_args->id_process;
	int client_socket_id = m_args->client_socket_id;
	FCallArgs* f_call_args = m_args->f_call_args;

	delete m_args;

	function_call(f_call_args, client_socket_id, false, id_process);

	return NULL;
}

void call_process (FCallArgs* f_call_args, int client_socket_id, int id_process){
	//Create thread to manage connection
	
	pthread_attr_t attr;
	pthread_t thread;

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	g_mutex.lock();

	ProcessArgs* args = new ProcessArgs(f_call_args, client_socket_id, id_process); 

	g_mutex.unlock();

	pthread_create (&thread, &attr, &call_process_thread, (void*)(args));
	

	pthread_attr_destroy (&attr);


}


void* process(void* args) {

	wait_process.inc();
	int client_socket_id; 
	int type_call=0;
	int len_fname=0;
	int id_message=0;
	int vi_message=0;
	int t_message=0;
	int id_process=0;
	double time_sleep;
	char *fname, *buffer;
	FCallArgs* f_call_args;

	client_socket_id = * (reinterpret_cast<int*>(args));
	free(args);


	while (true) {
		
		/* First, read the length of the text message from the socket. If
		read returns zero, the client closed the connection. */
		
		if (recv (client_socket_id, &type_call, sizeof (type_call), 0) == 0){
			close (client_socket_id);
			wait_process.dec();
			
			return NULL;
		}
		

		switch (type_call) {

			case CLEVER_RPC_RI:

				recv (client_socket_id, &id_message, sizeof (id_message), 0);
				recv (client_socket_id, &vi_message, sizeof (vi_message), 0);

				t_message = 'i';

				g_mutex.lock();
				buffer = (char*) malloc (sizeof(int));
				g_mutex.unlock();

				memcpy(buffer,&vi_message,sizeof(int));

				data_map.insert(client_socket_id, id_message, t_message, sizeof(int),buffer);
			break;

			case CLEVER_RPC_SI:

				recv (client_socket_id, &id_message, sizeof (id_message), 0);
				recv (client_socket_id, &time_sleep, sizeof (time_sleep), 0);

				data_map.sendData(client_socket_id, id_message, time_sleep);
			break;

			case CLEVER_RPC_PI:

				recv (client_socket_id, &len_fname, sizeof (len_fname), 0);

				printer.printInt(len_fname);
			break;

			case CLEVER_RPC_PS:

				
				recv (client_socket_id, &len_fname, sizeof (len_fname), 0);
				

				g_mutex.lock();

				fname = (char*) malloc ((len_fname+1)*sizeof(char));
				fname[len_fname]='\0';

				g_mutex.unlock();

				
				recv (client_socket_id, fname, len_fname, 0);
				

				printer.printStr(fname);
				free(fname);
			break;

			/* function call*/
			case CLEVER_RPC_FC:

				g_mutex.lock();

				f_call_args = new FCallArgs;

				g_mutex.unlock();

				f_call_args->receive(client_socket_id);

				if (!function_call(f_call_args, client_socket_id)) {
					return NULL;
				}
			break;

			/* process call */
			case CLEVER_RPC_PC:
				
				recv (client_socket_id, &id_process, sizeof (id_process), 0);
				

				g_mutex.lock();

				f_call_args = new FCallArgs;

				g_mutex.unlock();

				f_call_args->receive(client_socket_id);

				call_process (f_call_args, client_socket_id, id_process);
			break;

			/*get result process*/
			case CLEVER_RPC_GR:
				
				recv (client_socket_id, &id_process, sizeof(id_process), 0);
				recv (client_socket_id, &time_sleep, sizeof(time_sleep), 0);
				

				ret_map.sendData(client_socket_id, id_process, time_sleep);
			break;
		}
	}

	close (client_socket_id);
	wait_process.dec();
	
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
	g_mutex.lock();
	if(ext_func_map.find(funcname)==ext_func_map.end()){
		ext_func_map[funcname] = libname;
		ext_ret_map[funcname] = rettype;
	}
	g_mutex.unlock();
}

void RPCValue::loadLibrary(const char* libname) {
	g_mutex.lock();
	if(ext_mod_map.find(libname)==ext_mod_map.end()){
		void* m = dlopen(libname, RTLD_NOW);

		ext_mod_map[libname] = m;
		if (m == NULL) {
			clever_fatal("[RPC] Shared library `%s' not loaded!\n Error: \n %s",
				libname, dlerror());
			return;
		}
	}
	g_mutex.unlock();
}


void RPCValue::createConnection(int client_socket_id) {
	//Create thread to manage connection

	pthread_attr_t attr;
	pthread_t thread;

	pthread_attr_init (&attr);
	pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

	g_mutex.lock();
	int * cp = (int*)malloc(sizeof(int)); 
	*cp = client_socket_id;
	g_mutex.unlock();

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

	wait_process.init();

	do {
		struct sockaddr client_name;
		socklen_t client_name_len;
		int client_socket_id;
		int type_call;
		type_call=client_name_len=0;

		memset(&client_name, 0, sizeof(client_name));
		
		printer.printMsg("Waiting client...\n");

		client_socket_id = accept (m_socket, &client_name, &client_name_len);
		
		printer.printMsg("New client...\n");
		
		
		if (recv (client_socket_id, &type_call, sizeof (type_call), 0) == 0){
			close (client_socket_id);
			
			continue;
		}
		

		if(type_call == CLEVER_RPC_KILL) {
			printer.printMsg("Server died...\n");
			
			while(recv (client_socket_id, &type_call, sizeof (type_call), 0)!=0);
			close (client_socket_id);
			
			kill_me = 1;
		}else {
			createConnection(client_socket_id);
			printer.printMsg("Client connected...\n");
			int ok=CLEVER_RPC_OK;
			send(client_socket_id,(char*)(&ok),sizeof(int));
		}
		
	} while (!kill_me);

	wait_process.wait();
	close (m_socket);

}

bool RPCValue::createClient(const char* host, const int port, const int time) {
	socket = new CSocket;

	socket->setHost(host);
	socket->setPort(port);
	socket->setTimeout(time);

	int t=0;

	fprintf(stderr,"Connecting.");
	while (t<time) {
		if (socket->connect()) {
			fprintf(stderr,"\n");
			return true;
		}
		fprintf(stderr,".");
		sleep(1);
	}
	clever_fatal("[RPC] Failed to connect with RPC server!");
	return false;
}

void RPCValue::sendString(const char* s, int len) {
	int id=CLEVER_RPC_PS;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&len),sizeof(int));
	socket->send(s,len);
}

void RPCValue::sendInteger(int v) {
	int id=CLEVER_RPC_PI;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&v),sizeof(int));
}

void RPCValue::sendKill() {
	int id=CLEVER_RPC_KILL;

	socket->send((char*)(&id),sizeof(int));
}

bool RPCValue::sendInit() {
	int id=CLEVER_RPC_INIT;

	socket->send((char*)(&id),sizeof(int));

	int ok;

	if(!socket->receive((char*)(&ok),sizeof(int))) {
		return false;
	}

	return true;
}

void RPCValue::sendFunctionCall(const char* fname, const char* args, int len_fname, int n_args, int len_args){
	int id=CLEVER_RPC_FC;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&len_fname),sizeof(int));
	socket->send(fname,len_fname);
	socket->send((char*)(&n_args),sizeof(int));

	if(n_args>0){
		socket->send((char*)(&len_args),sizeof(int));
		socket->send(args,len_args);
	}

}

void RPCValue::sendProcessCall(int id_process, const char* fname, const char* args, int len_fname, int n_args, int len_args){
	int id = CLEVER_RPC_PC;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&id_process),sizeof(int));
	socket->send((char*)(&len_fname),sizeof(int));
	socket->send(fname,len_fname);
	socket->send((char*)(&n_args),sizeof(int));

	if(n_args>0){
		socket->send((char*)(&len_args),sizeof(int));
		socket->send(args,len_args);
	}

}

void RPCValue::sendInteger(int id_message, int v) {
	int id = CLEVER_RPC_RI;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&id_message),sizeof(int));
	socket->send((char*)(&v),sizeof(int));
}

int RPCValue::receiveInt(int id_message, double time_sleep) {
	int id = CLEVER_RPC_SI;

	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&id_message),sizeof(int));
	socket->send((char*)(&time_sleep),sizeof(double));

	int v;
	int type;

	if(!socket->receive((char*)(&type),sizeof(int))) {
		clever_fatal("[RPC] Failed to receive int!\n");
		return 0;
	}

	if(type != 'i'){
		clever_fatal("[RPC] Failed to receive int!\n");
		return 0;
	}

	socket->receive((char*)(&v),sizeof(int));

	return v;
}

RPCObjectValue* RPCValue::getResultProcess(int id_process, double time_sleep) {
	int id = CLEVER_RPC_GR;
	socket->send((char*)(&id),sizeof(int));
	socket->send((char*)(&id_process),sizeof(int));
	socket->send((char*)(&time_sleep),sizeof(double));
	return receiveObject();
}

RPCObjectValue* RPCValue::receiveObject(){
	RPCObjectValue* obj =  new RPCObjectValue;

	int* type = (int*)malloc(sizeof(int));
	int len=sizeof(int), len_s;
	int* vi;
	char* vc, *buffer;
	double* vd;

	if(!socket->receive((char*)type,len)){
		clever_fatal("[RPC] Failed to receive object!\n");
	}

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


