#include "func.h"

int main(int argc,char *argv[])
{
    if(argc!=3)
    {
        printf("error args\n");
        return -1;
    }
    int sfd;
    sfd=socket(AF_INET,SOCK_STREAM,0);//ipv4提供双向连续且可信赖的数据流，即TCP。支持OOB 机制，在所有数据传送前必须使用connect()来建立连线状态
    if(-1==sfd)
    {
        perror("socket");
        return -1;
    }
    printf("sfd=%d\n",sfd);
    int resue=1;
    int ret;
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));//SO_REUSEADDR 允许在bind（）过程中本地地址可重复使用
    if(-1==ret)
    {
        perror("setsockopt");
        return -1;
    }
    struct sockaddr_in ser;//请看netinet/in.h
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;//地址家族
    ser.sin_port=htons(atoi(argv[2]));//一定要用htons
    ser.sin_addr.s_addr=inet_addr(argv[1]);//协议地址
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
    int len=sizeof(client);
    new_fd=accept(sfd,(struct sockaddr *)&client,&len);
    printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[128]={0};
    int epfd=epoll_create(1);
    struct epoll_event event,evs[2];
    event.events=EPOLLIN;
    event.data.fd=0;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,0,&event);
    if(-1==ret)
    {
        perror("epoll_ctl");
        return -1;
    }
    event.data.fd=new_fd;
    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,new_fd,&event);
    if(-1==ret)
    {
        perror("epoll_ctl");
        return -1;
    }
    int i;
    int ret1;
    while(1)
    {
        bzero(evs,sizeof(evs));
        ret=epoll_wait(epfd,evs,2,-1);
        for(i=0;i<ret;i++)
        {
            if(evs[i].data.fd==new_fd)
            {
                memset(buf,0,sizeof(buf));
                ret1=recv(new_fd,buf,sizeof(buf),0);
                if(0==ret1)
                {
                    printf("byebye\n");
                    close(new_fd);
                    close(sfd);
                    break;
                }
                printf("%s\n",buf);
            }
            if(0==evs[i].data.fd)
            {
                memset(buf,0,sizeof(buf));
                ret1=read(0,buf,sizeof(buf));//读取标准输入,写到2号管道
                if(ret1>0)
                {
                    send(new_fd,buf,strlen(buf)-1,0);
                }else{
                    printf("byebye\n");
                    close(new_fd);
                    close(sfd);
                    break;
                }
            }
        }
    }
    return 0;
}

