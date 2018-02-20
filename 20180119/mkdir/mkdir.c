#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	ret=mkdir(argv[1],0777);
	if(-1==ret)
	{
		perror("mkdir");
		return -1;
	}
	return 0;
}

