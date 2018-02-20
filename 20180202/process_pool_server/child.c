#include "func.h"

void make_child(pData p,int pro_num)
{
    int i;
    int fds[2];
    pid_t pid;
    for(i=0;i<pro_num;i++)
    {
        //socketpair创建的只适用于父子进程或者线程间通信，不能用于两个进程之间通信
        socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
        pid=fork();
        if(0==pid)
        {
            close(fds[1]);
            child_handle(fds[0]);
        }
        close(fds[0]);
        p[i].pid=pid;
        p[i].pfd=fds[1];
        p[i].busy=0;
        printf("p[i].pfd=%d\n",p[i].pfd);
    }
}

void child_handle(int pfd)
{
    int new_fd;
    char c=0;
    while(1)
    {
        recv_fd(pfd,&new_fd);
        printf("I will send file new_fd=%d\n",new_fd);
        trans_file(new_fd);     
        write(pfd,&c,sizeof(c));//通知父进程我完成了文件发送
    }
}

