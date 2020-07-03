#pragma once
typedef struct RecvAttack {
	int myCode;
	int targetCode;
}RecvAttack;
typedef struct SendAttack {

	int type;
	int myCode;
	int targetCode;
}SendAttack;
typedef struct StopAttack {
	int type;
	int code;
}StopAttack;

typedef struct RecvAttachWeapon {
	int myCode;
	int weapon;
}RecvAttachWeapon;
typedef struct SendAttachWeapon {

	int type;
	int myCode;
	int weapon;
}SendAttachWeapon;

typedef struct RecvDamage {
	int from;
	int to;
	int damage;
}RecvDamage;
typedef struct SendDamage {
	int type;
	int from;
	int to;
	int damage;
}SendDamage;
typedef struct SendProjectile {
	int type;
	int num;
	int x;
	int y;
	int z;

}SendProjectile;
typedef struct RecvProjectile {
	int num;
	int x;
	int y;
	int z;

}RecvProjectile;
SendAttack createSendAttack(int type, int myCode, int targetCode);
SendAttachWeapon createSendAttachWeapon(int type, int myCode, int targetCode);
SendDamage createSendDamage(int type,int from,int to, int damage);
StopAttack createStopAttack(int type, int myCode);
SendProjectile createSendProjectile(int type, int num, int x, int y, int z);
