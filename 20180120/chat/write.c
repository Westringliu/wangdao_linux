#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char* argv[])
{
	int fd;
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	fd=open(argv[1],O_WRONLY);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("i am write\n");
//	sleep(2);
	char buf[128];
	int ret;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=read(0,buf,sizeof(buf));
		write(fd,buf,strlen(buf)-1);
	}
	return 0;
}
