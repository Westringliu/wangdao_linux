#include<stdio.h>
#include<unistd.h>
int main()
{	
	char path[128]={0};
	getcwd(path,sizeof(path));
	puts(path);
	printf("%s\n",getcwd(NULL,0));
	return 0;
}
