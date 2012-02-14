#include <stdio.h>

extern "C"{
	
double f1(int a, double c){
	printf("<>a=%d\n",a);
	printf("<>c=%e\n",c);
	return a+c;
}

double f2(const char* f, int a, double c){
	printf("<<>>a=%d\n",a);
	printf("<<>>c=%e\n",c);
	printf("<<>>f=%s\n",f);
	
	//f[0]='S';
	return 6.6;
}

double f3(char* f){
	printf("________________--\n");
	printf("<<>>f=%c\n",f[0]);
	//f[0]='S';
	return 6.6;
}

int f4(char* f){
	if(f==0) printf("casa\n");
	else printf("moert\n");
	
	puts(f);
	
	return 2;
}

char* f5(char* f){
	f[0]='9';
	printf("%s\n",f);
	return f;
}

};