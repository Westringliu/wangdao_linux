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
	fd=open(argv[1],O_RDWR|O_CREAT);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	printf("fd=%d\n",fd);
	char buf[128]={0};
	int ret;
	ret=read(fd,buf,sizeof(buf));
	if(-1==ret)
	{
		perror("read");
		return -1;
	}
	printf("buf=%s ret=%d\n",buf,ret);
	close(fd);
	return 0;
}
