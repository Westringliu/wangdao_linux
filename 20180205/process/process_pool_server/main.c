#include "func.h"
int fds[2];
void sig_exit(int signum)
{
    //异步拉起同步
    char c='t';
    write(fds[1],&c,sizeof(c));
}
int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        printf("./process_pool_server IP PORT process_num\n");
        return -1;
    }
    int pro_num=atoi(argv[3]);
    pData p=(pData)calloc(pro_num,sizeof(Data));
    make_child(p,pro_num);
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
    ser.sin_addr.s_addr=inet_addr(argv[1]);
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
    if(-1==ret)
    {
        perror("bind");
        return -1;
    }
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(pro_num+2,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    event.data.fd=sfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
    int i;
    for(i=0;i<pro_num;i++)
    {
        event.data.fd=p[i].pfd;
        event.events=EPOLLIN;
        epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].pfd,&event);
    }
    pipe(fds);
    event.data.fd=fds[0];
    event.events=EPOLLIN;
    epoll_ctl(epfd,EPOLL_CTL_ADD,fds[0],&event);
    signal(SIGUSR1,sig_exit);
    listen(sfd,pro_num);//同时连接最多pro_num客户端
    int new_fd;
    int nrecv;
    int j;
    char flag;
    while(1)
    {
        nrecv=epoll_wait(epfd,evs,pro_num+2,-1);
        for(i=0;i<nrecv;i++)
        {
            if(evs[i].data.fd==fds[0])
            {
                printf("I want to exit\n");
                read(fds[0],&flag,sizeof(flag));
                event.events=EPOLLIN;
                event.data.fd=sfd;
                epoll_ctl(epfd,EPOLL_CTL_DEL,sfd,&event);
                for(j=0;j<pro_num;j++)
                {
                    send_fd(p[j].pfd,0,1);
                }
                exit(0);
            }
            if(sfd==evs[i].data.fd)
            {
                new_fd=accept(sfd,NULL,NULL);
                for(j=0;j<pro_num;j++)//找到非忙碌的子进程
                {
                    if(0==p[j].busy)
                    {
                        break;
                    }
                }
                send_fd(p[j].pfd,new_fd,0);
                p[j].busy=1;//把子进程标识为忙碌    
                printf("%d child is busy\n",p[j].pid);
                close(new_fd);
            }
            for(j=0;j<pro_num;j++)
            {
                if(evs[i].data.fd==p[j].pfd)
                {
                    read(p[j].pfd,&flag,sizeof(flag));
                    p[j].busy=0;//子进程通知我它空闲了
                    printf("%d child is not busy\n",p[j].pid);
                }
            }
        }
    }
}

