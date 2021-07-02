#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	printf("Running ps with system\n");
	//system("ls -al"); //ls -al 명령어가실행됨
	system("./cmd_arg asdf 1234");
	printf("Process is Done\n");

	exit(0); //return 0; ->좀비프로세서
}
