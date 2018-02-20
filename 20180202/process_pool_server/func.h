#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <strings.h>
#include <time.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/time.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/uio.h>
#include <sys/epoll.h>
typedef struct{
        pid_t pid;
            int pfd;//子进程管道的对端
                short busy;//标识进程是否忙碌
}Data,*pData;

typedef struct{
        int len;
            char buf[1000];
}train;

#define FILENAME "file"
void make_child(pData p,int pro_num);
void child_handle(int pfd);
void send_fd(int,int);
void recv_fd(int,int*);
void trans_file(int);
void sendn(int,char*,int);
