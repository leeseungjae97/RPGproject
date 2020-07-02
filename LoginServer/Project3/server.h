#pragma once
#define PORT 4000
#define BUF_SIZE 100
#define MAX_CLNT 256

int clientCount = 0;
SOCKET clientSocks[MAX_CLNT];//클라이언트 소켓 보관용 배열
HANDLE hMutex;//뮤텍스

unsigned WINAPI HandleClient(void* arg);//쓰레드 함수
void SendMsg(char* msg, int len);//메시지 보내는 함수
void ErrorHandling(char* msg);
void err_exit(const char* msg);
int recvn(SOCKET sock, char* buffer, int length, int flags);
void ErrorHandling(char* msg);
unsigned WINAPI HandleClient(void* arg);
enum Type { REGISTER = 1, LOGIN = 2, SPAWN = 3, MOVE = 4 ,DUPCHECK = 5, ITEM = 6};
