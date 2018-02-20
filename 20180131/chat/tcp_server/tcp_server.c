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
    printf("sfd=%d\n",sfd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));//一定要用htons
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)
    {
        perror("bind");
        return -1;
    }
    listen(sfd,10);
    int new_fd;
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    int len=sizeof(client);
    new_fd=accept(sfd,(struct sockaddr *)&client,&len);
    printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[128]={0};
    fd_set rdset;
    while(1)
    {
        FD_ZERO(&rdset);
        FD_SET(0,&rdset);
        FD_SET(new_fd,&rdset);
        ret=select(new_fd+1,&rdset,NULL,NULL,NULL);//传入传出参数
        if(ret>0)
        {
            if(FD_ISSET(new_fd,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=recv(new_fd,buf,sizeof(buf),0);
                if(0==ret)
                {
                    printf("byebye\n");
                    close(new_fd);
                    //close(sfd);
                    break;
                }
                printf("%s\n",buf);
            }
            if(FD_ISSET(0,&rdset))
            {
                memset(buf,0,sizeof(buf));
                ret=read(0,buf,sizeof(buf));//读取标准输入,写到2号管道
                if(ret>0)
                {
                    send(new_fd,buf,strlen(buf)-1,0);
                }else{
                    printf("byebye\n");
                    close(new_fd);
                    //close(sfd);
                    break;
                }
            }
        }
    }
    return 0;
}

