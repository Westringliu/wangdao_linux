#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
typedef struct student
{
	char num[20];
	char name[20];
	char score[20];
}STU,*PSTU;

int main(int argc,char* argv[])
{
	STU s[3]={{"20180101","xiongda","66.9"},{"20180103","xionger","78.6"},{"20180106","weiqing","99"}};
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT|O_APPEND,0666);
    if(-1==fd)
	{
		perror("open");
		return -1;
	}	
	int ret;
	ret=lseek(fd,0,SEEK_SET);
	if(-1==ret)
	{
		perror("lseek");
		return -1;
	}
	int i;
	for(i=0;i<3;i++)
	{
		ret=write(fd,s[i].num,strlen(s[i].num));
		ret=write(fd,"\t",strlen("\t"));
		ret=write(fd,s[i].name,strlen(s[i].name));
		ret=write(fd,"\t",strlen("\t"));
		ret=write(fd,s[i].score,strlen(s[i].score));
		ret=write(fd,"\n",strlen("\n"));
		if(-1==ret)
		{
			perror("write");
			return -1;
		}
	}	
	return 0;
}
