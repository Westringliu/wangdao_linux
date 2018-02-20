#include"func.h"
typedef struct{
    int tickets;
    pthread_mutex_t mutex;
}DATA;

void *salewindow1(void *p)
{
    DATA *t=(DATA*)p;
    int i=0;
    while(1)
    {
        pthread_mutex_lock(&t->mutex);
        if(t->tickets>0)
        {
//            printf("i am salewindow1,i will sale %d\n",t->tickets);
            t->tickets--;
            i++;
//            printf("i am salewindow2,i have saled %d\n",t->tickets);
//            sleep(1);
            pthread_mutex_unlock(&t->mutex);
        }else{
            pthread_mutex_unlock(&t->mutex);
            printf("i am salewindow1,i have saled %d\n",i);
            break;
        }
    }
}

void *salewindow2(void *p)
{
    int i=0;
    DATA *t=(DATA*)p;
    while(1)
    {
        pthread_mutex_lock(&t->mutex);
        if(t->tickets>0)
        {
//            printf("i am salewindow2,i will sale %d\n",t->tickets);
            t->tickets--;
            i++;
//            printf("i am salewindow2,i have saled %d\n",t->tickets);
//            sleep(1);
            pthread_mutex_unlock(&t->mutex);
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
    t.tickets=1000000;
    pthread_mutex_init(&t.mutex,NULL);
    pthread_create(&pthid1,NULL,salewindow1,&t);
    pthread_create(&pthid2,NULL,salewindow2,&t);
    pthread_join(pthid1,NULL);
    pthread_join(pthid2,NULL);
    return 0;
}
