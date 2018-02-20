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
    char buf[128]={0};
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(0,&rdset);
        FD_SET(sfd,&rdset);
        ret=select(sfd+1,&rdset,NULL,NULL,NULL);//传入传出参数
        if(ret>0)
        {
            if(FD_ISSET(sfd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(sfd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("byebye\n");
                    close(sfd);
                    break;
                }
                printf("%s",buf);
            }
            if(FD_ISSET(0,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(0,buf,sizeof(buf));//读取标准输入,写到2号管道
                if(ret>0)
                {
                    send(sfd,buf,strlen(buf)-1,0);
                }else{
                    printf("byebye\n");
                    close(sfd);
                    break;
                }
            }
        }
    }
    close(sfd);
    return 0;
}

