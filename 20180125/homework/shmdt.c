#include"func.h" 
#define N 40000000

int main()
{
	int shmid;
	shmid=shmget((key_t)1234,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		perror("shmget");
		return -1;
	}
	printf("shmid=%d\n",shmid);
	int *p;
	p=(int*)shmat(shmid,NULL,0);
	if((int*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	p[0]=0;
	int i=0;
	if(!fork())
	{
		for(i=0;i<N;i++)
		{
			p[0]=p[0]+1;
		}
		return 0;
	}else{
		for(i=0;i<N;i++)
		{
			p[0]=p[0]+1;
		}
		wait(NULL);
		printf("p[0]=%d\n",p[0]);
		return 0;
	}
	return 0;
}
