#include"func.h"

void sig(int signum)
{
	printf("%d is coming\n",signum);
	sleep(2);
	printf("after %d comed\n",signum);
}

int main()
{
	if(signal(SIGINT,sig))
	{
		perror("signal");
		return -1;
	}
	signal(SIGQUIT,sig);
	char buf[128]={0};
	read(STDIN_FILENO,buf,sizeof(buf));
	printf("buf=%s",buf);
	return 0;
}
