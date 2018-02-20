#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<string.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	char *pstart;
	pstart=(char *)mmap(NULL,4096,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
	if((char *)-1==pstart)
	{
		perror("mmap");
		return -1;
	}
	strcpy(pstart,"world ");
	printf("%s\n",pstart);
	int ret;
	ret=munmap(pstart,4096);
	if(-1==ret)
	{
		perror("munmap");
		return -1;
	}
	return 0;
}
