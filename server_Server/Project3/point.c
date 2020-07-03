#include"point.h"

SendPoint createPoint3(int type,int code,int speed,int lotation , int x, int y, int z) {
    SendPoint v = { type,code,speed,lotation,x,y,z };
    return v;
}
SendPoint recvToSend(int type, RecvPoint recvPoint) {
    SendPoint sendPoint = { type,recvPoint.code,recvPoint.speed,recvPoint.lotation,recvPoint.x,recvPoint.y,recvPoint.z };
    return sendPoint;
}
void pointPrint(RecvPoint recvPoint) {
    printf("from %d : x:%d, y:%d, z:%d\n",recvPoint.code, recvPoint.x, recvPoint.y, recvPoint.z);

}
