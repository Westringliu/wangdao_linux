#include"func.h"

int main()
{
	int shmid;
	shmid=shmget((key_t)1234,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	char *p;
	p=(char*)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	char buf[1024];
	fgets(buf,sizeof(buf),stdin);
	while(1);
	{
		strcpy(p,buf);
	}
//	printf("shmid=%d\n",shmid);
	return 0;
}
