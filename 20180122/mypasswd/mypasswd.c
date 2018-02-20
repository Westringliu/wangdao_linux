#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>
int main(int argc,char *argv[])
{
	printf("uid:%d gid:%d\n",getuid(),getgid());
	printf("euid:%d egid:%d\n",geteuid(),getegid());
	FILE *fp=fopen(argv[1],"a");
	if(NULL==fp)
	{
		perror("fopen error");
		exit(-1);
	}
	fputs("world",fp);
	fclose(fp);
	return 0;
}
