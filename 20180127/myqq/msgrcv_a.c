#include"func.h"

typedef struct msgbuf
{
	long mtype;
	char buf[64];
}MSG;

int main()
{
//msg init
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
		return -1;
	}
	MSG msg;
	bzero(&msg,sizeof(msg));
	msg.mtype=1;
	//some bianliang
	int ret;
	while(1)
	{
		fputs(msg.buf,stdout);
		ret=msgrcv(msgid,&msg,sizeof(msg.buf),1,0);
		if(-1==ret)
		{
			perror("msgrcv");
			return -1;
		}
	}
//	printf("ret=%d\n",ret);
//	printf("buf=%s\n",msg.buf);	
	return 0;
}
