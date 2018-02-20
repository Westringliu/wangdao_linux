#include"func.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	FILE *fp=popen(argv[1],"r");
	if(NULL==fp)
	{
		perror("popen");
		return -1;
	}
	printf("i am running\n");
	char buf[128]={0};
//	fgets(buf,sizeof(buf),fp);
	fread(buf,sizeof(char),sizeof(buf),fp);
	printf("len=%ld,%s",strlen(buf),buf);
	fclose(fp);
	return 0;
}
