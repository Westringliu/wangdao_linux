#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

void printdir(char *path,int width)
{
	DIR *dir;
	dir=opendir(path);
	if(NULL==dir)
	{
		perror("opendir");
		return;
	}
	struct dirent *p;
	char buf[512]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,"..")){
		}else{
			printf("%*s%s\n",width," ",p->d_name);
			if(p->d_type==4)
			{
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				printdir(buf,width+4);
			}	
		}
	}
	closedir(dir);
}

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	printdir(argv[1],0);
	return 0;
}
