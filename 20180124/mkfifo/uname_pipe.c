#include"func.h"

int main()
{
	int fds[2];
	pipe(fds);
	if(!fork())
	{
		close(fds[1]);
		int i;
		read(fds[0],&i,sizeof(i));
		printf("i am child,i=%d\n",i);
	}else{
		close(fds[0]);
		int j=10;
		write(fds[1],&j,sizeof(j));
		wait(NULL);
		return 0;
	}
}
