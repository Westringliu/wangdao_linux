#include"func.h"

void print()
{
	printf("i am print\n");
	abort();
	exit(-1);
}

int main()
{
	int i=10;
	pid_t pid;
	pid=fork();
	if(0==pid){
		printf("i am child,mypid=%d,myppid=%d\n",getpid(),getppid());
		print();
		printf("after print ,i am child\n");
		return 5;
	}else{
		printf("i am parent,pid=%d,mypid=%d\n",pid,getpid());
		int status;
		wait(&status);
		if(WIFEXITED(status))
		{
			printf("exit status=%d\n",WEXITSTATUS(status));
		}else{
			printf("child process dump\n");
		}
		return 0;
	}
}
