#include<stdio.h>
int main()
{
	int a=11,b=12,i=0;
	int c[5]={1,2,3,4,5};
	printf("a=%d\n",a);
	printf("b=%d\n",b);
	for(i=0;i<5;i++)
	{
		printf("c[%d]=%d\n",i,c[i]);
	}
}
