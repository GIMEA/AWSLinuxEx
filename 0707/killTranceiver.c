#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ./killTranceiver [signal번호] [pid]
// argc = 3
// argv[1] = signal number
// argv[2] = proccess id
// "--help" 옵션 : 사용방법 안내
int main(int argc, char *argv[])
{
	int result = 0;
	int sigNum = 0;
	pid_t pid = 0;

	if(argc != 3 || strcmp(argv[1], "--help")==0)
		printf("%s pid sig-num\n", argv[0]);

	//pid를 숫자로 변환
	pid = atoi(argv[2]);
	sigNum = atoi(argv[1]);
	//내가 보내고자하는 프로세스에게 시그널을 전달(발생)
	result = kill(pid, sigNum);
	if(result != 0)
	{
		printf("error : system call kill()\n");
	}
	else
	{
		printf("시그널이 정상적으로 전달되었습니다.\n");
	}
	return 0;
}
