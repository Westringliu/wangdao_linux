#include"func.h"
void *thread_func(void *p)
{
    printf("I am child thread,i=%d\n",*(int*)p);
    pthread_exit((void*)2);
}

int main()
{
    int i=1;
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,thread_func,(void**)&i);
    if(ret!=0)
    {
        printf("pthread_join ret=%d\n",ret);
        return -1;
    }
    ret=pthread_join(pthid,(void**)&i);
    if(ret!=0)
    {
        printf("pthread i=%d\n",i);
       return -1; 
    }
    printf("i am main thread,i=%d\n",i);
    return 0;
}
