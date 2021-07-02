#include <stdio.h> // printf()
#include <unistd.h> //pid_t, getpid(), sleep

int main(void)
{
	pid_t pid, ppid;
	pid = getpid(); //현재 자신의 프로세스 id를 읽어온다.
	ppid = getppid();//부모 프로세스 id를 읽어온다.
	printf("my pid = %d\n", pid);
	printf("my ppid = %d\n", ppid);
	sleep(10);
}

//linux signal 종료 : kill -9 프로세스 id(pid, ppid값) -> 프로세스 종료됨
//9->SIGKILL
