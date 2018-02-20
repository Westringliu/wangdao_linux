#include<stdio.h>
#include<unistd.h>

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid){
		printf("i am child,pid:%d	ppid:%d\n",getpid(),getppid());
		pid=fork();
		if(0==pid)
		{
			printf("i am grandchild,pid:%d	ppid:%d\n",getpid(),getppid());
			return 0;
		}else{
			printf("i am uncle,pid:%d	ppid:%d\n",pid,getpid());
			return 0;
		}
		return 0;
	}else{
		printf("i am parent,pid:%d	ppid:%d\n",pid,getpid());
		sleep(5);
		return 0;
	}
	
}
