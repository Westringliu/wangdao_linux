#include"func.h"

typedef struct msgbuf
{
	long mtype;
	char buf[64];
}MSG;

int main()
{
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
		return -1;
	}
	MSG msg;
	bzero(&msg,sizeof(msg));
	msg.mtype=1;
	strcpy(msg.buf,"hello");
	int ret=msgsnd(msgid,&msg,sizeof(msg.buf),0);
	if(-1==ret)
	{
		perror("msgsnd");
		return -1;
	}	
	return 0;
}
