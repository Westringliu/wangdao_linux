#include "factory.h"

void* th_func(void* p)
{
    pfac pf=(pfac)p;
    pque_t que=&pf->que;
    pnode_t pcur;
    while(1)
    {
        pthread_mutex_lock(&que->mutex);
        if(0==que->que_size)
        {
            pthread_cond_wait(&pf->cond,&que->mutex);
        }
        que_get(que,&pcur);
        pthread_mutex_unlock(&que->mutex);
        trans_file(pcur->new_fd);       
        free(pcur);
    }
}

int main(int argc,char* argv[])
{
    if(argc!=5)
    {
        printf("./thread_pool_server IP  PORT  thread_num capacity\n");
        return -1;
    }
    int thread_num=atoi(argv[3]);
    int capacity=atoi(argv[4]);
    factory f;
    factory_init(&f,thread_num,capacity,th_func);
    factory_start(&f);
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
    listen(sfd,capacity);
    int new_fd;
    pque_t que=&f.que;
    pnode_t pnew;
    while(1)
    {
        new_fd=accept(sfd,NULL,NULL);
        pnew=(pnode_t)calloc(1,sizeof(node_t));
        pnew->new_fd=new_fd;
        que_set(que,pnew);//放入队列
        printf("set in queue success\n");
        pthread_cond_signal(&f.cond);//唤醒子线程
    }
}

