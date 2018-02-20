#include"func.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}	
	int ret=unlink(argv[1]);
	if(-1==ret)
	{
		perror("unlike");
		return  -1;
	}
	return 0;
}
