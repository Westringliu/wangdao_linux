#include"func.h"
typedef struct{
    pthread_cond_t cond;
    pthread_mutex_t mutex;
}data;
void *thread_func(void *p)
{
    data *t=(data*)p;
    printf("I am pthread1,i will wait\n");
    pthread_mutex_lock(&t->mutex);
    int ret=pthread_cond_wait(&t->cond,&t->mutex);
    pthread_mutex_unlock(&t->mutex);
    printf("I am pthread1,i wake up,ret=%d\n",ret);
}

int main()
{
    pthread_t pthid;
    data t;
    int ret=pthread_cond_init(&t.cond,NULL);
    if(ret!=0)
    {
        printf("error %d\n",ret);
        return -1;
    }
    pthread_mutex_init(&t.mutex,NULL);
    pthread_create(&pthid,NULL,thread_func,&t.cond);
    sleep(1);
    pthread_cond_signal(&t.cond);
    pthread_join(pthid,NULL);
    printf("I am main pthread\n");
    return 0;
}
