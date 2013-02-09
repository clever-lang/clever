//File: hello.c
//Description: A very simple C library
#include <stdio.h>

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

