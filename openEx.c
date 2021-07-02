#include<stdio.h>
#include<fcntl.h>

int main(void)
{
	int fd;
	int i;

	for(i = 0; i < 1024; i++)
	{
		fd = open("/home/hyejin/AWSLinuxEx/test.txt", O_RDONLY, O_TRUNC);
		printf("fd = %d\n", fd);
	}
	return 0;
}
