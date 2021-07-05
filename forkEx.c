#include <stdio.h>
#include <unistd.h> //pid_t(프로세서 id값)
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFF_SIZE 1024
int main(void)
{
	int status;
	int i = 3;
	int fd;
	pid_t pid;
	char buff[BUFF_SIZE];
	int rdByte;

	//fild descriptor table
	//프로세스의 생성과 함께 시스템에서 자동으로 장치를 열어줌
	//0 : stdin, 1 : stdout, 2 : stderr
	//다음으로 낮은 값으로 open시 번호를 할당 fd = 3일 것
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("can't open\n");
		return 0;
	}
	pid = fork();
	//fork()가 정상적으로 실행되지 않은 경우
	if (pid < 0)
	{
		printf("can't create child process\n");
		return 0;
	}

	//부모 프로세스
	else if (pid > 0)
	{
		printf("부모프로세스 %d : %d\n", getpid(), pid);
		printf("i = %d\n", i);
		rdByte = read(fd, buff, BUFF_SIZE);
		if(rdByte < 0)
			printf("can't read file\n");
		else
			printf("read:%s\n", buff);
		//wait(&status);
	}
	//자식 프로세스
	else if (pid == 0)
	{
		//sleep(1); //부모가 자식보다 먼저 종료됨(부모는 먼저 종료되면 안됨)
		printf("자식프로세스 %d\n", getpid());
		printf("i = %d\n", i);

		rdByte = read(fd, buff, BUFF_SIZE);
                if(rdByte < 0)
                        printf("can't read file\n");
                else
                        printf("read:%s\n", buff);
	}


	return 0;
}
