#include"func.h"
int main()
{
	sigset_t mask;
	sigemptyset(&mask);//清空mask
	sigaddset(&mask,SIGINT);//设置阻塞信号
	int ret=sigprocmask(SIG_BLOCK,&mask,NULL);
	if(-1==ret)
	{
		perror("sigprocmask");
		return -1;
	}
	sleep(5);
	sigset_t pend;
	sigemptyset(&pend);//清空pend
	sigpending(&pend);//检测是否有pend
	if(sigismember(&pend,SIGINT))
	{
		printf("SIG is pend\n");
	}else{
		printf("SIG is not pend\n");
	}
	ret=sigprocmask(SIG_UNBLOCK,&mask,NULL);
	if(-1==ret)
	{
		perror("sigprocmask");
		return -1;
	}
	return 0;
}
