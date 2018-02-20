#include"func.h"
void sig(int signum)
{
	time_t t;
	time(&t);
	printf("%s\n",ctime(&t));
}
int main()
{
	signal(SIGPROF,sig);
	sig(0);
//	kill(0,SIGALRM);
	struct itimerval t;
	bzero(&t,sizeof(t));
	t.it_value.tv_sec=3;
	t.it_interval.tv_sec=2;
	int ret=setitimer(ITIMER_PROF,&t,NULL);
	if(-1==ret)
	{
		perror("setitimer");
		return -1;
	}
	sleep(3);
	while(1);
}
