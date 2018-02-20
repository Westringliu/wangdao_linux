#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
	printf("uid=%d gid=%d euid=%d egid=%d\n",getuid(),getgid(),geteuid(),getegid);
	return 0;
}
