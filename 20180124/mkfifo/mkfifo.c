#include"func.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int ret;
	ret=mkfifo(argv[1],0666);
	if(-1==ret)
	{
		perror("mkfifo");
		return -1;
	}
	return 0;
}
