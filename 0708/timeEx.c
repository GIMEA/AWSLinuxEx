#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <stdlib.h>

int main(void)
{
	time_t UTCtime;
	struct tm *tm;
	//사용자 문자열로 시간정보를 저장하기 위한 문자열 버퍼
	char buf[BUFSIZ];
	//커널에서 시간 정보를 읽어서 UTCtiem변수에 넣어준다
	time(&UTCtime); //UTC 현재시간 읽어오기
	//printf("time : %d\n", (unsigned)UTCtime); // UTC 현재시간 출력

	tm = localtime(&UTCtime);
	//printf("asctime : %s\n", asctime(tm));
	
	//1. 우리가 만들 문자열 저장할 버퍼 -buf[]
	//2. 버퍼 사이즈
	//3. %a : 간단한 요일, %m : 월, %e : 일, 
	//%H : 시간(24시), %M : 분, %S : 초, %Y : 년
	//strftime(buf, sizeof(buf), "%a %m,%e %H:%M:%S %Y", tm);
	strftime(buf, sizeof(buf), "[%Y-%m-%d] %H:%M:%S", tm);

	printf("strftime : %s\n", buf);
}
