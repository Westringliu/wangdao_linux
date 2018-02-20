#include"func.h"
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
    struct hostent *p;
    p=gethostbyname(argv[1]);
    if(NULL==p)
    {
        printf("gethostbyname h_errno=%d\n",h_errno);
        return -1;
    }
    printf("h_name %s\n",p->h_name);
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++)
    {
        printf("%s\n",p->h_aliases[i]);
    }
    char ip[16]={0};
    for(i=0;p->h_addr_list[i]!=NULL;i++)
    {
        bzero(ip,sizeof(ip));
        inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip));
        printf("ip=%s\n",ip);
        printf("%d\n",p->h_length);
    }
    return 0;
}
