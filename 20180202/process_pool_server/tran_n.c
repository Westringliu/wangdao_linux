#include "func.h"
//循环发送
void sendn(int sfd,char* buf,int len)
{
    int total=0;
    int ret;
    while(total<len)
    {
        ret=send(sfd,buf+total,len-total,0);
        total=total+ret;
    }
}
//循环接收
void recvn(int sfd,char *buf,int len)
{
    int total=0;
    int ret;
    while(total<len)
    {
        ret=recv(sfd,buf+total,len-total,0);
        total=total+ret;
    }
}
