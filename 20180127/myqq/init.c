#include"func.h"

int main()
{
	int semid=semget(1234,2,IPC_CREAT|0600);
	if(-1==semid)
	{
		perror("semget");
		return -1;
	}
	unsigned short arr[2]={0,10};
	int ret=semctl(semid,0,SETALL,arr);
	if(-1==ret)
	{
		perror("semctl");
		return -1;
	}
	return 0;
}
