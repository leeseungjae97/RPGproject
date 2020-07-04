
#pragma once
typedef struct SendPoint {
    int type,speed,lotation, code, x, y, z;
}SendPoint;

typedef struct RecvPoint {
    int code,speed,lotation,x, y, z;
}RecvPoint;

SendPoint createPoint3(int type,int code,int speed, int lotation,int x, int y, int z);
SendPoint recvToSend(int type, RecvPoint recvPoint);
void pointPrint(RecvPoint recvPoint);
