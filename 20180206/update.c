#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="123";
    char* database="student";
    char query[200]="update Person1 set FirstName='meinv' where personID=";
    int personid=atoi(argv[1]);
    sprintf(query,"%s%d",query,personid);
    puts(query);
    int t,r;
    conn=mysql_init(NULL);
    if(!mysql_real_connect(conn,server,"root","95Westring",database,0,NULL,0))
    {
        printf("Error connecting to database:%s\n",mysql_error(conn));
    }else{
        printf("Connected...\n");
    }
    t=mysql_query(conn,query);
    if(t)
    {
        printf("Error making query:%s\n",mysql_error(conn));
    }else{
        printf("update success\n");
    }
    mysql_close(conn);
    return 0;
}

