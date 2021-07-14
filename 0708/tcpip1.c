#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

//현재 이 코드의 컨셉은 서버 1대에 클라이언트 1대만 접속 가능
int main(int argc, char *argv[])
{
	int serv_sock;
	int clnt_sock;

	//소켓의 주소값을 저장하는 구조체 객체 선언
	//책 p68
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size;

	//보낼 메시지 : 서버 -> 클라이언트로
	char message[] = "Hello world!\n";

	if(argc != 2){
		// ./tcpip1 [포트번호]
		printf("USAGE : %s <port>\n", argv[0]);
		exit(1);
	}

	//step1. socket() : 서버 소켓을 생성
	//fd값.. 0 : stdin, 1 : stdout, 2 : stderr
	//3 :serv_sock
	serv_sock = socket(PF_INET, SOCK_STREAM, 0); //프로토콜 IPv4, TCP
	if(serv_sock == -1)
		error_handling("socket() error");

	//step2. bind() :서버의 ip주소, 포트번호, 주소체계 설정
	//bind()함수를 호출하기 전에 구조체에 셋팅
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family=AF_INET; //주소체계 IPv4
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY); //IP주소 //htonl : host to network longtype(4byte)
	serv_addr.sin_port=htons(atoi(argv[1])); //port번호(short type 2byte)

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1 )
		error_handling("bind() error");

	//step3. listen() : 접속 대기열 버퍼의 크기를 설정
	if(listen(serv_sock, 5)==-1) //대기열 버퍼의 크기 : 5
		error_handling("listen() error");

	//step4. accept() : 클라이언트의 접속요청을 받아들임
	//클라이언트 소켓을 생성
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock, (struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock==-1)
		error_handling("accept() error");

	//step5. 데이터 read/write
	write(clnt_sock, message, sizeof(message));
	close(clnt_sock);
	close(serv_sock);
	return 0;
}
