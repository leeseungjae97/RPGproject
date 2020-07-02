#include"point.h"

SendPoint createPoint3(int type, int x, int y, int z) {
	SendPoint v = { type,x,y,z };
	return v;
}
SendPoint recvToSend(int type, RecvPoint recvPoint) {
	SendPoint sendPoint = { type,recvPoint.x,recvPoint.y,recvPoint.z };
	return sendPoint;
}
//SendPoint createPoint3_() {
//    int x, y, z;
//    int type;
//    printf("type: "); scanf("%d", &type);
//    printf("x: "); scanf("%d", &x);
//    printf("y: "); scanf("%d", &y);
//    printf("z: "); scanf("%d", &z);
//    return createPoint3(type, x, y, z);
//}
