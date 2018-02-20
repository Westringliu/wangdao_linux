#include"func.h"
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sig=atoi(argv[1]);
	pid_t pid=atoi(argv[2]);
	int ret=kill(pid,sig);
	if(-1==ret)
	{
		perror("kill");
		return -1;
	}
	return 0;
}
