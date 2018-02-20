#include"func.h"

void cleanup(void *p)
{
    printf("i am cleanup\n");
    free(p);
}

void *thread_func(void *p)
{
    printf("i am child thread\n");
    p=malloc(20);
//    sleep(2);
    pthread_cleanup_push(cleanup,p);
    printf("after sleep,i am child thread\n");
    pthread_exit(NULL);
    pthread_cleanup_pop(0);
}

int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,thread_func,NULL);
    if(ret!=0)
    {
        printf("error ret=%d\n",ret);
        return -1;
    }
    sleep(1);
    pthread_cancel(pthid);
    pthread_join(pthid,NULL);
    printf("i am main thread\n");
    return 0;
}
