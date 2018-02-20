#include<stdio.h>
#include<unistd.h>
int main(int argc,char* argv[])
{	
	char path[128]={0};
	getcwd(path,sizeof(path));
	puts(path);
	char *p;
	p=getcwd(NULL,0);
	printf("%s\n",p);
	FILE *fp;
	fp=fopen("file","rb+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	return 0;
}
