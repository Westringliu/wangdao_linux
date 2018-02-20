#include"func.h"
void sig()
{
//	printf("%d is coming\n",signum);
		return;
}
int main()
{
	signal(SIGALRM,sig);
	alarm(5);
	pause();
	return 0;
}
