#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

unsigned int adder(unsigned, unsigned);

int main(void)
{
	int status;
	unsigned int result = 0;
	pid_t pid;
	pid = fork();
	//자식프로세스가 정상적으로 만들어지지 않음
	if (pid == -1)
	{
		printf("can't create child process\n");
		return -1;
	}
	//자식 프로세스
	else if(pid == 0)
	{
		printf("자식 프로세스 : 내 pid = %d\n", getpid());
		result = adder(100001, 200000);
		printf("자식result = %d\n", result);
	}
	//부모 프로세스
	else if(pid > 0)
	{
		printf("부모 프로세스 : 자식 pid = %d\n", pid);
		result = adder(1, 100000);
		printf("부모result = %d\n", result);
	}
	//부모가 먼저 종료되면 안되기 때문
	wait(&status);
}

unsigned int adder(unsigned int start, unsigned int end)
{
	unsigned int i = 0;
	unsigned int result = 0;

	for(i = start; i <= end; i++)
		result += i;
	
	return result;
}
