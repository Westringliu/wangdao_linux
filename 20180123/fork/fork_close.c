#include"func.h"
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd=open(argv[1],O_RDWR);
	pid_t pid;
	char buf[128]={0};
	int ret;
	pid=fork();
	if(0==pid)
	{
		printf("I am child,mypid=%d,myppid=%d\n",getpid(),getppid());
		ret=read(fd,buf,sizeof(buf));
		return 0;
	}else{
		printf("I am parent,pid=%d,mypid=%d\n",getpid(),getppid());
		close(fd);
		printf("I am parent,close ok\n");
		sleep(2);
		return 0;
	}
}
