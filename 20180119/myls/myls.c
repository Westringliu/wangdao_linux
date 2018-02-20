#include"func.h"
int main(int argc,char* argv[])
{
	if(argc!=2)
	{
		printf("error args\n");
		return -1;
	}
	struct stat buf;
	DIR *dir;
	dir=opendir(argv[1]);
	struct dirent *p;
	while((p=readdir(dir))!=NULL)
	{
			memset(&buf,0,sizeof(buf));
			int ret;
//			sprintf(p->d_name,"%s%s","./",p->d_name);
//			printf("%s\n",p->d_name); 
			ret=stat(p->d_name,&buf);
			if(-1==ret)
			{
				perror("stat");
				return -1;
			}
		char i=S_ISDIR(buf.st_mode)?'d':'-';
		printf("%c %o %ld %s %s %ld %.12s %s\n",i,buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,buf.st_size,4+ctime(&buf.st_mtime),p->d_name);
	}
	return 0;
}
