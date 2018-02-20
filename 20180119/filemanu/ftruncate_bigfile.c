#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	long file_size=atol(argv[2]);//char -> long
	int ret=ftruncate(fd,file_size);
	if(-1==ret)
	{
		perror("ftruncate");
		return -1;
	}
	return 0;
}
