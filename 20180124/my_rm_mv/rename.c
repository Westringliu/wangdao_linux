#include"func.h"

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error argc\n");
		return -1;
	}
	int ret=rename(argv[1],argv[2]);
	if(-1==ret)
	{
		perror("rename");
		return -1;
	}
	return 0;
}
