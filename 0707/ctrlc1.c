#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void sigHandler(int sig)
{
	printf("OUCH! = I got signal %d\n", sig);
	//한번 실행하고나면 다시 default로 바꿔줌
	//(void)signal(SIGINT, SIG_DFL);
}

int main()
{
	//signal을 활용하기 위해서는 signal과 핸들러를 정의해야 한다.
	//SIGINT라는 시그널이 들어오면, sigHandler()로 점프해서 이동하라(->커널에 등록)
	signal(SIGINT, sigHandler);
	//signal(SIGINT, SIG_DFL);

	while(1)
	{
		printf("hello world!\n");
		//sleep 하는 도중에 시그널이 들어오면 시간을 유지하지 않음
		sleep(10);
	}
}
