#include"func.h"

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid){
		printf("i am child,mypid=%d,myppid=%d\n",getpid(),getppid());
		abort();
		return 5;
	}else{
		printf("i am parent,pid=%d,mypid=%d\n",pid,getpid());
		int status;
		pid_t pid_recycle;
		pid_recycle=wait(&status);
		if(WIFEXITED(status))
		{
			printf("exit status=%d\n",WEXITSTATUS(status));
		}else{
			printf("child process dump\n");
		}
		return 0;
	}
}
