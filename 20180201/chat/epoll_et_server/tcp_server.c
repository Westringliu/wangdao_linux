#include "func.h"

void set_nonblock(int fd)
{
    int status;
    status=fcntl(fd,F_GETFL);
    status=status|O_NONBLOCK;
    int ret=fcntl(fd,F_SETFL,status);
}
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
    int resue=1;
    int ret;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));
    if(-1==ret)
    {
        perror("setsockopt");
        return -1;
    }
    struct sockaddr_in ser;
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(atoi(argv[2]));//一定要用htons
    //ser.sin_addr.s_addr=inet_addr(argv[1]);
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)
    {
        perror("bind");
        return -1;
    }
    listen(sfd,10);
    int new_fd;
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    int len;
    char buf[128]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,evs[3];
    event.events=EPOLLIN;//监控的是读事件
    event.data.fd=STDIN_FILENO;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
    if(-1==ret)
    {
        perror("epoll_ctl");
        return -1;
    }
    event.data.fd=sfd;//监控new_fd是否可读
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    if(-1==ret)
    {
        perror("epoll_ctl1");
        return -1;
    }
    int i;
    int nfds;
    while(1)
    {
        bzero(evs,sizeof(evs));
        nfds=epoll_wait(epfd,evs,3,-1);
        for(i=0;i<nfds;i++)
        {
            if(evs[i].data.fd==sfd)
            {
                len=sizeof(client);
                new_fd=accept(sfd,(struct sockaddr *)&client,&len);
                printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
                event.data.fd=new_fd;//监控new_fd是否可读
                event.events=EPOLLIN|EPOLLET;//监控的是读事件,边沿触发
                set_nonblock(new_fd);
                nfds=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
            }
            if(evs[i].data.fd==new_fd)
            {
                while(1)
                {
                    memset(buf,0,sizeof(buf));
                    ret=recv(new_fd,buf,sizeof(buf)-1,0);
                    if(ret>0)
                    {
                        printf("%s",buf);
                    }else if(-1==ret){
                        break;
                    }else{
                        printf("byebye");
                        event.data.fd=new_fd;
                        epoll_ctl(epfd,EPOLL_CTL_DEL,new_fd,&event);
                        close(new_fd);
                        break;
                    }
                }
                printf("\n");
            }
            if(STDIN_FILENO==evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                ret=read(STDIN_FILENO,buf,sizeof(buf));//读取标准输入,写到2号管道
                if(ret>0)
                {
                    send(new_fd,buf,ret,0);
                }else{
                    printf("byebye\n");
                    close(new_fd);
                    close(sfd);
                    goto end;
                }
            }
        }
    }
end:
    return 0;
}

