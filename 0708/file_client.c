#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

void error_handling(char* message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
	int sock;
	int read_cnt;
	int flag;
	char buf[BUF_SIZE];
	FILE *fp;
	struct sockaddr_in serv_adr;

	if(argc != 3)
	{
		printf("USAGE : %s <IP> <port>\n", argv[0]);
	        exit(1);
    	}

	//step1. socket() : 소켓을 생성
	sock = socket(PF_INET, SOCK_STREAM, 0);

	//step2.1. connect() : 프로토콜, 서버의 주소, 포트번호를 설정한 뒤
	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET; //주소체계 IPv4
	serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_adr.sin_port = htons(atoi(argv[2]));

	//step2.2 connect() 서버에 접속 요청
	connect(sock, (struct sockaddr *)&serv_adr, sizeof(serv_adr));

	fp = fopen("receive.webp", "wb");

	flag = fcntl(sock, F_GETFL, 0);
	fcntl(sock, F_SETFL, flag | O_NONBLOCK);

	//step3. read(), write()
	while((read_cnt = read(sock, buf, BUF_SIZE)) != 0)
		fwrite((void*)buf, 1, read_cnt, fp);

	//상태 확인을 위해 터미널에 출력되는 메시지
	puts("Received file data");
	//파일 데이터 수신이 끝나면 클라이언트는 "Thank you"라는 문자열을 전송
	sprintf(buf, "Thank you", 10);
	write(sock, buf, strlen(buf));

	//step4. shutdown(), close()
	fclose(fp);
	close(sock);
	return 0;
}
