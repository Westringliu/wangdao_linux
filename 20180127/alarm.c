#include"func.h"
void sig(int signum)
{
	printf("%d is coming\n",signum);
}
int main()
{
	signal(SIGALRM,sig);
	alarm(3);
	pause();
	return 0;
}
