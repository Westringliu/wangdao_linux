#include"func.h"

int main()
{
	FILE *fp=popen("./scanf","w");
	if(NULL==fp)
	{
		perror("popen");
		return -1;
	}
	char buf[128]="3 4";
	fwrite(buf,sizeof(char),strlen(buf),fp);
	fclose(fp);
	return 0;
}
