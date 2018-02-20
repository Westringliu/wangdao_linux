#include"func.h"
#define N 20000000
int t;
void *thread_func(void *p1)
{
    //printf("I am child thread\n");
    int i;
    for(i=0;i<N;i++)
    {
        t=t+1;
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,thread_func,NULL);
    if(ret!=0)
    {
        printf("pthread_join ret=%d\n",ret);
        return -1;
    }
    int i;
    for(i=0;i<N;i++)
    {
        t=t+1;
    }
    printf("%d\n",t);
    return 0;
}
