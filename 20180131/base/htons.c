#include"func.h"

int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("error args");
        return -1;
    }
    short port;
    port=atoi(argv[1]);
    printf("por=%x\n",port);
    short sin_port;
    sin_port=htons(port);
    printf("sin_port=%x\n",sin_port);
    return 0;
}
