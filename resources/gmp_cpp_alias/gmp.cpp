/*
nffi.c
A simple C code to test FFI support on Clever.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gmp.h>

extern "C"{

mpz_t* init_bi(){
	mpz_t* r = (mpz_t*) malloc (sizeof(mpz_t));
	mpz_init(*r);
	return r;
}



void add_bi(mpz_t res, mpz_t a, mpz_t b){
	mpz_add(res,a,b);
}

void set_bi(mpz_t res, mpz_t a){
	mpz_set(res,a);
}

void set_str_bi(mpz_t res, char* str, int base){
	mpz_set_str(res, str, base);
}

void  clear_bi(mpz_t* x){
	mpz_clear(*x);
	free(x);
}

}

char* get_str_bi(mpz_t op, int base){
	char* s;
	
	s=mpz_get_str(NULL,base,op);

	return s;
}

