#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/select.h>

int main(int argc,char* argv[])
{
	int fdw,fdr;
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	fdr=open(argv[1],O_RDONLY);
	if(-1==fdr)
	{
		perror("open");
		return -1;
	}
	fdw=open(argv[2],O_WRONLY);
	if(-1==fdw)
	{
		perror("open");
		return -1;
	}
	printf("i am read\n");
	char buf[128]={0};
	int ret;
	fd_set rdset;
	while(1)
	{
		FD_ZERO(&rdset);
 		FD_SET(0,&rdset);
		FD_SET(fdr,&rdset);
   		ret=select(fdr+1,&rdset,NULL,NULL,NULL);
 	    if(ret>0)
		{
			if(FD_ISSET(fdr,&rdset))
	        {
				memset(buf,0,sizeof(buf));
				ret=read(fdr,buf,sizeof(buf));
				if(0==ret)
				{
					printf("byebye\n");
					close(fdr);
					close(fdw);
					break;
				}
				printf("%s\n",buf);
			}
			if(FD_ISSET(0,&rdset))
			{
				memset(buf,0,sizeof(buf));
				ret=read(0,buf,sizeof(buf));
				if(ret>0){
					write(fdw,buf,strlen(buf)-1);
				}else{
					printf("byebye\n");
					close(fdr);
					close(fdw);
					break;
				}
			}
		}
	}
	return 0;
}
