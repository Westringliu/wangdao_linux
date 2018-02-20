#include"func.h"

void sig(int signum,siginfo_t *p,void *p1)
{
	printf("%d is coming\n",signum);
	sleep(1);
	printf("after %d comed\n",signum);
}

int main()
{
	sigset_t sa_mask;
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	int ret=sigaction(SIGINT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	sigaction(SIGQUIT,&act,NULL);
	while(1);
	return 0;
}
