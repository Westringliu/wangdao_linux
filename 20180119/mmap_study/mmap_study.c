#include<unistd.h>
#include<stdio.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdlib.h>

typedef struct
{
	int integer;
	char string[24];
}RECORD;

#define NRECORDS (100)

int main()
{
	RECORD record,*mapped;
	int i,f;
	FILE *fp;

	fp=fopen("records.dat","w+");
	for(i=0;i<NRECORDS;i++)
	{
		record.integer=i;
		sprintf(record.string,"RECORD-%d",i);
		fwrite(&record,sizeof(record),1,fp);
	}	
	fclose(fp);
}
