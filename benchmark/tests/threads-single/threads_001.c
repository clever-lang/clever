#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
	
	time_t t0 = clock();

	int L = 10000000;
	long long acc = 0;
	int ini = 0, fim = 2 * L;
	while (ini <= fim) acc += ini++;
	
	time_t t1 = clock();

	printf("C\n");
	printf("%lld\n", acc);
	return 0;
}

