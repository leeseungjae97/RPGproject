#include "attack.h"

SendAttack createSendAttack(int type, int myCode, int targetCode) {
	SendAttack sendAttack = { type,myCode,targetCode };
	return sendAttack;
}
StopAttack createStopAttack(int type, int myCode) {
	StopAttack stopAttack = { type,myCode };
	return stopAttack;
}
SendAttachWeapon createSendAttachWeapon(int type, int myCode, int targetCode) {
	SendAttachWeapon temp = { type,myCode,targetCode };
	return temp;
}
SendDamage createSendDamage(int type,int from,int to, int damage){
	SendDamage sendDamage = { type,from,to,damage };
	return sendDamage;
}
SendProjectile createSendProjectile(int type, int num, int x, int y, int z) {
	SendProjectile temp = { type,num,x,y,z };
	return temp;
}
