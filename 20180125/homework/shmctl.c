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
	printf("shmid=%d\n",shmid);
	struct shmid_ds buf;
	int ret=shmctl(shmid,IPC_STAT,&buf);
	if(-1==ret)
	{
		perror("shmctl");
		return -1;
	}
	printf("cuid=%d,cgid=%d,mode=%o,size=%ld,natt=%ld\n",buf.shm_perm.cuid,buf.shm_perm.cgid,buf.shm_perm.mode,buf.shm_segsz,buf.shm_cpid,buf.shm_nattch);
	return 0;
}
