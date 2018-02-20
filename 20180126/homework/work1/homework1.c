#include"func.h"

typedef struct msgbuf
{
	long mtype;
	char buf[64];
}MSG;

int main()
{
	if(!fork())
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
		sleep(10);
		int ret=msgrcv(msgid,&msg,sizeof(msg.buf),1,0);
		if(-1==ret)
		{
			perror("msgrcv");
			return -1;
		}
		sleep(10);
		printf("ret=%d\n",ret);
		printf("buf=%s\n",msg.buf);	
	}else{
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
		sleep(10);
		wait(NULL);
		ret=msgctl(msgid,IPC_RMID,NULL);
		if(-1==ret)
		{
			perror("msgctl");
			return -1;
		}
	}
	return 0;
}
