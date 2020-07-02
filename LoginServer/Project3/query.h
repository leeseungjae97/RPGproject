#include <mysql.h>
#include <stdio.h>
#include "member.h"
#include<stdlib.h>
#define ISDUP(x,y) sprintf((x), "SELECT COUNT(*) FROM m2_user WHERE id =('%d');", (y));
#define RESISTERUSER(x,y) sprintf((x),"INSERT INTO m2_user values ( default ,('%d'),('%d'),default,default)",(y.id),(y.password));
#define ISEXIST(x,y) sprintf((x), "SELECT COUNT(*) FROM m2_user WHERE id = ('%d') AND `password` = ('%d')",(y.id),(y.password));
#define GETITEM(x) sprintf((x), "SELECT * FROM m2_item ");

typedef struct Query {
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES * res;
}Query;

Query getConnection();
void DestroyConnection(MYSQL * conn);
int CountDupResult(Query q);

