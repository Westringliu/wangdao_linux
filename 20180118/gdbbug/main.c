#include<stdio.h>
int add(int,int);
int main()
{
	int a=0,b=1,i;
	int c[5]={2,3,4,5,6};
	printf("%d\n",a);
	printf("%d\n",b);
	printf("a+b=%d\n",add(a,b));
	for(i=0;i<5;i++)
	{
		printf("c[%d]=%d\n",i,c[i]);
	}
	return 0;
}
