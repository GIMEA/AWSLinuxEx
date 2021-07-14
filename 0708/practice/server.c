#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

//step1. socket() :소켓 생성
//step2. bind() : ip주소, 포트번호, 주소체계 설정 //인터넷 주소 적고 소켓에 적용
//step3. listen() : 접속 대기열 버퍼의 크기를 설정
//step4. accept() : 클라이언트의 접속 요청 받아들임
//step5. 데이터 read/write


