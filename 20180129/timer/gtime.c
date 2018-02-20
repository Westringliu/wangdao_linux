#include"func.h"
int main()
{
	time_t t;
	time(&t);
	struct tm *p;
	p=gmtime(&t);
	printf("%04d-%02d-%02d %02d:%02d:%02d week=%d,days=%d\n",p->tm_year+1900,p->tm_mon+1,p->tm_mday,p->tm_hour+8,p->tm_min,p->tm_sec,p->tm_wday,p->tm_yday+1);
	return 0;
}
