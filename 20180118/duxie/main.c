#include<stdio.h>
#include<string.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	int ret;
	fseek(fp,5,SEEK_SET);
	long off;
	off=ftell(fp);
	printf("off=%ld\n",off);
	return 0;
}
