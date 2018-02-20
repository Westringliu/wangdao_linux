#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
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
//	printf("fd=%d\n",fd);
	char c='h';
	int ret;
	ret=lseek(fd,1024,SEEK_SET);
	if(-1==ret)
	{
		perror("lseek");
		return -1;
	}
	write(fd,&c,sizeof(c));
	close(fd);
	return 0;
}
