#include"member.h"

SendMemberInfo MemInfoToSendMemInfo(int type, MemberInfo minfo) {

	SendMemberInfo sminfo = { type, minfo.id,minfo.password };

	return sminfo;
}