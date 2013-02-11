//File: hello.c
//Description: A very simple C library
#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int x;
	double y;		
	int z;
	double w;
} C;

void hello() {
        printf("Hello Clever FFI Module!\n");
}

int add(int a, int b) {
        return a+b;
}

void printExt(char* s) {
        printf("S=%s\n",s);
}

int _sub(int a, int b){
        return a-b;
}


void setC(C* s, int x, double y, int z, double w) {
	s->x = x;
	s->y = y;
	s->z = z;
	s->w = w;
}

int getCX(C* s) {
	return s->x;
}

double getCY(C* s) {
	return s->y;
}

int getCZ(C* s) {
	return s->z;
}

double getCW(C* s) {
	return s->w;
}


char* getStr() {
	char* str = (char*) malloc(5*sizeof(char));
	sprintf(str, "%s", "dasd");
	return str;
}
