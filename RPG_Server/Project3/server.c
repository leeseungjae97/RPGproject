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
#include "server.h"
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
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //윈도우 소켓을 사용하겠다는 사실을 운영체제에 전달
        ErrorHandling("WSAStartup() error!");

    hMutex = CreateMutex(NULL, FALSE, NULL);//하나의 뮤텍스를 생성한다.
    serverSock = socket(PF_INET, SOCK_STREAM, 0); //하나의 소켓을 생성한다.

    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) //생성한 소켓을 배치한다.
        ErrorHandling("bind() error");
    if (listen(serverSock, 5) == SOCKET_ERROR)//소켓을 준비상태에 둔다.
        ErrorHandling("listen() error");

    while (1) {
        clientAddrSize = sizeof(clientAddr);
        clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &clientAddrSize);//서버에게 전달된 클라이언트 소켓을 clientSock에 전달
        WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
        clientSocks[clientCount++] = clientSock;//클라이언트 소켓배열에 방금 가져온 소켓 주소를 전달
        ReleaseMutex(hMutex);//뮤텍스 중지
        hThread = (HANDLE)_beginthreadex(NULL, 0, HandleClient, (void*)&clientSock, 0, NULL);//HandleClient 쓰레드 실행, clientSock을 매개변수로 전달
        printf("Connected Client IP : %s\n", inet_ntoa(clientAddr.sin_addr));
    }
    closesocket(serverSock);//생성한 소켓을 끈다.
    WSACleanup();//윈도우 소켓을 종료하겠다는 사실을 운영체제에 전달
    return 0;
}

unsigned WINAPI HandleClient(void* arg) {
    SOCKET clientSock = *((SOCKET*)arg); //매개변수로받은 클라이언트 소켓을 전달
    int strLen = 0, i,type;
    char msg[BUF_SIZE];

    while ((strLen = recvn(clientSock, (char*)&type, sizeof(int), 0)) != 0) { //클라이언트로부터 메시지를 받을때까지 기다린다.

        RecvPoint recvPoint;
        SendPoint sendPoint;
        int recvLen;
        switch (type) {
        case REGISTER:
            break;
        case LOGIN:
            break;
        case SPAWN:
            break;
        case MOVE:
            recvLen = recvn(clientSock, (char*)&recvPoint, sizeof(recvPoint), 0);
            sendPoint = recvToSend(MOVE, recvPoint);
            int j;
            WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
            for (j = 0; j < clientCount; j++)//클라이언트 개수만큼
                send(clientSocks[j], (char*)&sendPoint, sizeof(sendPoint), 0);//클라이언트들에게 메시지를 전달한다.
            ReleaseMutex(hMutex);//뮤텍스 중지
            break;
        }
    }
        



    //이 줄을 실행한다는 것은 해당 클라이언트가 나갔다는 사실임 따라서 해당 클라이언트를 배열에서 제거해줘야함
    WaitForSingleObject(hMutex, INFINITE);//뮤텍스 실행
    for (i = 0; i < clientCount; i++) {//배열의 갯수만큼
        if (clientSock == clientSocks[i]) {//만약 현재 clientSock값이 배열의 값과 같다면
            while (i++ < clientCount - 1)//클라이언트 개수 만큼
                clientSocks[i] = clientSocks[i + 1];//앞으로 땡긴다.
            break;
        }
    }
    clientCount--;//클라이언트 개수 하나 감소
    ReleaseMutex(hMutex);//뮤텍스 중지
    closesocket(clientSock);//소켓을 종료한다.
    return 0;
}
//중계





