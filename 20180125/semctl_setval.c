#include"func.h"

int main()
{
	int semid;
	semid=semget(1234,1,IPC_CREAT|0600);
		if(-1==semid)
		{
			perror("semget");
		return -1;	
		}
		int ret;
		ret=semctl(semid,0,SETVAL,1);
		if(-1==ret)
		{
			perror("semctl");
			return -1;
		}
		ret=semctl(semid,0,GETVAL);
		if(-1==ret)
		{
			perror("semctl");
			return -1;
		}
		printf("semval=%d\n",ret);
		return 0;
}
