#include "query.h"



Query getConnection() {
	MYSQL* conn;
	MYSQL_ROW row = NULL;
	MYSQL_RES * res = NULL;
	int len = 0;
	conn = mysql_init(NULL);
	conn = mysql_real_connect(conn, "powerlinux.co.kr", "sj2360", "1234", "sj2360", 3306, NULL, 0);

	if (conn) {
		puts("DB���� ����!!");
	}
	else {
		fprintf(stderr,"DB ���� ����" );
	}
	Query temp = { conn,row,res };

	return temp;
}

void DestroyConnection(MYSQL * conn) {
	mysql_close(conn);
}

int CountDupResult(Query q) {
	q.res = mysql_store_result(q.conn);
	int temp;
	while ((q.row = mysql_fetch_row(q.res)) != NULL) {
		temp = atoi(q.row[0]);
	}
	
	mysql_free_result(q.res);
	return temp;
}

