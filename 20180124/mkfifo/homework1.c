#include"func.h"

int main()
{
	int fds[2];
	pipe(fds);
	if(!fork())
	{
		char p1[5]="hello";
		close(fds[0]);
		write(fds[1],&p1,strlen(p1));
	}else{
		close(fds[1]);
		char p2[5];
		read(fds[0],&p2,strlen(p2));
		printf("%s\n",p2);
		wait(NULL);
		return 0;
	}
}
