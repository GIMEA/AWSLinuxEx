#include "head.h"

//#define DEBUG

int main(void)
{
	char buff[30];
	struct Data st;
	int msgid = 0;
	int running = 1;
	char *pState = 0;
	char *ptr = 0;

	memset(&st, 0, sizeof(st));
	msgid = msgget((key_t)0x1234, 0666|IPC_CREAT);

	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error : %d\n", errno);
	}

	FILE *fp = fopen("test.csv", "r");

	while(running)
	{
		//read csv
        	pState = fgets(buff, sizeof(buff), fp);

		if(pState == NULL)
			break;
		//strtok : 문자열에서 ','를 기준으로 token으로 나눠줌
		ptr = strtok(buff, ",");
		strcpy(&st.name, ptr);
		//strtok(NULL, " ");
		//함수를 호출하게 되면 이전에 찾은 구분자 뒤에서 부터 다시 구분자를 찾음
		ptr = strtok(NULL, ",");
		st.kor = atoi(ptr);
		ptr = strtok(NULL, ",");
       		st.eng = atoi(ptr);
		ptr = strtok(NULL, ",");
        	st.math = atoi(ptr);
		ptr = strtok(NULL, ",");
        	st.scien = atoi(ptr);
		st.endFlag = 0;


		st.msg_type = 1;
		if(msgsnd(msgid, (void*)&st, sizeof(st), 0) == -1)
		{
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}
	}

	memset(&st, 0, sizeof(st));
	st.msg_type = 1;
	st.endFlag = 1;

#ifdef DEBUG
	printf("name=%s\n", &st.name);
	printf("kor=%d\n", st.kor);
	printf("eng=%d\n", st.eng);
	printf("math=%d\n", st.math);
	printf("scien=%d\n", st.scien);
#endif
	exit(EXIT_SUCCESS);

	return 0;
}
