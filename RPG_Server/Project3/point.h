
#pragma once
typedef struct SendPoint {
    int type, x, y, z;
}SendPoint;

typedef struct RecvPoint {
    int x, y, z;
}RecvPoint;

SendPoint createPoint3(int type, int x, int y, int z);
SendPoint createPoint3_();
SendPoint recvToSend(int type, RecvPoint recvPoint);
