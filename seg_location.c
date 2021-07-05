#include <stdio.h>
#include <stdlib.h>

char globBuf[65536];
int primes[]={2, 3, 4, 7};
/*
static int square(int x)
{
	int result;
	result = x * x;
	return result;
}

static void doCalc(int val)
{
	printf("Tehd square of %d is %d\n", val, square(val));
	if(val <1000)
	{
		int t;

		t = val * val * val;
		printf("The cube of %d is %d\n", val, t);
	}
}
*/
int main(int argc, char *argv[])
{
	int test;
	int *ptest;
	*ptest = test;
	static int key = 9973;
	static char mbuf[10240000];
	char *p;
	p = malloc(1024);

	printf("test addr = 0x%x \n", ptest);
	printf("*p addr = 0x%x \n", p);
	printf("gloBuf address = 0x%x\n", globBuf);
	printf("primes[]=0x%x \n", primes);
//	doCalc(key);
//	exit(EXIT_SUCCESS);
}
