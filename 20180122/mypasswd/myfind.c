#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

void myfind(char *path,int width,char *str,int *flag)
{
	DIR *dir;
	dir=opendir(path);
	if(NULL==dir)
	{
//		perror("opendir");
		return;
	}
	struct dirent *p;
	char buf[512]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		}else{
			if(p->d_type==4||p->d_type==8)
			{
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				myfind(buf,width+4,str,flag);
			}	
			if(!strcmp(str,p->d_name))
			{
				printf("find %s\n",buf);
				*flag=1;
			}
		}
	}
	closedir(dir);
}

int main(int argc,char *argv[])
{
	int i=0;
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	myfind(argv[1],0,argv[2],&i);
	if(1!=i)
	{
		printf("not find\n");
	}
	return 0;
}
