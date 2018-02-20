#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char* argv[])
{
	int fd;
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
//	int fd1=fd;
	close(1);
	int fd1=dup(fd);	
	printf("%d %d\n",fd,fd1);
//	char buf[128]={0};
//	int ret=read(fd1,buf,sizeof(buf));
//	int ret=write(STDOUT_FILENO,"hello",5);
	//	printf("%d %s",ret,buf);
	return 0;
}
