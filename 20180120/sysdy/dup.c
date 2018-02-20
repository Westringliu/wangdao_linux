#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc,char* argv[])
{
	int fd;
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
//	int fd1=fd;
	int fd1=dup(fd);	
//会输出
//	3 4
//	13 hello world
//	dup会找最近的一个空区域存储拷贝的文件信息
//	13是返回的值， read返回成功读的字节数
	close(fd);
	printf("%d %d\n",fd,fd1);
	char buf[128]={0};
	int ret=read(fd1,buf,sizeof(buf));
	printf("%d %s",ret,buf);
	return 0;
}
