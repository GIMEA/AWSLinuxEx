//멀티 스레드 환경 구성
//뮤텍스를 사용하여 공유변수(메모리)를 동시 접근하지 못하게
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sched.h>

//mutex에서 사용할 공유 변수
static int count = 10;

//mutex를 사용하기 위해 초기화
static pthread_mutex_t countlock = PTHREAD_MUTEX_INITIALIZER;

//count값을 증가시키는 thread함수
void* increment(void* data)
{
	int err;
	while(1)
	{
		err = pthread_mutex_lock(&countlock);
		if(err)
			printf("ERROR : inc lock\n");
		//critical section
		count++;
		err = pthread_mutex_unlock(&countlock);
		if(err)
			printf("ERROR : inc unlock\n");

		//mutex 동작을 원하는 다른 스레드에게 우선 순위 양보
		err = sched_yield();
		
	}
}

//count값을 감소시키는 함수
void* decrement(void* data)
{
	int err;
        while(1)
        {
                err = pthread_mutex_lock(&countlock);
                if(err)
                        printf("ERROR : dec lock\n");
                //critical section
                count--;
                err = pthread_mutex_unlock(&countlock);
                if(err)
                        printf("ERROR : dec unlock\n");

                //mutex 동작을 원하는 다른 스레드에게 우선 순위 양보
                err = sched_yield();
		usleep(1000);

        }
}

//count값을 출력하는 스레드 함수
void* getcount(void* data)
{
	int err;
	int val;

        while(1)
        {
                err = pthread_mutex_lock(&countlock);
                if(err)
                        printf("ERROR : getcount lock\n");
                //critical section
                val = count;
                err = pthread_mutex_unlock(&countlock);
                if(err)
                        printf("ERROR : getcount unlock\n");

                //mutex 동작을 원하는 다른 스레드에게 우선 순위 양보
                err = sched_yield();
		sleep(1);
		printf("count = %d\n", val);
        }
}

int main(void)
{
	//thread id값을 저장할 변수 3개 생성
	pthread_t p_thread[3];
	int err;

	pthread_mutex_init(&countlock, NULL);

	err = pthread_create(&p_thread[0], NULL, increment, NULL);
	if(err < 0)
	{
		perror("incr thread create error :");
		exit(1);
	}

	err = pthread_create(&p_thread[1], NULL, getcount, NULL);
	if(err < 0)
        {
                perror("decr thread create error :");
                exit(1);
        }

	err = pthread_create(&p_thread[2], NULL, increment, NULL);
        if(err < 0)
        {
                perror("getcount thread create error :");
                exit(1);
        }

	pthread_detach(p_thread[0]);
	pthread_detach(p_thread[1]);
	pthread_detach(p_thread[2]);

	while(1);

	return 0;
}
