#include<stdlib.h>
#include<stdio.h>
#include <unistd.h>
int main()
{
		printf("Parent process id:%d\n",getpid()); pid_t iRet = fork();
		if(iRet < 0){//出错
				printf("Create child process fail!\n"); }else if(iRet == 0){//表示子进程
						printf("child process id:%d ppid:%d\n",getpid(),getppid()); }else{//表示父进程
						} printf("parent process success,child id:%d\n",iRet);
		return 0; }
