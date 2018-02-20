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
	fd=open(argv[1],O_WRONLY,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
//	printf("i am write\n");
	char *p="i am write\n";
	write(fd,p,strlen(p));
	while(1);

}
