#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int glob_var = 3;

//스레드 함수를 생성할 때
//리턴값은 void*
//넘겨받는 인수도 void*
void* t_function(void* data)
{
	int value;
	int i = 0;
	pthread_t t_id;
	glob_var++;
	//스레드의 id값을 확인
	t_id = pthread_self();
	printf("pid = %d, t_id = %ld, glob_var = %d\n", getpid(), t_id, glob_var);
	value = *((int *)data);
	printf("value = %d\n", value);

	sleep(2);
	return (void*)(value*value);
}

int main(void)
{
	pthread_t p_thread[2];
	int a = 1;
	int b = 2;
	int err;
	int status;

	printf("현재 pid = %d, glob_val = %d\n", getpid(), glob_var);

	//추가로 스레드 2개 생성
	//1. thread변수의 주소값,
	//2. thread attribute(NULL)
	//3. 스레드 생성시 실행할 스레드 함수 주소
	//4. 스레드 생성시 전달할 인자값
	err = pthread_create(&p_thread[0], NULL, t_function, (void*)&a);

	//스레드가 정상적으로 생성되지 않았을 때
	if(err != 0)
	{
		perror("ERROR : Pthread_create() : ");
		exit(1);
	}

	err = pthread_create(&p_thread[1], NULL, t_function, (void*)&b);

        //스레드가 정상적으로 생성되지 않았을 때
        if(err != 0)
        {
                perror("ERROR : Pthread_create(1) : ");
                exit(2);
	}
	pthread_join(p_thread[0], (void**)&status);
	printf("thread_join(0) : %d\n", status);

	pthread_join(p_thread[1], (void**)&status);
        printf("thread_join(1) : %d\n", status);

}

//POSIX스레드 컴파일 할 때
//gcc -o pthread_basic pthread_basic.c -lpthread
//l : 라이브러리
//-lpthread : pthread라는 라이브러리를 불러와서 실행하라
