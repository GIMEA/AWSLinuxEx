#include <stdio.h> // printf()
#include <unistd.h> //pid_t, getpid(), sleep

int main(void)
{
	pid_t pid;
	getpid(); //현재 자신의 프로세스 id를 읽어온다.
	printf("my pid = %d\n", pid);
	sleep(10);
}
