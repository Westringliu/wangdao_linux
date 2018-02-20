#include "factory.h"

void factory_init(pfac p,int thread_num,int capacity,pfunc tran_file)
{
    p->que.que_head=NULL;
    p->que.que_tail=NULL;
    p->que.que_size=0;
    p->que.que_capacity=capacity;
    pthread_mutex_init(&p->que.mutex,NULL);
    pthread_cond_init(&p->cond,NULL);
    p->pthid=(pthread_t*)calloc(thread_num,sizeof(pthread_t));
    p->flag=0;//0代表未启动，1代表启动
    p->thread_func=tran_file;
    p->thread_num=thread_num;
}

void factory_start(pfac p)
{
    if(0==p->flag)
    {
        int i;
        for(i=0;i<p->thread_num;i++)
        {
            pthread_create(p->pthid+i,NULL,p->thread_func,p);
        }
        p->flag=1;
    }else{
        printf("factory has start\n");
    }
}


