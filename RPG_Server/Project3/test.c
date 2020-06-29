#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32")

//#define PORT 4567
#define PORT 4000
typedef struct SendPoint {
   int type, x, y, z;
}SendPoint;

typedef struct RecvPoint{
   int x, y, z;
}RecvPoint;

SendPoint createPoint3(int type,int x, int y, int z) {
   SendPoint v = { type,x,y,z };
   return v;
}

SendPoint createPoint3_() {
   int x, y, z;
   int type;
   printf("type: "); scanf("%d", &type);
   printf("x: "); scanf("%d", &x);
   printf("y: "); scanf("%d", &y);
   printf("z: "); scanf("%d", &z);
   return createPoint3(type,x, y, z);
}

void err_exit(const char* msg) {
   LPVOID lpMsgBuf;
   FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
      0, WSAGetLastError(),
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)&lpMsgBuf, 0, 0);
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


int main(int argc, char* argv[]) {
   printf("c server\n");
   WSADATA wsa;
   WSAStartup(MAKEWORD(2, 2
   ), &wsa);         //WS2_32.DLL을 사용할수 있도록 초기화 하는데 사용하는 함수. 아래에 WSACleanup()을 통해 닫아주는것도 있음.

   SOCKET gate = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   //socket()을 통해 서버의 소켓을 생성함. TCP로

   if (gate == INVALID_SOCKET) {   //만약 소켓 연결 실패했을시
      err_exit("gate");
   }
   SOCKADDR_IN gateAddress = { 0, };
   gateAddress.sin_family = AF_INET;      //주소 체계: AF_INET 항상 이것으로 설정해야함. 필수임 // IPV4 인터넷 프로토콜
   gateAddress.sin_addr.s_addr = htonl(INADDR_ANY);   //호스트IP주소 -> 이 변수에는 INADDR_ 로 시작하는 값, 예를 들면 'INADDR_ANY' 와 같은 것이 저장되어야 한다. // 32비트 IPV4주소
   gateAddress.sin_port = htons(PORT);         //   short형의 변수를 host byte order에서 network byte order로 바꿔줌, 즉 이변수에 저장되는 값은 network byte order이어야함.

   if (bind(gate, (const struct sockaddr*)&gateAddress, sizeof(gateAddress)) == SOCKET_ERROR) { //bind()함수를 통해. 즉, 클라이언트가 서버의 위치를 알기위한 IP와 port의 등록작업 이라보면됌.
      err_exit("bind");
   }

   if (listen(gate, SOMAXCONN) == SOCKET_ERROR) {   //클라이언트의 connect()함수의 접속 요청을 '확인'하도록 요청한다. 확인되어진 요청에 대한 처리는 accept()함수에게 넘긴다. 5줄아래에잇음
      err_exit("listen");
   }

   SOCKADDR_IN clientAddress = { 0, };
   int cliAddrSize = sizeof(clientAddress);
   SOCKET client = accept(gate, (struct sockaddr*)&clientAddress, &cliAddrSize);   //접속된 클라이언트와 대화하기 위한 소켓 생성


   


   if (client == INVALID_SOCKET) err_exit("client");
   printf("accepted\n");

   printf("send\n");
   SendPoint sendPoint3 = createPoint3_();
   int sendLen = send(client, (char*)&sendPoint3, sizeof(sendPoint3), 0);
   if (sendLen < 1)err_exit("send");

   int a = -1;
   int recvLen1 = recvn(client, (char*)&a, sizeof(int), 0);
   printf("%d", a);
   RecvPoint recvPoint3;
   int recvLen = recvn(client, (char*)&recvPoint3, sizeof(recvPoint3), 0);
   if (recvLen < 1)err_exit("recv");
   printf("recv \nx: %d \ny: %d \nz: %d\n", recvPoint3.x, recvPoint3.y, recvPoint3.z);

   closesocket(client);      //다 쓴 소켓 닫기
   closesocket(gate);
   WSACleanup();
   system("pause");
}