#pragma once
#include <mysql.h>
#include <stdio.h>
#include "member.h"
#include<stdlib.h>
#define ISDUP(x,y) sprintf((x), "SELECT COUNT(*) FROM m2_user WHERE id =('%d');", (y));
#define RESISTERUSER(x,y) sprintf((x),"INSERT INTO m2_user values ( default ,('%d'),('%d'),default,default,default)",(y.id),(y.password));
#define LOGIN(x,y)  sprintf((x), "UPDATE m2_user SET Login = 1 WHERE id = ('%d') AND `password` = ('%d') AND LOGIN = 0",(y.id),(y.password));
#define ISEXIST(x,y) sprintf((x), "SELECT COUNT(*) FROM m2_user WHERE id = ('%d') AND `password` = ('%d')",(y.id),(y.password));
#define GETITEM(x) sprintf((x), "SELECT * FROM m2_item ");
#define GETLEVEL(x) sprintf((x), "SELECT * FROM m2_Level ");
#define GETSHOP(x) sprintf((x), "SELECT * FROM m2_shop ");
#define GETMONSTER(x) sprintf((x), "SELECT * FROM m2_monster ");
#define GETUSER(x) sprintf((x), "SELECT user_code FROM m2_user WHERE Login = 1");
#define GETEQUIPMENT(x) sprintf((x), "SELECT * FROM m2_equipment");
typedef struct Query {
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES * res;
}Query;

Query getConnection();
void DestroyConnection(MYSQL * conn);
int CountDupResult(Query q);

