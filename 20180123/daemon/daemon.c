#include"func.h"

int main(int argc,char *argv[])
{
	int fd=open("/tmp/file",O_RDWR);
	int i;
	if(!fork())
	{	
		printf("i am running\n");
		setsid();
		chdir("/");
		umask(0);
		while(1)
		{
			sleep(3);
			write(fd,"i have sleep 3 second\n",22);
		}
	}
	else{
		exit(0);
	}
}
