#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>

void pr_exit(int status)
{
	//1. 정상적인 종료
	if(WIFEXITED(status))
		printf("normal termiantion, exit status = %d\n", WEXITSTATUS(status));
	//2. 시그널에 의해서 종료
	else if(WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d %s\n", WTERMSIG(status), WCOREDUMP(status) ? "(cor file generated)" : "");
	//3. 시그널에 의해 정지된 경우
	else if(WIFSTOPPED(status))
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

int main(void)
{
	pid_t pid, end_pid;
	int status;
	int fd;
	int result;
/*
	//perror()함수의 사용법
	fd = open("aaa.txt", O_RDONLY);
	if(fd < 0)
		//내가 출력하고자 하는 메시지 + 시스템 에러 메시지
		perror("can't open file\n");
*/	//fork 1번 : 정상적인 종료
	pid = fork();
	//정상적으로 fork()가 실행되지 않은 경우
	//자식프로세스가 생성되지 않음
	if(pid < 0)
	{
		//파일디스크립터의 2 : stderr -> 메시지를 출력
		perror("fork error");
	}
	//부모 프로세서가 실행되는 부분
	else if(pid > 0)
	{

	}
	//자식 프로세서가 실행되는 부분
	else
	{
		return 5;
		//exit(7);
	}

	//wait()함수가 호출되면 status변수의 주소값을 전달하면
	//종료조건을 적어준다.
	if(end_pid = wait(&status))
	{
		pr_exit(status);
	}
	//SIGABRT 시그널을 발생시켜서 종료
	if((pid = fork())<0)
		perror("fork error");
	//자식 프로세스
	else if(pid == 0)
	{
		//SIGABRT 시그널
		abort();
	}

	//SIGFPE : 부동소수점 나눗셈
	if(wait(&status)==pid)
	{
		pr_exit(status);
	}

	        if((pid = fork())<0)
                perror("fork error");
        else if(pid == 0)
        {
                //0으로 나누면..
                result /= 0;
        }

        if(wait(&status)==pid)
        {
                pr_exit(status);
        }


	
	return 0;
}
