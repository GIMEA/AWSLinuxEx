//서버에서 클라이언트로 파일을 전송하는 프로그램
//이 예제는 파일을 전송하고 다루기 위해 파일 포인터를 선언
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

int main(int argc, char *argv[])
{
	int serv_sock, clnt_sock;
	FILE *fp;
	char buf[BUF_SIZE];
	int read_cnt;

	struct sockaddr_in serv_adr, clnt_adr;
	socklen_t clnt_adr_sz;

	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}

	//step1. socket() : 서버의 소켓을 생성
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);

	//step2. bind() : 서버의 프로토콜, ip주소, 포트번호를 설정
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));
	bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr));

	//step3. listen() : 대기열 버퍼의 크기 설정
	listen(serv_sock, 5);

	//step4. accept() : 클라이언트의 접속 요청 허용
	clnt_adr_sz = sizeof(clnt_adr);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);

	//step5. read()/write() : 데이터 송수신
	fp = fopen("dogs.webp", "rd");
	
	while(1)
	{
		read_cnt = fread((void*)buf, 1, BUF_SIZE, fp);
		if(read_cnt < BUF_SIZE)
		{
			//버퍼 사이즈만큼 데이터가 차지 않은 경우(짜투리 처리)
			write(clnt_sock, buf, read_cnt);
			break;
		}
		//버퍼 사이즈만큼 데이터를 전송(여기서 돌다가)
		write(clnt_sock, buf, BUF_SIZE);
	}
	
	//step6. close() : 클라이언트 접속 종료
	//close(clnt_sock);
        shutdown(clnt_sock, SHUT_WR);
        read(clnt_sock, buf, BUF_SIZE);
        printf("Message form client : %s\n", buf);

        //열었던 파일 닫기
        fclose(fp);
        //나머지 반 SHUT_RD와 동일
        close(clnt_sock);
        close(serv_sock);
}
