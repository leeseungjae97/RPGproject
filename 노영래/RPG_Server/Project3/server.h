#pragma once
#define PORT 4000
#define BUF_SIZE 100
#define MAX_CLNT 256
#define MAX_PARTY 4

int clientCount = 0;
User clientSocks[MAX_CLNT];//Ŭ���̾�Ʈ ���� ������ �迭
HANDLE hMutex;//���ؽ�

unsigned WINAPI HandleClient(void* arg);//������ �Լ�
void SendMsg(char* msg, int len);//�޽��� ������ �Լ�
void ErrorHandling(char* msg);
void err_exit(const char* msg);
int recvn(SOCKET sock, char* buffer, int length, int flags);
void ErrorHandling(char* msg);
unsigned WINAPI HandleClient(void* arg);
enum Type { REGISTER = 1, LOGIN = 2, SPAWN = 3, MOVE = 4 ,DUPCHECK = 5, ITEM = 6, LEVEL = 7, SHOP = 8,
	MONSTER = 9, USER = 10, EQUIPMENT = 11,STOPATTACK=20,ATTACK=21,WEAPON=22,DAMAGE=23,MAKEPARTY,REQUEST_TO_PARTY,REQUESET_TO_PLAYER,OUT_OF_PARTY};

