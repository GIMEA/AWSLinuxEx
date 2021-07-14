#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

//공유메모리 공간 100개
//sizeof(int)*SHMSIZE => 400bytes
#define SHMSIZE 100
#define KEYVALUE 0x1234