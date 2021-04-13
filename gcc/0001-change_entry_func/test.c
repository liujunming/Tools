#include <stdio.h>
#include <stdlib.h>

int test()  //test is the entry point instead of main
{
	printf("Entry is test function!\n");
	exit(0);
}

int main(int argc,char *argv[])
{
	printf("Entry is the default main!\n");
	return 0;
}
