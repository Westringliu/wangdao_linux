#include"func.h"

void *thread_func(void *p)
{
    char buf[20];
    printf("i am child thread\n");
    sleep(1);
    p=malloc(20);
    printf("after sleep,i am child thread\n");
    free(p);
    read(0,buf,sizeof(buf));
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
    sleep(10);
    pthread_cancel(pthid);
    pthread_join(pthid,NULL);
    printf("i am main thread\n");
}
