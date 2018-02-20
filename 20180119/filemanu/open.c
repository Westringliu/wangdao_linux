#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT|O_EXCL,0600);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("fd=%d",fd);
	return 0;
}
