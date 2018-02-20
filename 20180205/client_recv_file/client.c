#include "func.h"

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("error args\n");
        return -1;
    }
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);
    if(-1==sfd)
    {
        perror("socket");
        return -1;
    }
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));//一定要用htons
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret=connect(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)
    {
        perror("connect");
        return -1;
    }
    char buf[1000]={0};
    int len;
    recv(sfd,&len,sizeof(len),0);//接收文件名
    recv(sfd,buf,len,0);
    int fd;
    fd=open(buf,O_RDWR|O_CREAT,0666);
    if(-1==fd)
    {
        perror("open");
        return -1;
    }
    while(1)
    {
        recv(sfd,&len,sizeof(len),0);
        if(len>0)
        {
            bzero(buf,sizeof(buf));
            recv(sfd,buf,len,0);
            write(fd,buf,len);
        }else{
            break;
        }
    }
    close(fd);
    close(sfd);
}


