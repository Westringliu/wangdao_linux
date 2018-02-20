#include"func.h"

int main()
{
	int semid=semget(1234,2,0600);
	if(-1==semid)
	{
		perror("semget");
		return -1;
	}
	printf("i am productor\n");
	struct sembuf sopp,sopv;
	sopv.sem_num=0;
	sopv.sem_op=1;
	sopv.sem_flg=SEM_UNDO;
	sopp.sem_num=1;
	sopp.sem_op=-1;
	sopp.sem_flg=SEM_UNDO;
	while(1)
	{
		printf("product num is %d\n",semctl(semid,0,GETVAL));
		printf("space num is %d\n",semctl(semid,1,GETVAL));
		semop(semid,&sopp,1);
		printf("product a product\n");
		semop(semid,&sopv,1);
		printf("product num is %d\n",semctl(semid,0,GETVAL));
		printf("space num is %d\n",semctl(semid,1,GETVAL));
		sleep(1);
	}
	return 0;
}
