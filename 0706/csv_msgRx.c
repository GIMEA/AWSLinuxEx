#include "head.h"

//#define DEBUG


int main(void)
{
	char buff[30];
	int running = 1;
	char *pState;
	char *ptr;
	int msgid;

	struct Data st;

	memset(&st, 0, sizeof(st));

	msgid = msgget((key_t)0x1234, 0666|IPC_CREAT);
	if(msgid == -1)
	{
		fprintf(stderr, "msgget failed with error:%d\n", errno);
		exit(EXIT_FAILURE);
	}

	FILE *fp = fopen("result.csv", "w");
	fprintf(fp, "%s, %s, %s, %s, %s, %s, %s\n",
			"name", "kor", "eng", "math", "scien", "arg", "total");

	while(running)
	{

		if(msgrcv(msgid, (void*)&st, sizeof(st), 0, 0) == -1)
		{
			fprintf(stderr, "msgrcv failed with error : %d\n", errno);
			exit(EXIT_FAILURE);
		}

		if(st.endFlag == 1)
			break;

		st.total = st.kor+st.eng+st.math+st.scien;
		st.avg = st.total/4;

		fprintf(fp, "%s, %d, %d, %d, %d, %d, %d\n",
				st.name, st.kor, st.eng, st.math, st.scien, st.avg, st.total);
	}
	if(msgctl(msgid, IPC_RMID, 0) == -1)
	{
		fprintf(stderr, "msgctl(IPC_RMID) failed : %d\n", errno);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
