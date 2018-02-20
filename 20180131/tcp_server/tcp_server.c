#include"func.h"
int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("error args\n");
            return -1;
    }
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,sfd);
    if(-1==sfd)
    {
        perror("socket");
        return -1;
    }
    printf("sfd=%d\n",sfd);
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));
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
    new_fd=accept(sfd,(struct sockaddr*)&client,&len);
    printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[128]={0};
    ret=recv(new_fd,buf,sizeof(buf),0);
    if(-1==ret)
    {
        perror("recv");
        return -1;
    }
    printf("i am server,buf=%s\n",buf);
    ret=send(new_fd,"xiexie",6,0);
    if(-1==ret)
    {
        perror("send");
        return -1;
    }
    return 0;
}


