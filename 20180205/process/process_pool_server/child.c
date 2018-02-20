#include "func.h"

void make_child(pData p,int pro_num)
{
    int i;
    int fds[2];
    pid_t pid;
    for(i=0;i<pro_num;i++)
    {
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
    short flag;//退出标志flag
    while(1)
    {
        recv_fd(pfd,&new_fd,&flag);
        if(0==flag)
        {
            trans_file(new_fd);     
        }else{
            exit(0);
        }
        write(pfd,&c,sizeof(c));//通知父进程我完成了文件发送
    }
}

