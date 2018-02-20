#include"func.h"

int main()
{
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
		return -1;
	}
	int ret=msgctl(msgid,IPC_RMID,NULL);
	if(-1==ret)
	{
		perror("msgctl");
		return -1;
	}
	return 0;
}
