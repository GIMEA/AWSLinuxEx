#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(void)
{
	int status;
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
		//execl("/bin/ls", "ls", "-al", NULL);
		//execl("/bin/test_exec", "test_exec", NULL);
		execl("/usr/bin/python", "python", "test_python.py",  NULL);
	}
	//부모 프로세스
	else if(pid > 0)
	{
		printf("부모 프로세스 : 자식 pid = %d\n", pid);
	}
	//부모가 먼저 종료되면 안되기 때문
	wait(&status);
}
