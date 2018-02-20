#include<stdio.h>
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp;
	fp=fopen(argv[1],"ab+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	char buf[128]={0};
	int ret;
	ret=fread(buf,sizeof(char),sizeof(buf),fp);
	if(ret<=0)
	{
		perror("fread");
		return -1;
	}
	printf("buf=%s\n",buf);
	return 0;
}
