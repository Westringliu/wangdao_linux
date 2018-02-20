#include"func.h"

int main()
{
	pid_t pid;
	pid=fork();
	if(0==pid){
		printf("i am child\n");
		while(1);
		//		sleep(10);
		return 0;
	}else{
		printf("i am parent\n");
		sleep(10);
		return 0;
	}
}
