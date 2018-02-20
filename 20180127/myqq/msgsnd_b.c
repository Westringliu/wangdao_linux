#include"func.h"

typedef struct msgbuf
{
	long mtype;
	char buf[64];
}MSG;

void sig()
{
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
		return;
	}
	int ret=msgctl(msgid,IPC_RMID,NULL);
	if(-1==ret)
	{
		perror("msgctl");
		return;
	}
	//------fifo ctrl A----------
//		int fd=open("2.pipe",O_WRONLY);
//		if(-1==fd)
//		{
//			perror("open");
//			return;
//		}
//		char flag[4]="q";
//		write(fd,flag,sizeof(flag));
	exit(0);
}


int main()
{
	//sigaction struct init
	struct sigaction act;
	bzero(&act,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO;
	//msg struct init
	int msgid=msgget(1234,IPC_CREAT|0600);
	if(-1==msgid)
	{
		perror("msgget");
		return -1;
	}
	MSG msg;
	bzero(&msg,sizeof(msg));
	msg.mtype=1;
	int ret;
	char msg_snd[128]="B:";
	while(1)
	{
		//ctrl exit
	//	int fd=open("1.pipe",O_RDONLY);
	//	if(-1==fd)
	//	{
	//		perror("open");
	//		return -1;
	//	}
	//	char flag[4];
	//	read(fd,flag,sizeof(flag));
	//	if(!strcmp(flag,"q"))
	//	{
	//		return 0;
	//	}
		//send message
		strcpy(msg_snd,"B:");	
		ret=sigaction(SIGINT,&act,NULL);
		fgets(msg.buf,sizeof(msg.buf),stdin);
		if(-1==ret)
		{
			perror("sigaction");
			return -1;
		}
		strcat(msg_snd,msg.buf);
		strcpy(msg.buf,msg_snd);
		system("clear");
		ret=msgsnd(msgid,&msg,sizeof(msg.buf),0);
		if(-1==ret)
		{
			perror("msgsnd");
			return -1;
		}
		ret=msgsnd(msgid,&msg,sizeof(msg.buf),0);
		if(-1==ret)
		{
			perror("msgsnd");
			return -1;
		}
	}	
	return 0;
}
