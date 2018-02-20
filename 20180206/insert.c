#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>
int main(int argc,char* argv[])
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char* server="localhost";
    char* user="root";
    char* password="123";
    char* database="student";
    char query[200]="insert into Person1(FirstName,LastName,Age,salary) values('xiong','er',5,2000)";
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
        printf("insert success\n");
    }
    mysql_close(conn);
    return 0;
}

