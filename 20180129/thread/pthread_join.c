#include"func.h"
void *thread_func(void *p)
{
    p=malloc(20);
    printf("I am child thread,p=%p\n",p);
    pthread_exit(p);
}

int main()
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,thread_func,NULL);
    if(ret!=0)
    {
        printf("pthread_join ret=%d\n",ret);
        return -1;
    }
    void *p;
    ret=pthread_join(&pthid,&p);
    if(ret!=0)
    {
        printf("pthread ret=%d\n",ret);
       return -1; 
    }
    printf("i am main thread p=%p\n",p);
    return 0;
}
