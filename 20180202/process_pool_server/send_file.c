#include "func.h"

void sig(int signum)
{
    printf("%d is coming\n",signum);
}

void trans_file(int new_fd)
{
    signal(SIGPIPE,sig);
    train t;
    strcpy(t.buf,FILENAME);//把文件名放入buf
    t.len=strlen(t.buf);
    send(new_fd,&t,4+t.len,0);//发送文件名火车给对端
    int fd;
    fd=open(FILENAME,O_RDONLY);
    if(-1==fd)
    {
        perror("open");
        return;
    }
    while(bzero(&t,sizeof(t)),(t.len=read(fd,t.buf,sizeof(t.buf)))>0)
    {
        send(new_fd,&t,4+t.len,0);
    }
    t.len=0;
    send(new_fd,&t,4,0);//代表文件结束
    close(new_fd);
}

