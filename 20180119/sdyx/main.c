#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>

void printdir(char *path)
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
			printf("%s\n",p->d_name);
			if(p->d_type==4)
			{
				sprintf(buf,"%s%s%s",path,"/",p->d_name);
				printdir(buf);
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
	printdir(argv[1]);
	return 0;
}
