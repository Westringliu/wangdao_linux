#include "func.h"

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
    ret=setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&resue,sizeof(int));//地址可重用
    if(-1==ret)
    {
        perror("setsockopt");
        return -1;
    }
    struct sockaddr_in ser;
    //该结构体解决了sockaddr的缺陷,把port和addr 分开储存在两个变量中
    bzero(&ser,sizeof(ser));
    ser.sin_family=AF_INET;//ipv4
    ser.sin_port=htons(atoi(argv[2]));//一定要用htons
    ser.sin_addr.s_addr=inet_addr(argv[1]);//以上结构体定义详细baidu:sockaddr_in
    ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));//把名字和套接字相关联,此步只有服务器需要
    if(-1==ret)
    {
        perror("bind");
        return -1;
    }
    int epfd=epoll_create(1);
    struct epoll_event event,*evs;
    evs=(struct epoll_event*)calloc(pro_num+1,sizeof(struct epoll_event));
    event.events=EPOLLIN;
    event.data.fd=sfd;
    epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);//注册sfd
    int i;
    //多个事件循环注册
    for(i=0;i<pro_num;i++)
    {
        event.data.fd=p[i].pfd;
        event.events=EPOLLIN;
        epoll_ctl(epfd,EPOLL_CTL_ADD,p[i].pfd,&event);
    }
    listen(sfd,pro_num);//同时连接最多pro_num客户端
    int new_fd;
    int nrecv;
    int j;
    char flag;
    while(1)
    {
        nrecv=epoll_wait(epfd,evs,pro_num+1,-1);//轮询,处理sfd和pro_num个进程
        for(i=0;i<nrecv;i++)
        {
            if(sfd==evs[i].data.fd)
            {
                new_fd=accept(sfd,NULL,NULL);//后两个一般NULL
                for(j=0;j<pro_num;j++)//找到非忙碌的子进程
                {
                    if(0==p[j].busy)
                    {
                        break;
                    }
                }
                send_fd(p[j].pfd,new_fd);
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

