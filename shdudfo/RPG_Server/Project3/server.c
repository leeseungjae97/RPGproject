#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <process.h>
#include"point.h"
#include "user.h"
#include "server.h"
#include"attack.h"
#include"member.h"
#include"query.h"
#include <mysql.h>
#pragma comment(lib, "ws2_32")
void err_exit(const char* msg) {
    LPVOID lpMsgBuf;
    FormatMessage( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, 0, WSAGetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&lpMsgBuf, 0, 0);
    MessageBox(NULL, (LPCSTR)lpMsgBuf, msg, MB_OK);
    LocalFree(lpMsgBuf);
    exit(1);
}

int recvn(SOCKET sock, char* buffer, int length, int flags) {
    int curLen = 0;
    while (curLen < length) {
        int recvLen = recv(sock, buffer, length, flags);
        if (recvLen < 1)
            return SOCKET_ERROR;
        buffer += recvLen;
        curLen += recvLen;
    }
    return curLen;
}


void ErrorHandling(char* msg) {
    fputs(msg, stderr);
    fputc('\n', stderr);
    exit(1);
}




int main(int argc, char* argv[]) {
    WSADATA wsaData;
    SOCKET serverSock, clientSock;
    SOCKADDR_IN serverAddr, clientAddr;
    int clientAddrSize;
    HANDLE hThread;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //������ ������ ����ϰڴٴ� ����� �ü���� ����
        ErrorHandling("WSAStartup() error!");

    hMutex = CreateMutex(NULL, FALSE, NULL);//�ϳ��� ���ؽ��� �����Ѵ�.
    serverSock = socket(PF_INET, SOCK_STREAM, 0); //�ϳ��� ������ �����Ѵ�.

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //������ ������ ��ġ�Ѵ�.
        ErrorHandling("bind() error");
    if (listen(serverSock, 5) == SOCKET_ERROR)//������ �غ���¿� �д�.
        ErrorHandling("listen() error");
    puts("bind success!\n");
    while (1) {
        clientAddrSize = sizeof(clientAddr);
        clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//�������� ���޵� Ŭ���̾�Ʈ ������ clientSock�� ����
        WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
        

		//User user;
		//user.socket = clientSock;
		//clientSocks[clientCount++] = user;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
        ReleaseMutex(hMutex);//���ؽ� ����
        hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient ������ ����, clientSock�� �Ű������� ����
        printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
    }
    closesocket(serverSock);//������ ������ ����.
    WSACleanup();//������ ������ �����ϰڴٴ� ����� �ü���� ����
    return 0;
}
unsigned WINAPI HandleClient(void* arg) {
    //////////////////////////////////////////////////////////////////////////////������////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SOCKET clientSock = *((SOCKET*)arg); //�Ű������ι��� Ŭ���̾�Ʈ ������ ����
    int strLen = 0, i,type;
    char msg[BUF_SIZE];
////////////////////////////////////////////////////////////////////////////////���¿� ��/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int k = 1;
    char query[BUFSIZ] = "";
    int row, col;

    while ((strLen = recvn(clientSock, (char*)&type, sizeof(int), 0)) > 0) { //Ŭ���̾�Ʈ�κ��� �޽����� ���������� ��ٸ���.
///////////////////////////////////////////////////////////////////////////////////////������//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        SOCKET party[MAX_PARTY];
        int j = 0;
        RecvPoint recvPoint;
        SendPoint sendPoint;
        RecvAttack recvAttack;
        SendAttack sendAttack;
        StopAttack stopAttack;
        RecvAttachWeapon recvWeapon;
        SendAttachWeapon sendWeapon;
        RecvDamage RecvDamage;
        SendDamage sendDamage;
        int code;
        int recvLen;
		User user;
/////////////////////////////////////////////////////////////////////////////////////�¿���///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        SendMemberInfo smInfo;
        MemberInfo mInfo;
        Query q;
        int count;
        switch (type) {
        case REGISTER:
            q = getConnection();
            recvLen = recvn(clientSock, (char*)&mInfo, sizeof(MemberInfo), 0);
            if (recvLen < 0) {
                perror("recvn");
                DestroyConnection(q.conn);
                return -1;
            }
            RESISTERUSER(query, mInfo);
            if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
            {
                printf("query fail; err=%s\n", mysql_error(q.conn));
                //���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
                DestroyConnection(q.conn);
                return -1;
            }
            DestroyConnection(q.conn);
            smInfo = MemInfoToSendMemInfo(REGISTER, mInfo);
            send(*(SOCKET*)arg, (char*)&smInfo, sizeof(smInfo), 0);

            break;
        case LOGIN:
            q = getConnection();
            recvLen = recvn(clientSock, (char*)&mInfo, sizeof(MemberInfo), 0);
            if (recvLen < 0) {
                perror("recvn");
                DestroyConnection(q.conn);
            }
            ISEXIST(query, mInfo);
            if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
            {
                printf("query fail; err=%s\n", mysql_error(q.conn));
                //���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
                DestroyConnection(q.conn);
                return -1;
            }
            if ((count = CountDupResult(q)) != 1) {
                mInfo.id = MAXINT;
                mInfo.password = MAXINT;
            }
            else{
                LOGIN(query, mInfo);
                if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
                {
                    printf("query fail; err=%s\n", mysql_error(q.conn));
                    //���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
                    DestroyConnection(q.conn);
                    return -1;
                }
                printf("%d", mysql_affected_rows(q.conn));
                if (mysql_affected_rows(q.conn) == 0) {
                    mInfo.id = MININT;
						mInfo.password = MININT;
		/////////��ŷ�� ���⼭ ����/////////////////////////////
				}
				else {

					//User user = new User();
					//					//�α��� ������//
					//clientSocks[clientCount++] = clientSock;//Ŭ���̾�Ʈ ���Ϲ迭�� ��� ������ ���� �ּҸ� ����
				}
            }

            DestroyConnection(q.conn);
            smInfo = MemInfoToSendMemInfo(LOGIN, mInfo);
            send(*(SOCKET*)arg, (char*)&smInfo, sizeof(smInfo), 0);
            break;
		case DUPCHECK:
			q = getConnection();
			recvLen = recvn(clientSock, (char*)&mInfo.id, sizeof(int), 0);

			if (recvLen < 0) {
				perror("recvn");
				DestroyConnection(q.conn);
				return -1;
			}
			ISDUP(query, mInfo.id);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			count = CountDupResult(q);
			DestroyConnection(q.conn);
			send(*(SOCKET*)arg, (char*)&count, sizeof(count), 0);
			break;

		case ITEM:

			q = getConnection();

			GETITEM(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			int** ItemBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				ItemBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					ItemBuf[k][x] = atoi(q.row[x]);
				}
				send(*(SOCKET*)arg, (char*)(ItemBuf[k]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(ItemBuf);
			break;

		case LEVEL:

			q = getConnection();

			GETLEVEL(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			int** LevelBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				LevelBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&type, sizeof(int), 0);
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					LevelBuf[k][x] = atoi(q.row[x]);
				}
				send(*(SOCKET*)arg, (char*)(LevelBuf[k]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(LevelBuf);
			break;

		case SHOP:
			q = getConnection();

			GETSHOP(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			int** ShopBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				ShopBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&type, sizeof(int), 0);
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					ShopBuf[k][x] = atoi(q.row[x]);
				}
				send(*(SOCKET*)arg, (char*)(ShopBuf[k]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(ShopBuf);
			break;
		case MONSTER:
			q = getConnection();

			GETMONSTER(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			int** MonsterBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				MonsterBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&type, sizeof(int), 0);
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					MonsterBuf[k][x] = atoi(q.row[x]);
				}
				send(*(SOCKET*)arg, (char*)(MonsterBuf[k]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(MonsterBuf);
			break;
		case USER:
			q = getConnection();

			GETUSER(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			printf("%d %d", row, col);
			int** UserBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				UserBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&type, sizeof(int), 0);
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					UserBuf[x][k] = atoi(q.row[x]);
					printf("%d %d ", x, UserBuf[x][k]);

				}
				printf("\n");
				send(*(SOCKET*)arg, (char*)(UserBuf[col - 1]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(UserBuf);
			break;

		case EQUIPMENT:
			q = getConnection();

			GETEQUIPMENT(query);
			if (mysql_query(q.conn, query) != 0)   //show������ query�� �־��ذ�����. ��, �����Ѱ���   
			{
				printf("query fail; err=%s\n", mysql_error(q.conn));
				//���� ������ ������ �� ������ ����ϴ°Ŷ��ϴ�.  
				DestroyConnection(q.conn);
				return -1;
			}
			q.res = mysql_store_result(q.conn); //���� ���� ��� ���

			row = mysql_num_rows(q.res); //Ʃ���� ����
			col = mysql_num_fields(q.res);
			int** EquipmentBuf = malloc(sizeof(int*) * col);
			for (int k = 0; k < col; k++) {
				EquipmentBuf[k] = malloc(sizeof(int) * row); //�������� ���� �迭 ����
			}
			k = 0;
			send(*(SOCKET*)arg, (char*)&type, sizeof(int), 0);
			send(*(SOCKET*)arg, (char*)&row, sizeof(row), 0);
			while ((q.row = mysql_fetch_row(q.res)) != NULL) {
				for (int x = 0; x < col; x++) {
					EquipmentBuf[k][x] = atoi(q.row[x]);
				}
				send(*(SOCKET*)arg, (char*)(EquipmentBuf[k]), sizeof(int) * col, 0);
				k++;
			}

			mysql_free_result(q.res);
			free(EquipmentBuf);
			break;
		
//////////////////////////////////////////������/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case MOVE:
            recvLen = recvn(clientSock, (char*)&recvPoint, sizeof(recvPoint), 0);
            //pointPrint(recvPoint);
            sendPoint = recvToSend(MOVE, recvPoint);
            WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
            for (j = 0; j < clientCount; j++)//Ŭ���̾�Ʈ ������ŭ
                send(clientSocks[j].socket, (char*)&sendPoint, sizeof(sendPoint), 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
            ReleaseMutex(hMutex);//���ؽ� ����
            break;
        case STOPATTACK:
            
            recvLen = recvn(clientSock, (char*)&code, sizeof(int), 0);
            stopAttack = createStopAttack(STOPATTACK, code);
            //printf("%d\n", stopAttackCode);
            WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
            for (j = 0; j < clientCount; j++)//Ŭ���̾�Ʈ ������ŭ
                send(clientSocks[j].socket, (char*)&stopAttack, sizeof(stopAttack), 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
            ReleaseMutex(hMutex);//���ؽ� ����
            
            break;
        case ATTACK:

            
            recvLen = recvn(clientSock, (char*)&recvAttack, sizeof(recvAttack), 0);
            sendAttack = createSendAttack(ATTACK, recvAttack.myCode, recvAttack.targetCode);
            //printf("Attack %d %d %d\n", sendAttack.type, sendAttack.myCode, sendAttack.targetCode);
            WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
            for (j = 0; j < clientCount; j++)//Ŭ���̾�Ʈ ������ŭ
                send(clientSocks[j].socket, (char*)&sendAttack, sizeof(sendAttack), 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
            ReleaseMutex(hMutex);//���ؽ� ����
            break;
        case WEAPON:

            recvLen = recvn(clientSock, (char*)&recvWeapon, sizeof(recvWeapon), 0);
            sendWeapon = createSendAttachWeapon(WEAPON, recvWeapon.myCode, recvWeapon.weapon);
            //printf("Attack %d %d %d\n", sendAttack.type, sendAttack.myCode, sendAttack.targetCode);
            WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
            for (j = 0; j < clientCount; j++)//Ŭ���̾�Ʈ ������ŭ
                send(clientSocks[j].socket, (char*)&sendWeapon, sizeof(sendWeapon), 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
            ReleaseMutex(hMutex);//���ؽ� ����
            break;
        case DAMAGE:

            recvLen = recvn(clientSock, (char*)&RecvDamage, sizeof(RecvDamage), 0);
            sendDamage = createSendDamage(DAMAGE, RecvDamage.from, RecvDamage.to, RecvDamage.damage);
            printf("Attack %d %d %d\n", sendDamage.from,sendDamage.to,sendDamage.damage);
            WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
            for (j = 0; j < clientCount; j++)//Ŭ���̾�Ʈ ������ŭ
                send(clientSocks[j].socket, (char*)&sendDamage, sizeof(sendDamage), 0);//Ŭ���̾�Ʈ�鿡�� �޽����� �����Ѵ�.
            ReleaseMutex(hMutex);//���ؽ� ����
            break;

        }
    }
        

    
    printf("%d", 10);

    //�� ���� �����Ѵٴ� ���� �ش� Ŭ���̾�Ʈ�� �����ٴ� ����� ���� �ش� Ŭ���̾�Ʈ�� �迭���� �����������
    WaitForSingleObject(hMutex, INFINITE);//���ؽ� ����
    for (i = 0; i < clientCount; i++) {//�迭�� ������ŭ
        if (clientSock == clientSocks[i].socket) {//���� ���� clientSock���� �迭�� ���� ���ٸ�
            while (i++ < clientCount - 1)//Ŭ���̾�Ʈ ���� ��ŭ
                clientSocks[i] = clientSocks[i + 1];//������ �����.
            break;
        }
    }
    clientCount--;//Ŭ���̾�Ʈ ���� �ϳ� ����
    ReleaseMutex(hMutex);//���ؽ� ����
    closesocket(clientSock);//������ �����Ѵ�.
    return 0;
}
//�߰�





