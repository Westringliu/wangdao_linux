#include<stdio.h>

int multi(int,int);
int add(int,int);
int main()
{
	int c;
	int d;
	c=multi(3,4);
	d=add(3,4);
	printf("a*b=%d\n",c);
	printf("a+b=%d\n",d);
	return 0;
}
