#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	int fd;
	fd=open(argv[1],O_RDWR|O_CREAT);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
//	char buf[128]="how are you\n";
	int a[5]={1,2,3,4,5};
	int ret;
	ret=write(fd,a,sizeof(a));
//	ret=write(fd,buf,strlen(buf));
	if(-1==ret)
	{
		perror("write");
		return -1;
	}
	printf("a[0]=%d a[1]=%d a[2]=%d ret=%d\n",a[0],a[1],a[2],ret);
	close(fd);
	return 0;
}
