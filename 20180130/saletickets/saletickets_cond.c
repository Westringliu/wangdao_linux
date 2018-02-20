#include"func.h"
typedef struct{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}DATA;

void *salewindow1(void *p)
{
    DATA *t=(DATA*)p;
    int i=0;
    int ret;
    while(1)
    {
        pthread_mutex_lock(&t->mutex);
        if(t->tickets>0)
        {
            printf("i am salewindow1,i will sale %d\n",t->tickets);
            t->tickets--;
            i++;
//            sleep(1);
            if(t->tickets==0)
            {
                ret=pthread_cond_signal(&t->cond);
                printf("pthread_cond_signal ret=%d\n",ret);
            }
            pthread_mutex_unlock(&t->mutex);
            usleep(10000);
        }else{
            pthread_mutex_unlock(&t->mutex);
            printf("i am salewindow1,i have saled %d\n",i);
            break;
        }
    }
}

void *salewindow2(void *p)
{
    DATA *t=(DATA*)p;
    int i=0;
    int ret;
    while(1)
    {
        pthread_mutex_lock(&t->mutex);
        if(t->tickets>0)
        {
            printf("i am salewindow2,i will sale %d\n",t->tickets);
            t->tickets--;
            i++;
//            sleep(1);
            if(t->tickets==0)
            {
                ret=pthread_cond_signal(&t->cond);
                printf("pthread_cond_signal ret=%d\n",ret);
            }
            pthread_mutex_unlock(&t->mutex);
            usleep(10000);
        }else{
            pthread_mutex_unlock(&t->mutex);
            printf("i am salewindow2,i have saled %d\n",i);
            break;
        }
    }
}

int main()
{
    pthread_t pthid1,pthid2;
    DATA t;
    t.tickets=100;
    pthread_mutex_init(&t.mutex,NULL);
    pthread_cond_init(&t.cond,NULL);
    pthread_create(&pthid1,NULL,salewindow1,&t);
    pthread_create(&pthid2,NULL,salewindow2,&t);
    pthread_mutex_lock(&t.mutex);
    if(t.tickets>0)
    {
        printf("i will wait\n");
        pthread_cond_wait(&t.cond,&t.mutex);
    }
    t.tickets=20;
    pthread_mutex_unlock(&t.mutex);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}
